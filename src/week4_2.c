#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct node {
    struct node *next;
    int hash;
};

struct node *pair_filter(struct node *head) {

    /* pair_filter
    * Make a copy of the linked list starting at head,
    * only taking the elements with an even index
    *
    * @head : head of a linked list, possibly NULL
    * @return: pointer to the filtered linked list, return NULL if error or if head == NULL
    */
    if (head == NULL || head->next == NULL){
        return NULL;
    }
    int i = 1;
    struct node *res;
    struct node *n = malloc(sizeof(struct node));
    if (n==NULL) return NULL;
    memcpy(n, head->next, sizeof(struct node));
    res = n;
    struct node *actual = res;
    head = head->next;
    while (head != NULL) {
        head = head->next;
        i++;
        if (i%2 != 0){
            n = malloc(sizeof(struct node));
            if (n==NULL) return NULL;
            memcpy(n, head, sizeof(struct node));
            actual->next = n;
            actual = actual->next;
        }
    }
    actual->next = NULL;
    return res;
}

int main(int argc, char const *argv[])
{
    struct node c = {NULL, 1};
    struct node b = {NULL, 2};
    struct node a = {NULL, 3};
    struct node d = {NULL, 4};
    c.next = &b;
    b.next = &a;
    a.next = &d;
    struct node *res = pair_filter(&c);
    printf("%d, %d", res->hash, res->next->hash);
    return 0;
}
