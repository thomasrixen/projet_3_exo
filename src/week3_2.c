#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct node{
    /*
    * Node has a value, @value, and two children, @left and @right.
    * All the children of @left and itself have a smaller value than the node and all the children of @right and itself have a larger value than node
    */
    int value;
    struct node* left; // to smaller values
    struct node* right; // to larger values
} node_t;

typedef struct bt{
    struct node* root;
} bt_t;

/*
* Return 1 if there is a node containing @value in @tree and 0 otherwise.
*/
int contains(bt_t* tree, int value){
    if (tree == NULL){
        return 0;
    }
    node_t *n = tree->root;
    return nodeContains(n, value);
}

int nodeContains(node_t *n, int value){
    if (n == NULL){
        return 0;
    }
    else if (n->value == value){
        return 1;
    }
    else if (n->value > value){
        return nodeContains(n->left, value);
    }
    else{
        return nodeContains(n->right, value);
    }
}

typedef struct product {
    char *name;
    double price;
} product_t;

double getPtrPrice(product_t *ptrProd){
    /*
    * @ptrProd != NULL
    * @return: the price of the product ptrProd
    */
   return ptrProd->price;
}


double getPrice(product_t prod){
    /*
    * @return: the price of the product prod
    */
   return prod.price;
}


char* getPtrName(product_t *ptrProd){
    /*
    * ptrProd != NULL
    * @name in ptrProd != NULL
    * @return: a string on the heap that contains the name of the product ptrProd or NULL if an error happens
    */
   char *s = malloc((strlen(ptrProd->name) + 1)*sizeof(char));
   if (s == NULL){
       return NULL;
   }
   strcpy(s, ptrProd->name);
   return s;
}


char* getName(product_t prod){
    /*
    * @name in prod != NULL
    * @return: a string on the heap that contains the name of the product ptrProd or NULL if an error happens
    */
    char *s = malloc((strlen(prod.name) + 1)*sizeof(char));
    if (s == NULL){
       return NULL;
    }
    strcpy(s, prod.name);
    return s;
}


int prodEquals(product_t *ptrProd, product_t prod){
    /*
    * @ptrProd != NULL
    * @name in ptrProd != NULL
    * @name in prod != NULL
    * @return: 1 if the two products are the same, i.e., they have the same price and the same name
    */
   return ((ptrProd->price == prod.price) && (strcmp(ptrProd->name, prod.name) == 0));
}


