#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>


uint8_t get_3_leftmost_bits(uint32_t x) {
    return (x & (7<<29))>>29;
}

uint8_t get_4_rightmost_bits(uint32_t x) {
    return x & 0b1111;
}


/*
 * @pre 0<= pos < 64
 */
uint64_t set_bit(uint64_t x, int pos, bool value) {
    if (value){
        return x | (1<<pos);
    }
    return ~(1<<pos) & x;
}

uint32_t cycle_bits(uint32_t x, uint8_t n) {
    return (x << n) | (x >> (32-n));
}

#include <stdint.h>
uint8_t nbits(uint32_t n) {
    int i =0;
    int count = 0;
    while ((1<<i) <= n){
        count += ((1<<i) & n)>>i;
        i++;
    }
    return count;
}

uint32_t reset_highestorder_strong_bit(uint32_t x) {
    int i = 1;
    while((1<<i) <= x){
        i++;
    }
    return x & ~(1<<(i-1));
}

int main(int argc, char const *argv[])
{
    printf("%d\n", reset_highestorder_strong_bit(atoi(argv[1])));
    return 0;
}
