#pragma once
#include <iostream>
#include <string>
#include <cstdint>

class Screen {
    private:
    std::string buffer;

    public:
    Screen();
    void clear();
    void write(uint8_t value);
    std::string getOutput () const;

};
