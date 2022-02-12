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
    return 0;
}