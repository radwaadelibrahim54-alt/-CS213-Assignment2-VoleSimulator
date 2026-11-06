#pragma once
#include <string>
#include <cstdint>
using byte = uint8_t;

class Screen {
    private:
    std::string buffer;

    public:
    Screen();
    void clear();
    void writeByte(byte value);
    std::string getOutput () const;

};


