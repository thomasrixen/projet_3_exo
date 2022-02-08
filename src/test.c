#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int eq(int a, int b){
    if (a==b){
        return 0;
    }
    return 1;
}

int ne(int a, int b){
    if (a!=b){
        return 0;
    }
    return 1;
}

int gt(int a, int b){
    if (a>b){
        return 0;
    }
    return 1;
}

int ge(int a, int b){
    if (a>=b){
        return 0;
    }
    return 1;
}

int lt(int a, int b){
    if (a<b){
        return 0;
    }
    return 1;
}

int le(int a, int b){
    if (a<=b){
        return 0;
    }
    return 1;
}

int main(int argc, char const *argv[])
{
    if (argc != 4){
        return 1;
    }
    if (strcmp(argv[2], "-eq") == 0){
        return eq(atoi(argv[1]), atoi(argv[3]));
    }
    if (strcmp(argv[2], "-ne") == 0){
        return ne(atoi(argv[1]), atoi(argv[3]));
    }
    if (strcmp(argv[2], "-lt") == 0){
        return lt(atoi(argv[1]), atoi(argv[3]));
    }
    if (strcmp(argv[2], "-gt") == 0){
        return gt(atoi(argv[1]), atoi(argv[3]));
    }
    if (strcmp(argv[2], "-le") == 0){
        return le(atoi(argv[1]), atoi(argv[3]));
    }
    if (strcmp(argv[2], "-ge") == 0){
        return ge(atoi(argv[1]), atoi(argv[3]));
    }
    return 1;
}
