#include <cstring>
#include "sha3algo.hpp"
#include "../../input_output_utils.hpp"


int main(int argc, char** argv) {
    char input_file[40];
    char output_file[60];

    int hash_size = strtol(argv[2], NULL, 10);
    int rounds = strtol(argv[3], NULL, 10);


    sprintf(output_file, "../data/%s_output_%d_%d.txt", argv[1], hash_size, rounds);


    sprintf(input_file, "%s", argv[1]);
    sprintf(input_file + strlen(input_file), ".txt");

    unsigned char output[hash_size >> 3] = {0};
    
    std::vector<std::string> lines = read_input_hex(input_file);
    printf("%s read\n", input_file);

    std::vector<std::string> hashes;
    hashes.resize(lines.size());

    for (size_t i = 0; i < lines.size(); ++i) {
        char *c_str = (char *)malloc(lines[i].size());
        for (size_t j = 0; j < lines[i].size(); ++j) {
            c_str[j] = lines[i][j];
        }
        Keccak_Dev(1600 - (hash_size << 1), (hash_size << 1), (const unsigned char*)c_str, lines[i].size(), 0x06, output, hash_size >> 3, rounds);
        hashes[i].assign((const char *)output, hash_size >> 3);
        free(c_str);
        // if (i % 100000 == 0) {
        //     printf("i = %ld\t\t", i);
        //     fflush(0);
        // }
    }


    write_output_bin(output_file, hashes);
    printf("\n%s finished\n", output_file);


}
