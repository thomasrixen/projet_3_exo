#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
/*
 * @pre 0<= pos < 64
 */
uint64_t set_bit(uint64_t x, int pos, bool value) {
    if (value) {
        return x | (value << pos);
    }
    return (~(1 << pos)) & x;

}


uint8_t nbits(uint32_t n) {
    int count = 0;
    for (int i = 0; i < 31; i++) {
        count += ((1 << i) & n) >> i;
    }
    return count;
}

uint32_t reset_highestorder_strong_bit(uint32_t x) {
    for (int i = 0; i < 31; i++) {
        if (1<<(31-i) & x){
            return x & ~(1<<(31-i));
        }
    }
    return 0;
}

uint8_t get_4_rightmost_bits(uint32_t x) {
    return x & (15);
}

uint8_t get_3_leftmost_bits(uint32_t x) {
    return x>>29;
}

uint32_t cycle_bits(uint32_t x, uint8_t n) {
    return x << n | x >> (32-n);
}
int main(int argc, char const *argv[])
{
    /* code */
    int x = 16;
    printf("%d\n", cycle_bits(x, 1));
    return 0;
}
