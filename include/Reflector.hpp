#ifndef REFLECTOR_H
#define REFLECTOR_H
#include "BaseCipher.hpp"

class Reflector : public BaseCipher {
    friend class Enigma;
    private:
        static const size_t COUNT;
        static Reflector reflectors[];
        Reflector(std::string name, std::string cipher);
        Reflector();
        char encipher(char letter, bool forward = true);
    public:
        static Reflector SelectReflector(std::string name);
        Reflector(const Reflector &r);
};

#endif
