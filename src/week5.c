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



int main(int argc, char const *argv[])
{
    /*
    point_t a = {1,2,3};
    point_t c[] = {a, a};
    int i =save(c, 3, "./test.txt");
    printf("%d\n", i);
    point_t *b = readFile("./test.txt");
    printf("%d\n",b->y);
    */
    return 0;
}
