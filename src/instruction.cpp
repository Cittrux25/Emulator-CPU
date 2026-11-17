//
// Created by User on 11/16/2026.
//

#include "instruction.h"

Instructions::Instructions(OpCode op, int x, int y):opcode(op), a(x), b(y) {}

OpCode Instructions::getOpCode() const {return opcode;}
int Instructions::getA() const {return a;}
int Instructions::getB() const {return b;}

std::string Instructions::opcodeName() const {
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
std::ostream& operator<<(std::ostream& os, const Instructions& ins) {
    os<<ins.opcodeName()<<" "<<ins.a<<" "<<ins.b;
    return os;
}