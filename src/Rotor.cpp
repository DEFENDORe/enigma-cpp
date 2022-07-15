#include "Rotor.hpp"
#include <stdexcept>

const size_t Rotor::COUNT = 8;

Rotor Rotor::rotors[Rotor::COUNT] = {
    Rotor("I", "EKMFLGDQVZNTOWYHXUSPAIBRCJ", "Q"),
    Rotor("II", "AJDKSIRUXBLHWTMCQGZNPYFVOE", "E"),
    Rotor("III", "BDFHJLCPRTXVZNYEIWGAKMUSQO", "V"),
    Rotor("IV", "ESOVPZJAYQUIRHXLNFTGKDCMWB", "J"),
    Rotor("V", "VZBRGITYUPSDNHLXAWMJQOFECK", "Z"),
    Rotor("VI", "JPGVOUMFYQBENHZRDKASXLICTW", "ZM"),
    Rotor("VII", "NZJHGRCXMYSWBOUFAIVLPEKQDT", "ZM"),
    Rotor("VIII", "FKQHTLXOCBJSPDZRAMEWNIUYGV", "ZM")
};

Rotor Rotor::SelectRotor(std::string name, char position, char ring) {
    Rotor selected;
    size_t _position = position < 0 || position > 25 ? ALPHABET.find(position) : position;
    size_t _ring = ring < 0 || ring > 25 ? ALPHABET.find(ring) : ring;
    bool found = false;
    if (_position == std::string::npos)
        throw std::invalid_argument("Rotor::SelectRotor - Invalid position provided. (0-25/A-Z)");
    if (_ring == std::string::npos)
        throw std::invalid_argument("Rotor::SelectRotor - Invalid ring provided. (0-25/A-Z)");
    for (size_t i = 0; i < Rotor::COUNT; i++) {
        if (Rotor::rotors[i].name == name) {
            found = true;
            selected = Rotor::rotors[i];
            selected.setPosition(_position);
            selected.setRing(_ring);
            break;
        }
    }
    if (!found)
        throw std::invalid_argument("Rotor::SelectRotor - Invalid rotor name provided.");
    return selected;
}

Rotor::Rotor() {}

Rotor::Rotor(std::string name, std::string cipher, std::string notch, size_t position, size_t ring) {
    this->name = name;
    this->cipher = cipher;
    this->notch = notch;
    this->position = position;
    this->ring = ring;
    this->offset = base26(this->position - this->ring);
}

Rotor::Rotor(const Rotor &r) {
    this->name = r.name;
    this->cipher = r.cipher;
    this->notch = r.notch;
    this->position = r.position;
    this->ring = r.ring;
    this->offset = r.offset;
}

bool Rotor::isOnNotch() {
    return this->notch.find(ALPHABET[this->position]) != std::string::npos;
}

void Rotor::step() {
    if (this->next != nullptr && this->isOnNotch())
        this->next->step();
    this->offset = base26(++this->offset);
    this->position = base26(this->offset + this->ring);
}

char Rotor::encipher(char letter, bool forward) {
    size_t i = base26(ALPHABET.find(letter) + this->offset);
    char l = forward ? this->cipher[i] : this->reverse_cipher()[i];
    l = ALPHABET[base26(ALPHABET.find(l) - this->offset)];
    if (forward)
        return this->next->encipher(l, forward);
    else
        return this->prev->encipher(l, forward);
}

void Rotor::setPosition(size_t position) {
    this->position = position;
    this->offset = base26(this->position - this->ring);
}

void Rotor::setRing(size_t ring) {
    this->offset = base26(this->position + this->ring);
    this->ring = ring;
    this->position = this->offset;
    this->offset = base26(this->position - this->ring);
}