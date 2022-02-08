#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


struct node {
    struct node *next;
    char *name;
};

/**
* Remove the top element of the stack and return its content.
*
* @head : pointer to the top of the stack
* @result : pointer to store the popped element
*
* @return 0 if no error, 1 otherwise
*
* pre : @result contains a null-terminated correct string
* post : @result contains the string @name from the element at the top of the stack
*/

int pop(struct node **head, char *result){
    if (head==NULL || *head==NULL) return 1;
    struct node *n = *head;
    if (result == NULL){
        return 1;
    }
    strcpy(result, n->name);
    *head = n->next;
    free(n->name);
    free(n);
    return 0;
}

/**
* Add @name at the "top" of the stack.
*
* @head : pointer to the top of the stack
* @name : the string to be placed in the element at the top of the stack
*
* @return 0 if no error, 1 otherwise
*/

int push(struct node **head, const char *value){
    if (head==NULL) return 1;
    struct node *n = malloc(sizeof(struct node));
    if (n==NULL) return 1;
    char *cp = malloc((strlen(value)+1)*sizeof(char));
    if (cp==NULL) return 1;
    strcpy(cp, value);
    n->name = cp;
    if (*head != NULL){
        n->next = *head;
    }
    *head = n;
    return 0;
}

uint8_t func(uint8_t x){
    return x+1;
}

uint8_t gfunc(uint8_t x){
    if (x==245){
        return 0;
    }
    return x+1;
}

int cmp_func(uint8_t (*f)(uint8_t), uint8_t (*g)(uint8_t)){
    for (int i = 0; i < 256; i++)
    {
        if (f(i) != g(i)){
            return 0;
        }
    }
    return 1;
}


int main(int argc, char const *argv[])
{
    /*
    struct node **head = malloc(sizeof(struct node));
    push(head, "Test");
    printf("%s\n", (*head)->name);
    push(head, "Encore");
    printf("%s\n", (*head)->name);
    char res[10];
    pop(head, res);
    printf("%s, %s\n", (*head)->name, res);
    pop(head, res);
    free(head);
    */
    printf("%d\n", cmp_func(&func, &gfunc));
    return 0;
    
}
