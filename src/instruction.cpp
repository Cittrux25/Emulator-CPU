//
// Created by User on 11/16/2026.
//

#include "instruction.h"

instructions::instructions(OpCode op, int x, int y):opcode(op), a(x), b(y) {}

OpCode instructions::getOpCode() const {return opcode;}
int instructions::getA() const {return a;}
int instructions::getB() const {return b;}

std::string instructions::opcodeName() const {
    switch (opcode) {
        case OpCode::MOV: return "MOV";
        case OpCode::ADD: return "ADD";
        case OpCode::DEC: return "DEC";
        case OpCode::JNZ: return "JNZ";
        case OpCode::LOAD: return "LOAD";
        case OpCode::STORE: return "STORE";
        case OpCode::HALT: return "HALT";
    }
    return "";
}
std::ostream& operator<<(std::ostream& os, const instructions& ins) {
    os<<ins.opcodeName()<<" "<<ins.a<<" "<<ins.b;
    return os;
}