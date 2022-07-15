#ifndef ROTOR_H
#define ROTOR_H
#include "BaseCipher.hpp"
#include <vector>

class Rotor: public BaseCipher {
    friend class Enigma;
    private:
        static const size_t COUNT;
        static Rotor rotors[];
        std::string notch;
        size_t position;
        size_t ring;
        size_t offset;
        
        Rotor();
        Rotor(std::string name, std::string cipher, std::string notch, size_t position = 0, size_t ring = 0);
        bool isOnNotch();
        void step();
        char encipher(char letter, bool forward = true);
    public:
        static Rotor SelectRotor(std::string name, char position = 'A', char ring = 'A');
        Rotor(const Rotor &r);
        void setPosition(size_t position);
        void setRing(size_t ring);
        
};

#endif
