#ifndef BASECIPHER_H
#define BASECIPHER_H
#include <string>

class BaseCipher {
    friend class Enigma;
    friend class Plugboard;
    friend class Rotor;
    friend class Reflector;
    private:
        inline static const std::string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        static size_t base26(size_t num);
        std::string name;
        std::string cipher;
        std::string reverse_cipher();
        BaseCipher* next = nullptr;
        BaseCipher* prev = nullptr;
        virtual void step();
        virtual char encipher(char letter, bool forward = true) = 0;
};

#endif
