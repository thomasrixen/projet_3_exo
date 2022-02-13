#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>
#include <errno.h>

typedef struct point {
    int x;
    int y;
    int z;
} point_t;


 int file_exists(char *filename){
    /*
    * @pre filename != NULL
    * @post return 0 if the file {filename} exist. -1 Otherwise.
    */
   int f = open(filename, O_WRONLY);
    if (f<0){
        return -1;
    }
    close(f);
    return 0;
 }


int save(point_t *pt, int size, char *filename) {
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
    size_t len = (size_t) (size)*sizeof(point_t);
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


int sum_file(char *filename) {
    /*
    * @pre filename != NULL, name of the file
    * @post returns the sum of all integers stored in the binary file.
    *       return -1 if the file can not be open.
    *       return -2 if the file can not be closed.
    *       return -3 if mmap() fails.
    *       return -4 if munmap() fails.
    *       return -5 if fstat() fails.
    */
    int fd = open(filename, O_RDWR, 700);
    if (fd<0){
        return -1;
    }
    struct stat st;
    if (fstat(fd, &st)<0){
        return -5;
    }
    if (st.st_size==0){
        // file is empty => stop immediatly
        if (close(fd)<0){
            return -2;
        }
        return 0;
    }
    int *ptr = (int *) mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED){
        return -3;
    }
    int sum = 0;
    for (int i = 0; i < st.st_size/sizeof(int); i++)
    {
        sum += *(ptr+i);
    }

    if (munmap(ptr, st.st_size)<0){
        return -4;
    }
    if (close(fd)<0){
        return -2;
    }
    return sum;
}

point_t * readFile(char* filename){
    int fd = open(filename,O_RDONLY);
    if (fd<0){
        return NULL;
    }
    struct stat st;
    fstat(fd, &st);
    point_t * ptr = (point_t *)mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (ptr==MAP_FAILED){
        return NULL;
    }
    point_t * new = malloc(st.st_size);
    memcpy(new, ptr, st.st_size);
    if (munmap(ptr, st.st_size)<0){
        return NULL;
    }
    close(fd);
    return new;
}


int get(char *filename, int index) {
    /*
    * @pre filename != NULL, index >= 0
    * @post return the integer at the index {index}
    *       of the array in the file {filename}.
    *       return -1 in case of error.
    *       return -2 if index >= length of array.
    */
    int fd = open(filename, O_RDWR);
    if (fd<0){
        return -1;
    }
    struct stat st;
    if (fstat(fd, &st)<0){
        return -1;
    }
    if (st.st_size/sizeof(int)<=index){
        // Out of bounds
        if (close(fd)<0){
            return -1;
        }
        return -2;
    }
    int * ptr = (int *) mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED){
        return -1;
    }
    int res = *(ptr+index);
    if (munmap(ptr, st.st_size)<0){
        return -1;
    }
    if (close(fd)<0){
        return -1;
    }
    return res;
}


void set(char *filename, int index, int value) {
    /*
    * @pre filename != NULL, index >= 0
    * @post set the element in the file {filename}
    *       at index {index} at value {value}.
    *       do nothing in case of errors
    */
    int fd = open(filename, O_RDWR);
    if (fd<0){
        return;
    }
    struct stat st;
    if (fstat(fd, &st)<0){
        return;
    }
    if (st.st_size/sizeof(int)<=index){
        // Out of bounds
        if (close(fd)<0){
            return;
        }
        return;
    }
    int * ptr = (int *) mmap(NULL, st.st_size, PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED){
        return;
    }
    *(ptr+index) = value;
    if (msync(ptr, st.st_size, MS_SYNC)<0){
        return;
    }
    if (munmap(ptr, st.st_size)<0){
        return;
    }
    if (close(fd)<0){
        return;
    }
    return;
}

int copy(char *file_name, char *new_file_name) {
    /*
    * @pre file_name != NULL, name of the original file
    *      new_file_name != NULL, name of the new file (the copy)
    *
    * @post copy the contents of {file_name} to {new_file_name}.
    *       return 0 if the function terminates with success, -1 in case of errors.
    */
    int fd1 = open(file_name, O_RDWR);
    
    if (fd1<0){
        return -1;
    }
    struct stat st;
    if (fstat(fd1, &st)<0){
        return -1;
    }
    int fd2 = open(new_file_name, O_RDWR|O_CREAT, st.st_mode);
    if (fd2<0){
        return -1;
    }
    if (ftruncate(fd2, st.st_size)<0){
        return -1;
    }
    void *ptr1 = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd1, 0);
    if (ptr1 == MAP_FAILED){
        return -1;
    }
    void *ptr2 = mmap(NULL, st.st_size, PROT_WRITE, MAP_SHARED, fd2, 0);
    if (ptr2 == MAP_FAILED){
        return -1;
    }
    memcpy(ptr2, ptr1, st.st_size);
    if (msync(ptr2, st.st_size, MS_SYNC)<0){
        return -1;
    }
    if (munmap(ptr1, st.st_size)<0){
        return -1;
    }
    if (munmap(ptr2, st.st_size)<0){
        return -1;
    }
    if (close(fd1)<0){
        return -1;
    }
    if (close(fd2)<0){
        return -1;
    }
    return 0;
}


int main(int argc, char const *argv[])
{
    /* Exercice 2 example
    point_t a = {1,2,3};
    point_t c[] = {a, a};
    int i =save(c, 3, "./test.txt");
    printf("%d\n", i);
    point_t *b = readFile("./test.txt");
    printf("%d\n",b->y);
    */

    /* Exercice 3 example
    int i[5] = {1,2,5,4,3};
    saveType(i, 5, "./int.txt", sizeof(int));
    printf("%d\n", sum_file("./int.txt"));
    */

    /* Exercice 4 example
    int i[5] = {1,2,5,4,3};
    saveType(i, 5, "./int.txt", sizeof(int));
    set("./int.txt", 3, 7);
    printf("%d\n", get("./int.txt", 4));
    */

    /* Exercice 5 example
    copy("./test.txt", "./copy.txt");
    */
    return 0;
}
