#include <stdlib.h>
#include <stdio.h>

int absval(int i) {
    return i>=0 ? i : -i;
    /*
    if (i>=0){
        return i;
    }
    return -i;
    */

}

int factorial(int n){
    if (n==0){
        return 1;
    }
    return n*factorial(n-1);
}

/* tab_find

@tab : an array of int
@len : the number of int in tab
@elem : the elem looked for
@return : return the index at which elem is found, else returns -1 if not found. */
int tab_find(int tab[], int len, int elem){
    for (int i = 0; i < len; i++)
    {
        if (tab[i] == elem){
            return i;
        }
    }
    return -1;
}

int fi(int *tab, int len, int elem){
    for (int i = 0; i < len; i++)
    {
        if (*(tab+i)==elem) return i;
    }
    return -1;
    
}

int f()
{
    int a = 1252;
    printf("%d\n", a);
    return 0;
}

int main(int argc, const char *argv[])
{
    int arg[] = {0,1,2,3,4};
    printf("%p\n", arg);
    printf("%d\n", fi(arg, 5, 2));
}
