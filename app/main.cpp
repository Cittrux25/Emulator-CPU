#include <iostream>
#include <vector>
//#include "registers.h"
//#include "instruction.h"
//#include "program.h"

class Registers {
    int r[4];
    int pc;
public:
    explicit Registers(int startPc = 0);
    int get(int i) const;
    void set(int i, int v);
    void incrementPc();

    friend std::ostream& operator<<(std::ostream& os, const Registers& reg);
};

Registers::Registers(int startPc) :pc(startPc) {
    for (int i=0; i<4 ;i++) {r[i]=0;}

}
void Registers::incrementPc() {pc++;}

int Registers::get(int i) const {return r[i];}

void Registers::set(int i, int v) {r[i]=v;}

std::ostream& operator<<(std::ostream& os, const Registers& reg) {
    for (int i=0; i<4 ;i++) os<<reg.get(i)<<" ";
    os<<reg.pc;
    return os;
};

enum class OpCode {
    MOV, ADD, DEC, JNZ, LOAD, STORE, HALT
};

class Instructions {
    OpCode opcode;
    int a;
    int b;
    std::string opcodeName() const;
public:
    explicit Instructions(OpCode op, int x=0, int y=0);
    OpCode getOpCode() const;
    int getA() const;
    int getB() const;
    friend std::ostream& operator<<(std::ostream& os, const Instructions& in);
};

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
};

class Program {
    std::vector<Instructions> code;
public:
    Program()=default;
    explicit Program(const std::vector<Instructions> & instrs);
    void add(const Instructions& ins);
    const Instructions& at(std::size_t line) const;
    std::size_t size() const;
    friend std::ostream& operator<<(std::ostream& os, const Program& prog);
};

Program::Program(const std::vector<Instructions>& instrs):code(instrs){}
void Program::add(const Instructions& ins) {
    code.push_back(ins);
}
const Instructions& Program::at(std::size_t line) const {
    return code.at(line);
}
std::size_t Program::size() const {
    return code.size();
}
std::ostream& operator<<(std::ostream& os, const Program& prog) {
    for (std::size_t i=0;i<prog.code.size();i++)
        os<<i<<":"<<prog.code[i]<<"\n";
    return os;
};

class Memory {

};

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

    std::cout<<static_cast<int>(ins.getOpCode())<<" "<<ins.getA()<<" "<<ins.getB()<<" "<<prog.at(0)<<" "<<prog.size()<<"\n";
    return 0;
}
