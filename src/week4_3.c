#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node{
    char val;
    struct node *next;
} node_t;


int compare(char a, char b) {
    /*
    * @return: 0 if equals, negative number if @b is greater,
    * and positive number otherwise
    */
   return a-b;
}


int insert(node_t **head, char val, int (*cmp)(char,char)) {
    /*
    * @value: value to be inserted. If the value is already in the list, no element is added and the list is not modified
    * @fun: comparison function which defines the order relationship of the list
    * @head: first node of the list, head != NULL
    * @return: 0 if success, -1 otherwise
    */
    node_t *new;
    if (*head==NULL || cmp((*head)->val, val)>0 ){
        new = malloc(sizeof(node_t));
        if (new==NULL) return -1;
        new->val = val;
        new->next = *head;
        *head = new;
        return 0;
    }
    if (cmp((*head)->val, val)==0){
        return 0;
    }
    node_t *act = *head;
    while (act->next != NULL){
        if (cmp(act->next->val, val) == 0) return 0;
        else if (cmp(act->next->val, val)>0){
            new = malloc(sizeof(node_t));
            if (new==NULL) return -1;
            new->val = val;
            new->next = act->next;
            act->next = new;
            return 0;
        }
        act = act->next;
    }
    new = malloc(sizeof(node_t));
    if (new==NULL) return -1;
    new->val = val;
    new->next = NULL;
    act->next = new;
    return 0;
}

int main(int argc, char const *argv[])
{
    node_t **head = malloc(sizeof(node_t));
    insert(head, 5, &compare);
    printf("%d\n", (*head)->val);
    insert(head, 4, &compare);
    printf("%d\n", (*head)->val);
    insert(head, 6, &compare);
    printf("%d\n", (*head)->next->next->val);
    return 0;
}
