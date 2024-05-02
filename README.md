# cunoVM
cunoVM - 32bit stack-based virtual machine for programming languages made by me (miko089)

cunoVM is **educational project**, you shouldn't use it in real languages

## Currently supported commands:
- Halt (0x00) - exit the program, number on the top of stack is program's return code
- ADD (0x01), SUB (0x02), MUL (0x03), DIV (0x04) - basic math operations (addiction, 
substraction, multiplication and division). Brings two arguments fom top of the stack and perform operation as if 
numbers were 32bit signed integers
- GET (0x05), SET (0x06) - these commands require one argument (offset). GET copy element from [arg] position of stack 
(if offset < 0 -> offset from end (arg = -1 equals top of the stack), else counts from back of the stack)
- LOAD (0x07) - LOAD one byte from [arg] of static memory and pushes it on the top of the stack
- JMP (0x08)  - pops top of the stack and jumps to [arg] position in code if that was not zero
- JMPI (0x09) - jumps to [arg] anyway
- CMP (0x0A) - pops two top elements from stack. If first > second -> push 1 elif
first == second -> 0 else -1
- POP (0x0B) - desintegrates an element on top of the stack
- PUSH (0x0C) - took arg and pushes it on the top of the stack
- INP (0x0D) - reads one byte from stdin on the top of the stack pushes in stack
- PRNT (0x0E) - print one byte from top of the stack as ascii symbol then pops
- RET (0x0F) - return from function
- CALL (0x10) - call func from [arg] in code

## TODO
- [ ] Check stack overflow
- [ ] add dynamic memory
- [ ] add support for system calls from virtual machine
