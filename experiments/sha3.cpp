#include "sha3algo.hpp"
#include <cstdio>

int main() {
    const unsigned char input[] = "HACKERS from 115";
    const size_t input_size = sizeof(input);
    const size_t output_size = 64;
    unsigned char output[output_size] = {0};
    
    FIPS202_SHA3_224(input, input_size, output);

    printf("%s\n", input);
    for (int i = 0; i < input_size; ++i) {
        printf("%x ", input[i]);
    }
    printf("\n\n");
    for (int i = 0; i < output_size; ++i) {
        printf("%x ", output[i]);
    }
    printf("\n");

}