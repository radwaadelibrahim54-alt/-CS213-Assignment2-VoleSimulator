 #pragma once
 #include <cstdint>
 
using byte = uint8_t;
class Memory{
  
 private:
     byte cells[256];
    
 public:
     Memory();
     byte read(uint8_t address) const;
     void write(uint8_t address, byte value);
     bool isValidAddress (int address ) const;
 };










 
