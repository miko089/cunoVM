
#include "vm.h"
#include <vector>
#include <iostream>

int main() {
    VM a = VM(std::vector<uint8_t>{
        INP,
        INP,
        INP,
        INP,
        SET,
        0xFF,
        0xFF,
        0xFF,
        0xFD,
        PRNT,
        PRNT,
        PRNT,
        HALT
    });
    uint32_t retCode = a.runProgram();
    std::cout << "\nreturn code is " << retCode << std::endl;
    return 0;
}
