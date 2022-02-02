#include <stdio.h>
#include <string.h>

/* print_digit
 * @n: an integer
 *
 * result: print to stdout "The magic number is NUMBER.\n"
 */
void print_digit(int number) {
    printf("The magic number is %d.\n", number);
}

void print_foo() {
    printf("foo\n");
}

void format_str(char *buffer, unsigned int d, char *name, char initial) {
    sprintf(buffer, "Mister %s %c has %d eggs", name, initial, d);
}

char* strcat(char* dest, const char* src) {
    char temp[100];
    return dest;
}

size_t strlen(const char* s) {
    int i = 0;
    while (*(s+i) != '\0'){
        i++;
    }
    return i;
}

int strcasecmp(const char *s1, const char *s2) {
    int i = 0;
    while (*(s1+i) != '\0' || *(s2+i) != '\0'){
        if (*(s2+i) == '\0'){
            return 1;
        }
        if (*(s1+i)== '\0'){
            return -1;
        }

        char a = *(s1+i);
        if (*(s1+i) >= 'A' && *(s1+i) <='Z'){
            a = a - 'A' + 'a';
        }

        char b = *(s2+i);
        if (*(s2+i) >= 'A' && *(s2+i) <='Z'){
            b = b - 'A' + 'a';
        }
        
        if (a < b){
            return -1;
        }
        else if (a > b){
            return 1;
        }
        i++;
    }
    return 0;
}


/*
* @return: returns true (1) if str is a palindrome, -1 if str is NULL, otherwise false (0).
*/
int pal(char *str) {
    if (str == NULL){
        return -1;
    }
    int i = 0;
    int j = strlen(str) -1;
    while (i<j){
        while (*(str+i) == ' '){
            i++;
        }
        while (*(str+j) == ' '){
            j--;
        }
        if (i>=j) return 1;
        if (*(str+i) != *(str+j)){
            return 0;
        }
        j--;
        i++;
    }
    return 1;
}

void swap(int *i, int *j) {
    int temp = *i;
    *i = *j;
    *j = temp;
}

struct fract_t {
        int num;
        int denum;
};

void swap2(struct fract_t *a, struct fract_t *b){
    struct fract_t temp = *b;
    b->num = a->num;
    b->denum = a->denum;
    a->num = temp.num;
    a->denum = temp.denum;
}

int main(int argc, char const *argv[])
{
    struct fract_t a = {1,2};
    struct fract_t b = {3,4};
    swap2(&a,&b);
    printf("%d %d\n", a.num, a.denum);
    printf("%d %d\n", b.num, b.denum);
    return 0;
}
