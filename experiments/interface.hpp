#include "sha3algo.hpp"
#include <functional>

using sha3_func = std::function<void(const unsigned char *input, unsigned int inputByteLen, unsigned char *output)>;

sha3_func get_sha3(size_t hash_size) {
    switch (hash_size) {
        case 224:
            return FIPS202_SHA3_224;
        case 256:
            return FIPS202_SHA3_256;
        case 384:
            return FIPS202_SHA3_384;
        case 512:
            return FIPS202_SHA3_512;
        default:
            return nullptr;
    }
}

