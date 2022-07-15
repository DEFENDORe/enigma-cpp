#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <limits>

#include <termios.h>
#include <stdio.h>

#include <Enigma.hpp>
#include <cxxopts.hpp>

cxxopts::Options options("enigma-cli", "Enigma M3 Machine CLI Program");

void showHelp() {
    std::cout << options.help() << std::endl
              << Enigma::Info() << std::endl;
    exit(0);
}

std::vector<std::string> parsePlugs(std::string &plugs) {
    std::vector<std::string> results;
    std::stringstream  ss(plugs);
    std::string temp;
    std::string letters = "";
    while (getline(ss, temp, ',')) {
        for(char &c: temp)
            c = c & ~' ';
        if (temp.length() != 2 ||
            Enigma::ALPHABET.find(temp[0]) == std::string::npos ||
            Enigma::ALPHABET.find(temp[1]) == std::string::npos)
                throw std::invalid_argument("Invalid plugboard entry.");
        if (letters.find(temp[0]) != std::string::npos ||
            letters.find(temp[1]) != std::string::npos)
                throw std::invalid_argument("Duplicate plugboard entry.");
            letters += temp;
        results.push_back(temp);
    }
    return results;
}

size_t parseRotorSetting(std::string &setting) {
    size_t result = std::string::npos;
    try {
        result = std::stoi(setting);
    } catch (std::exception & e) {
        for(char &c: setting)
            c = c & ~' ';
        result = Enigma::ALPHABET.find(setting[0]);
        if (setting.length() != 1 || result == std::string::npos)
            throw std::invalid_argument("Invalid rotor position or ring provided.");
    }
    if (result > 25 || result < 0)
        throw std::invalid_argument("Invalid rotor position or ring provided.");
    return result;
}

void singleCharMode(bool enable) {
    static struct termios t;
    static struct termios t_saved;
    if (enable) {
        // Set terminal to single character mode.
        tcgetattr(fileno(stdin), &t);
        t_saved = t;
        t.c_lflag &= (~ICANON & ~ECHO);
        t.c_cc[VTIME] = 0;
        t.c_cc[VMIN] = 1;
        tcsetattr(fileno(stdin), TCSANOW, &t);
    } else {
        // Restore terminal mode.
        tcsetattr(fileno(stdin), TCSANOW, &t_saved);
    }
}

int main(int argc, char** argv) {
    options.add_options()
        ("p,plugboard", "Plugboard letter swaps\nExample: -p ab,cd,ef", cxxopts::value<std::string>()->default_value(""))
        ("r,reflector", "Reflector name\nExample: -r B", cxxopts::value<std::string>())
        ("w,rotor", "Rotor wheels. (Name,Position,Ring) x3\nExample: -w I,0,0,II,0,0,III,0,0", cxxopts::value<std::vector<std::string>>())
        ("t,text", "Input text to encode/decode", cxxopts::value<std::string>())
        ("h,help", "Print usage")
    ;
    cxxopts::ParseResult result = options.parse(argc, argv);

    if (result.count("help") || !result["rotor"].count() || !result["reflector"].count()) {
        showHelp();
    }

    auto plugs = result["plugboard"].as<std::string>();
    auto rotors = result["rotor"].as<std::vector<std::string>>();
    auto reflector = result["reflector"].as<std::string>();

    auto plugPairs = parsePlugs(plugs);

    Enigma enigma;

    if (rotors.size() != 9)
        showHelp();

    try {
        // wire plugboard
        for (auto &plug : plugPairs)
            enigma.plugboard.swap(plug[0], plug[1]);
        enigma.right = Rotor::SelectRotor(rotors[0], parseRotorSetting(rotors[1]), parseRotorSetting(rotors[2]));
        enigma.middle = Rotor::SelectRotor(rotors[3], parseRotorSetting(rotors[4]), parseRotorSetting(rotors[5]));
        enigma.left = Rotor::SelectRotor(rotors[6], parseRotorSetting(rotors[7]), parseRotorSetting(rotors[8]));
        enigma.reflector = Reflector::SelectReflector(reflector);
    } catch (std::exception &e) {
        showHelp();
    }
    

    if (result["text"].count()) {
        auto text = result["text"].as<std::string>();
        std::cout << enigma.encipher(text);
    } else {
        singleCharMode(true);
        std::streambuf *pbuf = std::cin.rdbuf();
        bool done = false;
        while (!done) {
            char c;
            if (pbuf->sgetc() == EOF)
                done = true;
            c = pbuf->sbumpc();
            if (c == '\n')
                done = true;
            std::cout << enigma.encipher(c);
        }
        singleCharMode(false);
    }
    std::cout << std::endl;
    return 0;
};