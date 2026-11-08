#include <iostream>
#include "Memory.h"

Memory::Memory(){
for ( int i = 0; i < 256; i++){
    cells[i]=0;
}
}
bool Memory ::isValidAddress(int address) const{
    return address >= 0 && address < 256;
}

void Memory::write(uint8_t  address,byte value){
        cells[address]= value;
    }
    
  uint8_t Memory::read(uint8_t address ) const {
        return cells[address];
  }
