#include "encryption.h"

void encrypt(std::string_view key, std::string &data) {
    for (unsigned i = 0; i < data.size(); i++) {
        data[i] ^= key[i % key.size()];
    }
}

void decrypt(std::string_view key, std::string &data) {
    for (unsigned i = 0; i < data.size(); i++) {
        data[i] ^= key[i % key.size()];
    }
}
