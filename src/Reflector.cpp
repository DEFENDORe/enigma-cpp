#include "Reflector.hpp"
#include <stdexcept>

const size_t Reflector::COUNT = 2;

Reflector Reflector::reflectors[Reflector::COUNT] = {
    Reflector("B", "YRUHQSLDPXNGOKMIEBFZCWVJAT"),
    Reflector("C", "FVPJIAOYEDRZXWGCTKUQSBNMHL")
};


Reflector Reflector::SelectReflector(std::string name) {
    Reflector selected;
    bool found = false;
    for (size_t i = 0; i < Reflector::COUNT; i++) {
        if (Reflector::reflectors[i].name == name) {
            found = true;
            selected = Reflector::reflectors[i];
            break;
        }
    }
    if (!found)
        throw std::invalid_argument("Reflector::SelectReflector - Invalid reflector name provided.");
    return selected;
}

Reflector::Reflector() {}

Reflector::Reflector(std::string name, std::string cipher) {
    this->name = name;
    this->cipher = cipher;
}

Reflector::Reflector(const Reflector &r) {
    this->name = r.name;
    this->cipher = r.cipher;
}

char Reflector::encipher(char letter, bool forward) {
    size_t index = ALPHABET.find(letter);
    char l = this->cipher[index];
    return this->prev->encipher(l, false);
}
