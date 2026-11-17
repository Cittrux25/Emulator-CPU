#include <iostream>
#include "registers.h"
#include "instruction.h"
#include "program.h"

int main() {
    Registers reg;
    reg.set(0, 5);
    reg.incrementPc();
    std::cout<<reg<<"\n";
    Instructions ins(OpCode::MOV, 0, 5);
    std::cout<<ins<<"\n";

    Program prog;
    prog.add(Instructions(OpCode::MOV, 0, 5));
    prog.add(Instructions(OpCode::MOV, 1, 0));
    prog.add(Instructions(OpCode::ADD, 1, 0));
    prog.add(Instructions(OpCode::DEC, 0));
    prog.add(Instructions(OpCode::JNZ, 0, 2));
    prog.add(Instructions(OpCode::HALT));
    std::cout<<prog;

    return 0;
}
