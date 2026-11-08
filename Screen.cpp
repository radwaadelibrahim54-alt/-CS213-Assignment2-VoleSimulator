
#include "Screen.h"

Screen::Screen(){
}
void Screen::writeByte(byte value){
     buffer += static_cast <char>(value);
}
std::string Screen :: getOutput() const{
    return buffer;
}