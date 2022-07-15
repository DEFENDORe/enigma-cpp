#ifndef PLUGBOARD_H
#define PLUGBOARD_H
#include "BaseCipher.hpp"

class Plugboard : public BaseCipher {
    friend class Enigma;
    private:
        Plugboard();
        char encipher(char letter, bool forward = true);
    public:
        Plugboard(const Plugboard &p);
        void swap(char first, char second);
        void unswap(char letter);
};

#endif
