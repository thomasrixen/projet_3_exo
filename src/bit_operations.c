#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

uint8_t get_3_leftmost_bits(uint32_t x) {
    return x >> 29;
}

uint8_t get_4_rightmost_bits(uint32_t x) {
    return (x << 28) >> 28;
}

uint64_t set_bit(uint64_t x, int pos, bool value) {
    if (value){
        uint64_t res = 1;
        for (int i = 0; i<pos; i++){
            res = res*2;
        }
        return x | res;
    }else{
        uint64_t res = 1;
        for (int i = 0; i<pos; i++){
            res = res*2;
        }
        return x - res;
    }
    
}


uint32_t cycle_bits(uint32_t x, uint8_t n) {
    int res[32];
    int copy[32];
    int pow = 1;
    for (int i = 0; i<32; i++){
        res[i] = x%2;
        copy[i] = x%2;
        x = x/2;
    }
    for (int i = 0; i<32; i++){
        res[(i+n)%32] = copy[i];
    }
    uint32_t ret = 0;
    pow = 1;
    for (int i = 0; i<32;i++){
        ret += res[i]*pow;
        pow*=2;
    }
    return ret;
}

uint8_t nbits(uint32_t n) {
    int res = 0;
    for (int i = 0; i<32; i++){
        res += n%2;
        n = n/2;
    }
    return res;
}

uint32_t reset_highestorder_strong_bit(uint32_t x) {
    uint32_t pow = 1;
    for (int i = 0; i<31;i++){
        pow*=2;
    }
    for (int i = 0; i<32;i++){
        if (pow<=x){
            return x-pow;
        }
        pow/=2;
    }
    return x;
}

void printBit(int x){
    int res[32];
    for (int i = 0; i<32; i++){
        res[i] = x%2;
        x = x/2;
    }
    for (int i = 31; i>=0; i--){
        printf("%d ", res[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    uint32_t x = 1;
    printBit(x);
    printBit(reset_highestorder_strong_bit(x));
    return 0;
}
