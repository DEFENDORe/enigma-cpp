#include "Enigma.hpp"
#include <sstream>

void Enigma::wire() {
    this->plugboard.next = &this->right;
    this->right.prev = &this->plugboard;
    this->right.next = &this->middle;
    this->middle.prev = &this->right;
    this->middle.next = &this->left;
    this->left.prev = &this->middle;
    this->left.next = &this->reflector;
    this->reflector.prev = &this->left;
}

std::string Enigma::encipher(std::string input) {
    this->wire();
    std::string output;
    for (size_t i = 0; i < input.length(); i++) {
        input[i] = islower(input[i]) ? toupper(input[i]) : input[i];
        if (BaseCipher::ALPHABET.find(input[i]) == std::string::npos)
            continue;
        this->right.step();
        output += this->plugboard.encipher(input[i]);
    }
    return output;
}

char Enigma::encipher(char input) {
    this->wire();
    input = islower(input) ? toupper(input) : input;
    if (BaseCipher::ALPHABET.find(input) == std::string::npos)
        return '\0';
    this->right.step();
    return this->plugboard.encipher(input);
}

std::string Enigma::Info() {
    std::stringstream ss;
    ss << "Rotors: ";
    for (size_t i = 0; i < Rotor::COUNT; i++)
        ss << Rotor::rotors[i].name << " ";
    ss << std::endl
       << "Rotor Position: A-Z, 0-25" << std::endl
       << "Rotor Ring Setting: A-Z, 0-25" << std::endl
       << "Reflectors: ";
    for (size_t i = 0; i < Reflector::COUNT; i++)
        ss << Reflector::reflectors[i].name << " ";
    return ss.str();
}