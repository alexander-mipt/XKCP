#include "sha3algo.hpp"
#include <cstdio>
#include <cassert>
#include <cstring>
#include "fileio.hpp"
#include <unistd.h>


#define HASH_SIZE 224

unsigned int g_bit_changes[HASH_SIZE] = {0};
unsigned int g_iterations = 0;
unsigned int g_changes_total = 0;

void calculate_bit_diff(const unsigned char* hash, const unsigned char* hash0) {
    
    for (int byte_idx = 0; byte_idx < HASH_SIZE / 8; ++byte_idx) {
        // calculate diff
        unsigned char byte = hash0[byte_idx] ^ hash[byte_idx];
        
        for (int bit_idx = 0; bit_idx < 8; ++bit_idx) {
            unsigned char bit = (byte >> bit_idx) & 0x1;
           
            // register diff           
            if (bit == 1) {
                g_bit_changes[byte_idx * 8 + bit_idx]++;
                g_changes_total++;
            }
        }
    }
    g_iterations++;
}

int save_hash_result(int fd, const unsigned char* input, const size_t inByteLen, const unsigned char* hash, const size_t hashByteLen) {
    ssize_t bytes = 0;
    // printf("%.*s", inByteLen, input);
    bytes = write(fd, input, inByteLen);
    if (bytes != inByteLen) {
        return -1;
    }
    // printf("%.*s\n", hashByteLen, hash);
    bytes = write(fd, hash, hashByteLen);
    bytes += write(fd, "\n", 1);
    if (bytes != hashByteLen + 1) {
        return -1;
    }
    return 0;
}



void dump_test_results() {
    printf("bit changes\n");
    for (int i = HASH_SIZE - 1; i >= 0; --i) {
        printf("%u ", g_bit_changes[i]);
    }
    printf("\n");
    printf("average avalanche:\n");
    printf("%f\n", 1. * g_changes_total / (g_iterations * HASH_SIZE));
    printf("iterations total\n%u\n", g_iterations);
}

ssize_t len_without_newline(const char* buf, const size_t max_len) {
    char* newline = (char*)memchr(buf, '\n', max_len);
    if (newline == nullptr)
        return -1;
    
    return newline - buf;
}

int main() {
    unsigned char* hash0 = (unsigned char*)calloc(HASH_SIZE / 8, sizeof(unsigned char));
    unsigned char* hash = (unsigned char*)calloc(HASH_SIZE / 8, sizeof(unsigned char));
    int hash_fd = open("hash_log.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);

    // read input as strings ended with newline
    fileio::ReadOnly f("avalanche_effect.txt", 0);
    char* ptr = (char*)f.getSegment();
    const size_t seg_size = f.getSegSize();
    unsigned int seg_num = 0;

    // input string
    char* start = ptr;
    ssize_t len0 = 0;
    // rest of input string (from prev seg)
    char* tmp = nullptr;
    size_t rest_len = 0;

    size_t newlines = 0;


    while(ptr != nullptr) {
        newlines++;
        // printf("here\n");
        // loaded bytes from cur segment
        size_t loaded = 0;
        // printf("here\n");
        // compute 1st string (or tail of string from prev segment)
        ssize_t len = len_without_newline((char*)ptr, seg_size);
        // printf("here\n");
        if (len == -1) {
            printf("error: string without newline\n");
            exit(-1);
        }

        char* input = nullptr;
        if (rest_len != 0) {
            printf("!!!!!here?\n");
            char* input = (char*)calloc(len + rest_len + 1, sizeof(char));
            assert(input != nullptr);
            assert(tmp != nullptr);
            // printf("?here?\n");
            assert(memcpy(input, tmp, rest_len) == input);
            // printf("?here?\n");
            assert(memcpy(input + rest_len, (char*)ptr, len + 1) == input + rest_len);
            printf("%u, %.*s",len + rest_len + 1, len + rest_len + 1, input);
            // printf("?here?\n");
            free(tmp);
            tmp = nullptr;
            start = input;
            printf("?here?\n");
        } else {
            printf("?here__\n");
            start = ptr;
        }

        loaded += (len + 1);
        printf("here??\n");
        if (seg_num == 0) {
            SHA3_FUNC(224, (const unsigned char*)start, (int)(len + rest_len), hash0);
            //save_hash_result(hash_fd, (const unsigned char*)start, (int)(len + rest_len + 1), hash0, HASH_SIZE / 8);
            write(hash_fd, (unsigned char*)start, len + rest_len + 1);
        } else {
            printf("here???\n");
            assert(start != nullptr);
            SHA3_FUNC(224, (const unsigned char*)start, (int)(len + rest_len), hash);
            // printf("here????\n");
            // do analysis
            if (len == len0) {
                calculate_bit_diff(hash, hash0);
            }
            // printf("here???\n");
            // dump input & hash
            // save_hash_result(hash_fd, (const unsigned char*)start, (int)(len + rest_len + 1), hash, HASH_SIZE / 8);
            write(hash_fd, (unsigned char*)start, len + rest_len + 1);
            printf("%u, %.*s",len + rest_len + 1, len + rest_len + 1, start);
            // dump avalanche stat

            // save prev result
            memcpy(hash0, hash, HASH_SIZE / 8);
        }
        
        
        // clear rest for new segment processing
        ssize_t len0 = len + rest_len;
        rest_len = 0;
        start = ptr;
        if (input != nullptr) {
            free(input);
        }   

        printf("nl: %u\n", newlines);   
        
        while (loaded < seg_size) {
            // printf("here\n");
            start += (len + 1); 
            len = len_without_newline(start, seg_size - loaded); 
            
            if (len == -1) {
                rest_len = seg_size - loaded;
                loaded = seg_size;
                continue;
            }
            
            
            // snprintf("len: %ld\t%s", len, start);
            // printf("len: %ld\t%.*s\n", len, (int)len, start);
            // print_hash(224, (const unsigned char*)start, len);
            
            //dump_hash(224, hash_224);
            
            loaded += (len + 1);

            SHA3_FUNC(224, (const unsigned char*)start, (int)(len), hash);
            newlines++;
            // do analysis
            if (len == len0) {
                calculate_bit_diff(hash, hash0);
            }
            // dump input & hash
            // save_hash_result(hash_fd, (const unsigned char*)start, (int)(len + 1), hash, HASH_SIZE / 8);
            write(hash_fd, (unsigned char*)start, len + 1);
            printf("%u, %.*s",len + 1, len + 1, start);
            // dump avalanche stat
            // save prev result
            memcpy(hash, hash0, HASH_SIZE / 8);
            len0 = len;

            //assert(newlines < 479);
            // printf("nl: %u\n", newlines);
        }

        // save rest of prev segment
        if (rest_len > 0) {
            tmp = (char*)calloc(rest_len, sizeof(char));
            assert(tmp != nullptr);
            assert(memcpy(tmp, start, rest_len) == tmp);
            printf("rest: %d\n", rest_len);
        }

        // load next file segment
        printf("next seg\n");
        ptr = (char*)f.nextSegment();
        printf("next seg!\n");
        seg_num++;
    }

    dump_test_results();

    printf("\n\n\n");
    print_hash(224, (const unsigned char*)"sasha", 0);
    print_hash(224, (const unsigned char*)"savsha", 0);
    print_hash(224, (const unsigned char*)"sabsfba", 0);
    print_hash(224, (const unsigned char*)"sasbdfna", 0);
    print_hash(224, (const unsigned char*)"", 0);
    print_hash(224, (const unsigned char*)"", 0);
    print_hash(224, (const unsigned char*)"", 1);
    print_hash(224, (const unsigned char*)"\0", 1);
    unsigned char zero = '\0';
    print_hash(224, &zero, 1);

}