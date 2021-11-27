extern "C"
{
#include "SimpleFIPS202.h"
#include "stdio.h"
}

int main() {
    const unsigned char input[] = "HACKERS from 115";
    const size_t input_size = sizeof(input);
    const size_t output_size = 64;
    unsigned char output[output_size] = {0};
    
    SHA3_224(output, input, input_size);

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