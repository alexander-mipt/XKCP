#include "sha3algo.hpp"
#include <cstdio>
#include <cassert>
#include <cstring>
#include "fileio.hpp"

void dump_hash(const unsigned bits_len, const unsigned char *hash) {
  const unsigned size = bits_len >> 3;
  for (unsigned i = 0; i < size; ++i) {
    printf("%02x ", hash[i]);
  }
  putchar('\n');
}

void print_hash(const unsigned hashBitlen, const unsigned char* input, const unsigned inputBytelen) {
    if (!(hashBitlen == 224 || hashBitlen == 256 || hashBitlen == 384 || hashBitlen == 512)) {
        printf("hash error\n");
        return;
    }

    printf("input len: %u(%u)\nhash len: %u(%u)\n", inputBytelen, inputBytelen * 8, hashBitlen >> 3, hashBitlen);
    unsigned char* hash = (unsigned char*)calloc(hashBitlen >> 3, sizeof(unsigned char));
    assert(hash != nullptr);
    
    switch(hashBitlen) {
        case 224:
            SHA3_FUNC(224, input, inputBytelen, hash);
            break;
        case 256:
            SHA3_FUNC(256, input, inputBytelen, hash);
            break;
        case 384:
            SHA3_FUNC(384, input, inputBytelen, hash);
            break;
        case 512:
            SHA3_FUNC(512, input, inputBytelen, hash);
            break;
        default:
            printf("hash error\n");
    }
    
    
    dump_hash(224, hash);

}

ssize_t len_without_newline(const char* buf, const size_t max_len) {
    char* newline = (char*)memchr(buf, '\n', max_len);
    if (newline == nullptr)
        return -1;
    
    return newline - buf;

}

int main() {
    fileio::ReadOnly f("avalanche_effect.txt", 0);
    unsigned char* hash_224 = (unsigned char*)calloc(64, sizeof(unsigned char));
    char* ptr = (char*)f.getSegment();
    while(ptr != nullptr) {
        size_t loaded = 0;
        ssize_t len = 0;
        char* start = ptr;
        
        while (loaded < f.getSegSize() && len != -1) {
            len = len_without_newline(start, f.getSegSize());
            loaded += (len + 1);
            // snprintf("len: %ld\t%s", len, start);
            printf("len: %ld\t%.*s\n", len, (int)len, start);
            print_hash(224, (const unsigned char*)start, len);
            //SHA3_FUNC(224, (const unsigned char*)start, (int)len, hash_224);
            //dump_hash(224, hash_224);
            start += (len + 1);
        }

        ptr = (char*)f.nextSegment();
    }

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