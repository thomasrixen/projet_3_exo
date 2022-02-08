#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


char *buf_strcpy(const char *src) {

    /*
* Creates a buffer that has the same size as src, and copies the content of src to this buffer.
*
* @src: string to be copied
* @return: return pointer. if src == NULL or in case of error, return NULL
*
* Remember that strings are terminated with '\0' and that strlen("abc") returns 3 even if 4 bytes are required to store this string.
*/
    int i = 0;
    while (*(src+i) != '\0'){
        i++;
    }
    char *ptr = malloc((size_t)(i+1)*sizeof(char));
    if (ptr == NULL){
        return NULL;
    }
    int j = 0;
    while (j<=i){
        *(ptr+j) = *(src+j);
        j++;
    }
    return ptr;
}

void *calloc2(size_t nmemb, size_t size) {
    if (nmemb ==0 || size == 0){
        void * ptr = NULL;
        return ptr;
    }
    char *ptr = malloc((size_t) (nmemb+1)*size);
    if (ptr == NULL){
        return NULL;
    }
    for (int i = 0; i < nmemb; i++)
    {
        *(ptr+i) = 0;
    }
    *(ptr+nmemb+1) = '\0';
    return (void *) ptr;
}


void *sleepy_malloc(size_t s) {
    /* Wrapper to the malloc system call.
    * If malloc fails, sleep for 5 seconds, and then try again.
    * If malloc failed 10 times in a row, return NULL.
    */
   void *ptr;
   for (int i = 0; i <10; i++){
       ptr = malloc(s);
       if (ptr != NULL){
           return ptr;
       }
       sleep(5);
   }
   return NULL;
}


typedef struct node {
    /**
    * Structure node
    *
    * @next: pointer to the next node in the list, NULL if last node_t
    * @value: value stored in the node
    */
  struct node *next;
  int value;
} node_t;

typedef struct list {
    /**
    * Structure list
    *
    * @first: first node of the list, NULL if list is empty
    * @size: number of nodes in the list
    */
  struct node *first;
  int size;
} list_t;


node_t *init_node(int value) {
    /*
    * Create a new node containing the value @value.
    *
    * @value: value stored in the node
    * @next : pointer to next node, initialised to NULL.
    * @return: returns the pointer to the newly created node, or NULL if an error occured.
    */
   node_t *new = (node_t *) malloc(sizeof(node_t));
   if (new == NULL){
       return NULL;
   }
   new->value = value;
   new->next = NULL;
   return new;
}


int add_node(list_t *list, int value) {
    /*
    * Add a node at the head of the list @list and increment the number of nodes in the list (member `size`)
    *
    * @l: linked list
    * @value: value to add to the list
    *
    * @return: 0 if success, 1 otherwise
    */
   if (list == NULL){
       return 1;
   }
    node_t *n = init_node(value);
    if (n == NULL){
        return 1;
    }
    list->size = list->size + 1;
    if (list->first != NULL){
        n->next = list->first;
    }
    list->first = n;
    return 0;
}

int main(int argc, char const *argv[])
{
    list_t l = {NULL, 0};
    add_node(&l, 5);
    printf("%d, %d\n", l.first->value, l.size);
    add_node(&l, 7);
    printf("%d, %d\n", l.first->value, l.size);
    add_node(&l, 15);
    printf("%d, %d\n", l.first->value, l.size);
    return 0;
}
