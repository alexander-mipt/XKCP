#include "../sha3algo.hpp"
#include "../input_output_utils.hpp"

const int HASH_SIZES_COUNT = 4;


int main(int argc, char** argv) {
    char input_file[40] = "test_in.txt";
    char output_file[40] = "test_result.txt";
    int hash_sizes[HASH_SIZES_COUNT] = {224, 256, 384, 512};
    unsigned char output[512 >> 3] = {0};

    std::vector<std::string> lines = read_input(input_file);
    printf("%s read\n", input_file);

    std::vector<std::string> hashes;
    hashes.resize(lines.size() * HASH_SIZES_COUNT);

    for (size_t i = 0; i < lines.size(); ++i) {
        char *c_str = (char *)malloc(lines[i].size());
        for (size_t j = 0; j < lines[i].size(); ++j) {
            c_str[j] = lines[i][j];
        }
        for (size_t j = 0; j < HASH_SIZES_COUNT; j++) {
            int hash_size = hash_sizes[j];
            Keccak(1600 - (hash_size << 1), (hash_size << 1), (const unsigned char*)c_str, lines[i].size(), 0x06, output, hash_size >> 3);
            hashes[HASH_SIZES_COUNT * i + j].assign((const char *)output, hash_size >> 3);
        }
        free(c_str);
    }

    write_output_hex(output_file, hashes);
    printf("%s finished\n", output_file);
}