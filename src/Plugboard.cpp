#include "Plugboard.hpp"

Plugboard::Plugboard() {
    this->name = "Plugboard";
    this->cipher = ALPHABET;
}

Plugboard::Plugboard(const Plugboard &p) {
    this->name = p.name;
    this->cipher = p.cipher;
}

char Plugboard::encipher(char letter, bool forward) {
    const size_t i = ALPHABET.find(letter);
    return forward ? this->next->encipher(this->cipher[i]) : this->cipher[i];
}

void Plugboard::swap(char first, char second) {
    const size_t f = ALPHABET.find(first);
    const size_t s = ALPHABET.find(second);
    this->unswap(first);
    this->unswap(second);
    const char temp = ALPHABET[f];
    this->cipher[f] = this->cipher[s];
    this->cipher[s] = temp;
}

void Plugboard::unswap(char letter) {
    const size_t ai = ALPHABET.find(letter);
    const size_t i = this->cipher.find(letter);
    const char temp = this->cipher[ai];
    this->cipher[ai] = this->cipher[i];
    this->cipher[i] = temp;
}