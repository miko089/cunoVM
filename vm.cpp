//
// Created by Михаил Малюгин on 28.04.2024.
//

#include <cstdlib>
#include "vm.h"
#include <iostream>


VM::VM(std::vector<uint8_t> code,
       uint8_t *staticMemory,
       uint32_t stackSize,
       uint32_t startPosition)
: stackSize(stackSize), staticMemory(staticMemory), codePtr(startPosition), code(code) {
    stack = static_cast<uint32_t *>(calloc(sizeof(uint32_t), stackSize));
    callStack = std::stack<uint32_t>();
}

VM::~VM() {
    free(stack);
    stack = nullptr;
}

bool VM::isWorking() { return work; };

void VM::callFunc(uint32_t funcPtr) {
    callStack.push(codePtr + 1);
    codePtr = funcPtr;
    return;
}

void VM::nextTick() {
    if (code.size() <= codePtr) {
        work = false;
        retCode = 13; // never seen halt, out of bounds
        return;
    }
    int32_t arg = 0;
    switch (code[codePtr]) {
        case HALT:
            work = false;
            retCode = stack[stackPtr];
            break;
        case ADD:
            if (stackPtr < 2) {
                retCode = 14; // not enough args
                work = false;
                break;
            }
            stackPtr -= 1;
            stack[stackPtr] += stack[stackPtr+1];
            break;
        case SUB:
            if (stackPtr < 2) {
                retCode = 14; // not enough args
                work = false;
                break;
            }
            stack[stackPtr-1] = stack[stackPtr] - stack[stackPtr-1];
            stackPtr -= 1;
            break;
        case MUL:
            if (stackPtr < 2) {
                retCode = 14; // not enough args
                work = false;
                break;
            }
            stackPtr -= 1;
            stack[stackPtr] *= stack[stackPtr+1];
            break;
        case DIV:
            if (stackPtr < 2) {
                retCode = 14; // not enough args
                work = false;
                break;
            }
            stack[stackPtr-1] = stack[stackPtr] / stack[stackPtr-1];
            stackPtr -= 1;
            break;
        case GET:
            for (int i = 0; i < 4; ++i) {
                codePtr += 1;
                arg += code[codePtr] << (8*(3-i));
            }
            if (arg < 0) {
                stackPtr += 1;
                arg *= -1;
                if (arg > stackPtr - 1) {
                    retCode = 15; // arg can't be used
                    work = false;
                    break;
                }
                stack[stackPtr] = stack[stackPtr-arg];
            } else {
                if (arg > stackPtr - 1) {
                    retCode = 15;
                    work = false;
                    break;
                }
                stack[stackPtr] = stack[arg];
            }
            break;
        case SET:
            for (int i = 0; i < 4; ++i) {
                codePtr += 1;
                arg += code[codePtr] << (8*(3-i));
            }
            stackPtr -= 1;
            if (arg < 0) {
                arg *= -1;
                if (arg > stackPtr) {
                    retCode = 15; // arg can't be used
                    work = false;
                    break;
                }
                stack[stackPtr-arg+2] = stack[stackPtr+1];
            } else {
                stack[arg] = stack[stackPtr+1];
            }
            break;
        case LOAD:
            for (int i = 0; i < 4; ++i) {
                codePtr += 1;
                arg += code[codePtr] << (8*(3-i));
            }
            stackPtr += 1;
            stack[stackPtr] = staticMemory[arg];
            break;
        case JMP:
            for (int i = 0; i < 4; ++i) {
                codePtr += 1;
                arg += code[codePtr] << (8*(3-i));
            }
            if (stack[stackPtr] != 0) {
                codePtr = arg;
            }
            stackPtr -= 1;
            break;
        case JMPI:
            for (int i = 0; i < 4; ++i) {
                codePtr += 1;
                arg += code[codePtr] << (8*(3-i));
            }
            codePtr = arg;
            break;
        case CMP:
            stackPtr -= 1;
            stack[stackPtr] = ((stack[stackPtr] == stack[stackPtr+1]) ? 0 :
                               (stack[stackPtr+1] > stack[stackPtr]) ? 1 : -1);
            break;
        case POP:
            stackPtr -= 1;
            break;
        case PUSH:
            for (int i = 0; i < 4; ++i) {
                codePtr += 1;
                arg += code[codePtr] << (8*(3-i));
            }
            stackPtr += 1;
            stack[stackPtr] = arg;
            break;
        case INP:
            {
                char inp;
                std::cin >> inp;
                stackPtr += 1;
                stack[stackPtr] = inp;
            }
            break;
        case PRNT:
            std::cout << static_cast<char>(stack[stackPtr]);
            stackPtr -= 1;
            break;
        case CALL:
            for (int i = 0; i < 4; ++i) {
                codePtr += 1;
                arg += code[codePtr] << (8*(3-i));
            }
            callFunc(arg);
            break;
        case RET:
            codePtr = callStack.top();
            callStack.pop();
            break;
    }
    codePtr++;
}

uint32_t VM::runProgram() {
    work = true;
    while (this->isWorking()) {
        nextTick();
    }
    return retCode;
}





