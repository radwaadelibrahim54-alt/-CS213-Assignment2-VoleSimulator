#include <sstream>
#include <iomanip>
#include "Screen.h"

Screen::Screen(){
}
void Screen::writeByte(byte value){
     std::ostringstream oos;
    oos << std::hex << std::uppercase << std::setw(2) << std::setfill('0');
    oos << static_cast <int> (value);
    buffer = buffer + oos.str();
    buffer = buffer + " ";
    }
std::string Screen :: getOutput() const{
    return buffer;
}
