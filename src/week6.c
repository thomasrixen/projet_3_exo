#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

int global = 0;
pthread_mutex_t mu;

int saveType(void *pt, int size, char *filename, size_t element_size) {
    /*
    * @pre pt != NULL, pointer to the first point_t in the array
    *      size > 0, the length of the array.
    *      filename != NULL
    * @post writes the array of point_t in the file.
    *       return 0 is everything worked correctly
    *       -1 if open() failed.
    *       -2 if close() failed.
    *       -3 if mmap() failed.
    *       -4 if munmap() failed.
    *       -5 if msync() failed.
    *       -6 if ftruncate() failed.
    *
    */
    int fd = open(filename, O_RDWR|O_CREAT, 700);
    size_t len = (size_t) (size)*element_size;
    if (fd<0){
        return -1;
    }
    if (ftruncate(fd, len)<0){
        return -6;
    }
    void *ptr = mmap(NULL, len, PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED){
        return -3;
    }
    memcpy(ptr, pt, len);
    if (msync(ptr,len, MS_SYNC)<0){
        return -5;
    }
    if (munmap(ptr, len)<0){
        return -4;
    }
    if (close(fd)<0){
        return -2;
    };
    return 0;
}


typedef struct points {
    int NOMA;
    float LEPL1103;
    float LEPL1203;
    float LEPL1108;
    float LEPL1302;
    float LEPL1402;
    float average;
} points_t;


int compar(const void* s1, const void* s2){
    /*
    * Function used to compare two structures based on their averages.
    *
    * @s1 : a pointer to the first structure
    * @s2 : a pointer to the second structure
    *
    * @return an integer less than, equal to, or greater than zero if the first argument is considered to be
    *        respectively less than, equal to, or greater than the second
    */
    points_t *p1 = (points_t*) s1;
    points_t *p2 = (points_t*)s2;
    if (p1->average < p2->average){
        return -1;
    }else if (p1->average == p2->average){
        return 0;
    }else{
        return 1;
    }
}


int sort(char* filename){
    /*
    * Function used to update the file with the structures stored in it
    *
    * @filename : the path indicating where to find the file (!= NULL)
    *
    * @return 0 if no error
    *        -1 if open failed
    *        -2 if mmap failed
    *        -3 if munmap failed
    *        -4 if msync failed
    *        -5 if fstat failed
    *        -6 if close failed
    */
    int fd = open(filename, O_RDWR);
    if (fd<0){
        return -1;
    }
    struct stat st;
    if (fstat(fd, &st)<0){
        if (close(fd)<0){
            return -6;
        }
        return -5;
    }
    size_t number = st.st_size/sizeof(points_t);
    points_t *ptr = (points_t*)mmap(NULL, st.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED){
        if (close(fd)<0){
            return -6;
        }
        return -2;
    }
    for (int i = 0; i<number; i++){
        (ptr+i)->average = ((ptr+i)->LEPL1103 + (ptr+i)->LEPL1108 + (ptr+i)->LEPL1203 + (ptr+i)->LEPL1302 + (ptr+i)->LEPL1402)/5;
    }
    qsort(ptr, number, sizeof(points_t), &compar);
    if (msync(ptr, st.st_size, MS_SYNC)<0){
        if (munmap(ptr, st.st_size)<0){
            return -3;
        }
        return -4;
    }
    if (munmap(ptr, st.st_size)<0){
        return -3;
    }
    if (close(fd)<0){
        return -6;
    }
    return 0;
}

void inc(){
    global++;
}

int protect(void inc(void), int nb, pthread_mutex_t* mutex){
    /*
    * Function used to protect a global variable used in the function inc().
    *
    * @inc : the function that must be called in critical (= protected) section
    * @nb : the number of times the function inc() has to be called
    * @mutex : an initialised mutex that has to be used for the protection
    *
    * @return 0 if no error, -1 otherwise
    */
    for (int i = 0; i < nb; i++)
    {
        if (pthread_mutex_lock(mutex)!=0){
            return -1;
        }
        inc();
        if (pthread_mutex_unlock(mutex)!=0){
            return -1;
        }
    }
    return 0;
}

void *protectCall( void * ptr){
    protect(&inc, 500, &mu);
    int *pt = 0;
    return (void*)pt;
}


int doMyWork(void* long_computing(void*), void* backup_computing(void*), char* string, int ret_value){
    /*
    * Function used to launch threads that will do the work for us.
    *
    * @long_computing : a function that will do a really long computing and that must be started by the thread.
    *                 This function initially returns a pointer to an int and takes as argument a string.
    *                 These have been casted into void* to match pthread_create() function specifications.
    *                 You have to launch this function with the argument *string* and compare the returned value
    *                 to *ret_value*. If the return value doesn't match *ret_value*,
    *                 you have to launch another thread on the same argument with the function *backup_computing*.
    *
    * @backup_computing :  a backup function that must be used if the first thread didn't do the job correctly.
    *                    As for *long_computing*, this function initially takes a string as argument and returns
    *                    a pointer to an int.
    *
    * @string : the string that must be used as a parameter to both functions described above.
    *
    * @ret_value : the value to which the first returned code must be compared to to know if the first thread
    *             correctly did the job or not.
    *
    * @return the int returned by the function started by the thread if no problem
    *         -1 if you can't create the first thread
    *         -2 if you can't join the first thread
    *         -3 if you can't create the second thread
    *         -4 if you can't join the second thread
    */
    pthread_t t;
    if (pthread_create(&t, NULL, long_computing, (void *)string)!=0){
        return -1;
    }
    void * ret;
    if (pthread_join(t, &ret)!=0){
        return -2;
    }
    if (*((int*) ret) == ret_value){
        return *((int*) ret);
    }
    if (pthread_create(&t, NULL, backup_computing, (void *)string)!=0){
        return -3;
    }
    if (pthread_join(t, &ret)!=0){
        return -4;
    }
    return *((int*) ret);
}

typedef struct data {
    int longitude;
    int latitude;
    float avg_temp;
} data_t;


int put(data_t** buf, int len, int* first, int* last, int* in, data_t* d){
    /*
    * Function used to put a new value in the shared buffer.
    *
    * @buf : the shared buffer to fill in with the adresses pointing to the data_t's
    * @len : the length of the shared buffer
    * @first : the pointer to the array index where you can find the first inserted element that's still in the buffer
    *         (or more exactly the pointer to the first element, **if any**)
    * @last : the pointer to the array index where you can find the first empty space in the buffer
    *         (or more exactly the first NULL pointer in the array, **if any**)
    * @in : the number of data_t* pointers in the buffer
    * @d : the data_t* that has to be inserted in the buffer
    *
    * @return 0 if no error, -1 otherwise
    */
    if (*in>=len){
        return -1;
    }
    (*in)++;
    *((buf)+*last) = d;
    (*last)++;
    if (*last>=len){
        *last = 0;
    }
    return 0;
}


data_t* get(data_t** buf, int len, int* first, int* last, int* in){
    /*
    * Function used to get a value from the shared buffer.
    *
    * @buf : the shared buffer to fill out
    * @len : the length of the shared buffer
    * @first : the pointer to the array index where you can find the first element inserted that's still in the buffer
    *         (or more exactly the pointer to the first element, **if any**)
    * @last : the pointer to the array index where you can find the first empty space in the buffer
    *         (or more exactly the first NULL pointer in the array, **if any**)
    * @in : the number of data_t* pointers in the buffer
    *
    * @return the pointer to the element that you get if no error, NULL otherwise
    */
    if (*in == 0){
        return NULL;
    }
    data_t* ret = *(buf + *first);
    (*first)++;
    if (*first>=len){
        *first = 0;
    }
    (*in)--;
    return ret;
}

int main(int argc, char const *argv[])
{
    /* Example exercice 1
    points_t a[] = {{0, 10, 9, 11, 11,9, 0}, {1, 18, 17, 19, 17, 19, 0}};
    saveType(a, 2, "./points.txt", sizeof(points_t));
    sort("./points.txt");
    */

    /* Example exercice 2
    pthread_t t;
    pthread_mutex_init(&mu, NULL);
    pthread_create(&t, NULL, &protectCall, NULL);
    pthread_t t2;
    pthread_create(&t2, NULL, &protectCall, NULL);
    pthread_join(t, NULL);
    pthread_join(t2, NULL);
    printf("%d\n", global);
    pthread_mutex_destroy(&mu);
    */

    /* Example exercice 4
    data_t **a = malloc(6*sizeof(data_t));
    int first = 0;
    int last = 0;
    int in = 0;
    data_t d = {1,2,3};
    put(a, 5, &first, &last, &in, &d);
    printf("%d, %d, %d\n", first, last, in);
    put(a, 5, &first, &last, &in, &d);
    printf("%d, %d, %d\n", first, last, in);
    put(a, 5, &first, &last, &in, &d);
    printf("%d, %d, %d\n", first, last, in);
    put(a, 5, &first, &last, &in, &d);
    printf("%d, %d, %d\n", first, last, in);
    put(a, 5, &first, &last, &in, &d);
    printf("%d, %d, %d\n", first, last, in);
    get(a, 5, &first, &last, &in);
    printf("%d, %d, %d\n", first, last, in);
    put(a, 5, &first, &last, &in, &d);
    printf("%d, %d, %d\n", first, last, in);
    get(a, 5, &first, &last, &in);
    printf("%d, %d, %d\n", first, last, in);
    get(a, 5, &first, &last, &in);
    printf("%d, %d, %d\n", first, last, in);
    put(a, 5, &first, &last, &in, &d);
    printf("%d, %d, %d\n", first, last, in);
    free(a);
    */
    return 0;
}
