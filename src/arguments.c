#include <stdio.h>

int main(int argc, char **argv)
{
    int i = 1;
    while (i<argc){
        if (i+2>=argc){
            printf("%s", *(argv+i));
        }else{
            printf("%s ", *(argv+i));
        }
        i+=2;
    }
    printf("\n");
    return 0;
}
