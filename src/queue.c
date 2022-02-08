#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
  struct node* next;
  int value;
} node_t;

typedef struct queue{
  struct node* tail;
  int size;
} queue_t  ;


int enqueue(queue_t* q, int val){
    /*
    * Add @val value at the head of the @q queue
    *
    * @val     : the value to enqueue
    * @q     : the queue
    *
    * @return 0 if no error, -1 otherwise
    *
    * pre : The queue q will always be valid, you don't need to handle the NULL case.
    */
   node_t *n = malloc(sizeof(node_t));
   if (n==NULL){
       return -1;
   }
   n->value = val;
   if (q->size == 0){
       q->tail = n;
       n->next = n;
   }else{
       n->next = q->tail->next;
       q->tail->next = n;
   }
   q->size++;
   return 0;
}


int dequeue(queue_t* q){
    /*
    * Remove the node at the tail of the @q queue and return the value of this node
    * @q         : the queue
    * @return     : the value at the tail
    *
    * pre         : The given queue will always be valid, you do not need to handle the NULL case.
    */
    q->size--;
    int i = q->tail->value;
    if (q->size==0){
        free(q->tail);
        q->tail = NULL;
        return i;
    }
    node_t *n = q->tail;
    for (int i = 0; i < q->size; i++)
    {
        n = n->next;
    }
    n->next = q->tail->next;
    free(q->tail);
    q->tail = n->next;
    return i; 
}

int main(int argc, char const *argv[])
{
    queue_t q = {NULL, 0};
    enqueue(&q, 4);
    printf("%d, %d\n", (&q)->size, (&q)->tail->value);
    enqueue(&q, 6);
    printf("%d, %d, %d\n", (&q)->size, (&q)->tail->value, q.tail->next->value);
    int i = dequeue(&q);
    printf("%d, %d ,%d\n", (&q)->size ,(&q)->tail->value, i);
    dequeue(&q);
    return 0;
}
