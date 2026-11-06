 #pragma once
 #include <cstdint>
 class Memory{
    private:
     uint8_t cells[256];
     public:
     Memory();
     uint8_t read(uint16_t address) const;
     void write(uint16_t address, uint8_t value);

 };










 