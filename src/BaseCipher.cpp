#include "BaseCipher.hpp"

std::string BaseCipher::reverse_cipher() {
    std::string rev(ALPHABET.length(), '\0');
    for (size_t i = 0; i < ALPHABET.length(); i++)
        rev[i] = ALPHABET[this->cipher.find(ALPHABET[i])];
    return rev;
}

size_t BaseCipher::base26(size_t num) {
    return (ALPHABET.length() + num) % ALPHABET.length();
}

void BaseCipher::step() {};