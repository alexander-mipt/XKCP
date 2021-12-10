#include "sha3algo.hpp"
#include <cstdio>
#include <cassert>
#include <cstring>
#include "fileio.hpp"
#include <unistd.h>
#include <cstdint>


#define HASH_SIZE 224

size_t g_bit_changes_total[HASH_SIZE] = {0};
size_t g_changes_total = 0;
size_t g_iterations_total = 0;

size_t g_bit_changes_local[HASH_SIZE] = {0};
size_t g_changes_local = 0;
size_t g_iterations_local = 0;

void collect_bit_stat(const unsigned char* hash, const unsigned char* hash0) {
    
    for (int byte_idx = 0; byte_idx < HASH_SIZE / 8; ++byte_idx) {
        // calculate diff
        unsigned char byte = hash0[byte_idx] ^ hash[byte_idx];
        
        for (int bit_idx = 0; bit_idx < 8; ++bit_idx) {
            unsigned char bit = (byte >> bit_idx) & 0x1;
           
            // register diff           
            if (bit == 1) {
                g_bit_changes_local[byte_idx * 8 + bit_idx]++;
                g_changes_local++;
            }
        }
    }
    g_iterations_local++;
    g_iterations_total++;
}

int flush_bit_stat(int fd, size_t inLenBits, bool bit_stat) {
    if (g_iterations_local == 0)
        return -1;

    if (fd >= 0) {
        // idx | iterations | changes per iter (av %) |
        assert(dprintf(fd, "\n%6lu\t%6lu\t%6lu\t%8.3f\t|\t", g_iterations_total, inLenBits, g_iterations_local, 1. * g_changes_local / (g_iterations_local * HASH_SIZE)) > 0);
    }
    
    for (int bit_idx = 0; bit_idx < HASH_SIZE; ++ bit_idx) {
        
        if (fd >= 0 && bit_stat) {
            // bit changes (av %) | ... |
           assert(dprintf(fd, "%8.3f ", 1. * g_bit_changes_local[bit_idx] / g_iterations_local) > 0); 
        }
        

        g_bit_changes_total[bit_idx] += g_bit_changes_local[bit_idx];
        g_bit_changes_local[bit_idx] = 0;
    }
    
    g_changes_total += g_changes_local;
    g_changes_local = 0;

    g_iterations_local = 0;
    // g_iterations_global is incremented in collect_bit_stat

    return 0;
}

int dump_global_stat(int fd, bool bit_stat) {
    assert(fd >= 0);
    assert(dprintf(fd, "\n%6lu\t%6s\t%6lu\t%8.3f\t|\t", g_iterations_total, "", g_iterations_total, 1. * g_changes_total / (g_iterations_total * HASH_SIZE)) > 0);
    
    for (int bit_idx = 0; bit_stat && bit_idx < HASH_SIZE; ++ bit_idx) {
        // bit changes (av %) | ... |
        assert(dprintf(fd, "%8.3f ", 1. * g_bit_changes_total[bit_idx] / g_iterations_total) > 0); 
    }
    
    dprintf(fd, "\n");
}

int save_hash_result(int fd, const unsigned char* hash) {
    assert(hash != nullptr);
    for (off_t i = 0; i < HASH_SIZE / 8; ++i) {
        assert(dprintf(fd, "%02x", hash[i]) > 0);
    }
    dprintf(fd, "\n");
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
    
    // hash log file
    int hash_fd = open("output_hash.log", O_WRONLY | O_TRUNC | O_CREAT, 0644);
    // avalanche effect stat file
    int stat_fd = open("avalanche_stat.log", O_WRONLY | O_TRUNC | O_CREAT, 0644);
    dprintf(stat_fd, "%6s\t%6s\t%6s\t%6s\t|\t%16s (%u bits)", "Idx", "InLenBits", "Itrs", "Mod", "ModPerBit", HASH_SIZE);

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

    while(ptr != nullptr) {
        // loaded bytes from cur segment
        size_t loaded = 0;
        // compute 1st string (or tail of string from prev segment)
        ssize_t len = len_without_newline((char*)ptr, seg_size);

        if (len == -1) {
            printf("error: string without newline\n");
            exit(-1);
        }

        char* input = nullptr;
        if (rest_len != 0) {
            char* input = (char*)calloc(len + rest_len + 1, sizeof(char));
            assert(input != nullptr);
            assert(tmp != nullptr);
            assert(memcpy(input, tmp, rest_len) == input);
            assert(memcpy(input + rest_len, (char*)ptr, len + 1) == input + rest_len);
            free(tmp);
            tmp = nullptr;
            start = input;
        } else {
            start = ptr;
        }

        loaded += (len + 1);
        if (seg_num == 0) {
            // get hash
            SHA3_FUNC(224, (const unsigned char*)start, (int)(len + rest_len), hash0);
            // write(hash_fd, (unsigned char*)start, len + rest_len + 1);
            save_hash_result(hash_fd, hash0);
        } else {
            assert(start != nullptr);
            // get hash
            SHA3_FUNC(224, (const unsigned char*)start, (int)(len + rest_len), hash);
            // write(hash_fd, (unsigned char*)start, len + rest_len + 1);
            save_hash_result(hash_fd, hash);
            
            // calculate avalanche stat
            if (len + rest_len == len0) {
                collect_bit_stat(hash, hash0);
                flush_bit_stat(stat_fd, len0, false);
            }
            
            // dump avalanche stat

            // save prev result
            memcpy(hash0, hash, HASH_SIZE / 8);
        }
        
        // clear rest for new segment processing
        len0 = len + rest_len;
        rest_len = 0;
        start = ptr;
        if (input != nullptr) {
            free(input);
        }  
        
        while (loaded < seg_size) {
            start += (len + 1); 
            len = len_without_newline(start, seg_size - loaded); 
            
            if (len == -1) {
                rest_len = seg_size - loaded;
                loaded = seg_size;
                continue;
            }
            
            loaded += (len + 1);

            SHA3_FUNC(224, (const unsigned char*)start, (int)(len), hash);
            // write(hash_fd, (unsigned char*)start, len + 1);
            save_hash_result(hash_fd, hash);
            // do analysis
            if (len == len0) {
                collect_bit_stat(hash, hash0);
                flush_bit_stat(stat_fd, len0, false);
            }

            // save prev result
            memcpy(hash, hash0, HASH_SIZE / 8);
            len0 = len;
        }

        // save rest of prev segment
        if (rest_len > 0) {
            tmp = (char*)calloc(rest_len, sizeof(char));
            assert(tmp != nullptr);
            assert(memcpy(tmp, start, rest_len) == tmp);
        }

        // load next file segment
        ptr = (char*)f.nextSegment();
        seg_num++;
        printf("loaded seg: %u\n", seg_num);
    }

    dump_global_stat(stat_fd, true);
    dump_global_stat(STDOUT_FILENO, false);
/*
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
*/
}