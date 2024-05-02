//
// Created by Михаил Малюгин on 28.04.2024.
//

#ifndef CUNOVM_VM_H
#define CUNOVM_VM_H

#include <cstdint>
#include <stack>
#include <vector>

enum OP {
    HALT = 0x00, // end of the program
    ADD  = 0x01,
    SUB  = 0x02,
    MUL  = 0x03,
    DIV  = 0x04, // basic math operations
    GET  = 0x05, // get a element from offset (if < 0 -> curPos+offs else from stack beginning)
                 // from stack and push on top of the stack (requires argument)
    SET  = 0x06, // pops element from top of the stack and replace element from offset to it
                 // (requires argument)
    LOAD = 0x07, // load byte from static memory (address)
    JMP  = 0x08, // pops top of the stack and jumps if that was not zero (requires argument)
    JMPI = 0x09, // jump implicit (requires argument)
    CMP  = 0x0A, // Pops two top elements from stack. If first > second -> push 1 elif
                 // first == second -> 0 else -1
    POP  = 0x0B,
    PUSH = 0x0C, // (requires argument)
    INP  = 0x0D, // reads one byte from standard input and pushes it to stack
    PRNT = 0x0E, // print ascii char from last byte from top of the stack
    RET  = 0x0F, // return
    CALL = 0x10, // (requires argument) call function
};

class VM {
public:
    // Default stack size is 16MiB and every stack block is 4 bytes
    explicit VM(
            std::vector<uint8_t> code,
            uint8_t *staticMemory = nullptr,
            uint32_t stackSize=(16*1024*1024)/4,
            uint32_t startPosition = 0);
    ~VM();
    bool isWorking();
    void nextTick();
    uint32_t runProgram();
    void callFunc(uint32_t funcPtr);
private:
    uint32_t stackSize;
    bool work = false;
    uint32_t *stack;
    uint32_t stackPtr = 0;
    std::stack<uint32_t> callStack;
    std::vector<uint8_t> code;
    uint32_t codePtr;
    uint8_t *staticMemory;
    uint32_t retCode;
};


#endif //CUNOVM_VM_H
