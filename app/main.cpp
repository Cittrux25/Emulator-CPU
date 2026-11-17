#include <iostream>
#include "registers.h"
#include "instruction.h"

int main() {
    Registers reg;
    reg.set(0, 5);
    reg.incrementPc();
    std::cout<<reg<<"\n";
    instructions ins(OpCode::MOV, 0, 5);
    std::cout<<ins<<"\n";
    return 0;
}
