#ifndef ENIGMA_H
#define ENIGMA_H
#include "Plugboard.hpp"
#include "Reflector.hpp"
#include "Rotor.hpp"

class Enigma {
    private:
        void wire();
    public:
        inline static const std::string & ALPHABET = BaseCipher::ALPHABET;
        static std::string Info();
        Plugboard plugboard;
        Rotor right;
        Rotor middle;
        Rotor left;
        Reflector reflector;
        std::string encipher(std::string input);
        char encipher(char input);
};

#endif
