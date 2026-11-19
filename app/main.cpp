#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
//#include "registers.h"
//#include "instruction.h"
//#include "program.h"
//#include "memory.h"

class Registers {
    int r[4];
    int pc;
public:
    explicit Registers(int startPc = 0);
    int get(int i) const;
    void set(int i, int v);
    void incrementPc();
    int getPc() const;
    void setPc(int value);

    friend std::ostream& operator<<(std::ostream& os, const Registers& reg);
};

int Registers::getPc()const {return pc;}
void Registers::setPc(int value) {pc = value;};

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
    int* cells;
    std::size_t size;
public:
    explicit Memory(std::size_t n=16);
    Memory(const Memory& other);
    Memory& operator=(const Memory& other);
    ~Memory();
    int read(std::size_t addr) const;
    void write(std::size_t addr, int value);
    friend std::ostream& operator<<(std::ostream& os, const Memory& mem);
};

Memory::Memory(std ::size_t n):cells(new int[n]()),size(n) {}
Memory::~Memory() {
    delete[] cells;
}
int Memory::read(std::size_t addr) const {
    if (addr>=size) {
        std::cerr<<"Adresa invalida: "<<addr<<"\n";
        return 0;
    }
    return cells[addr];
}

void Memory::write(std::size_t addr, int value) {
    if (addr>=size) {
        std::cerr<<"Adresa invalida: "<<addr<<"\n";
        return;
    }
    cells[addr] = value;
}
std::ostream& operator<<(std::ostream& os, const Memory& mem) {
    for (std::size_t i=0; i<mem.size; i++) {
        if (mem.cells[i]!=0) {
            os<<"["<<i<<"] "<<mem.cells[i]<<"\n";
        }
    }
    return os;
}

Memory::Memory(const Memory& other):cells(new int[other.size]()),size(other.size) {
    for (std::size_t i=0;i<size;i++) {
        cells[i]=other.cells[i];
    }
}
Memory& Memory::operator=(const Memory& other) {
    if (this==&other) {
        return *this;
    }
    int* newcells = new int[other.size];
    for (std::size_t i=0;i<other.size;i++) {
        newcells[i]=other.cells[i];
    }
    delete[] cells;
    cells=newcells;
    size=other.size;
    return *this;
}

class Cpu {
    Registers regs;
    Memory mem;
    Program prog;
    bool halted;
    void execute (const Instructions& ins);

public:
    explicit Cpu(const Program& prog, std::size_t memorySize =16);
    bool step();
    void run(std::size_t maxSteps = 1000) {
        std::size_t steps=0;
        while (steps < maxSteps && step()) {
            steps++;
        }
    }
    bool isHalted() const;
    int getRegister(int i) const;
    friend std::ostream& operator<<(std::ostream& os, const Cpu& cpu);
};

Cpu::Cpu(const Program& p, std::size_t memorySize):regs(),mem(memorySize), prog(p) , halted(false){}
void Cpu::execute(const Instructions& ins) {
    int a=ins.getA();
    int b=ins.getB();
    switch (ins.getOpCode()) {
        case OpCode::MOV:
            regs.set(a,b);
            regs.incrementPc();
            break;
        case OpCode::ADD:
            regs.set(a,regs.get(a)+regs.get(b));
            regs.incrementPc();
            break;
        case OpCode::DEC:
            regs.set(a,regs.get(a)-1);
            regs.incrementPc();
            break;
        case OpCode::JNZ:
            if (regs.get(a)!=0) {
                regs.setPc(b);
            } else {
                regs.incrementPc();
            }
            break;
        case OpCode::LOAD:
            regs.set(a,mem.read(static_cast<std::size_t>(b)));
            regs.incrementPc();
            break;
        case OpCode::STORE:
            mem.write(static_cast<std::size_t>(b),regs.get(a));
            regs.incrementPc();
            break;
        case OpCode::HALT:
            halted=true;
            break;
    }
}
bool Cpu::step() {
    if (halted) {
        return false;
    }
    std::size_t pc=static_cast<std::size_t>(regs.getPc());
    if (pc>=prog.size()) {
        halted=true;
        return false;
    }
    execute(prog.at(pc));
    return true;
}
bool Cpu::isHalted()const{return halted;}
int Cpu::getRegister(int i)const{return regs.get(i);}
std::ostream& operator<<(std::ostream& os, const Cpu& cpu) {
    os<<"Registre: "<<cpu.regs<<"\n";
    os<<"Memorie: "<<cpu.mem<<"\n";
    os<<"Oprit: "<<(cpu.halted ? "da":"nu");
    return os;
}

int main() {
    Registers reg;
    reg.set(0, 5);
    reg.incrementPc();
    reg.setPc(3);
    std::cout<<reg.get(0)<<" "<<reg.getPc()<<"\n";
    std::cout<<reg<<"\n";
    Instructions ins(OpCode::MOV, 0, 5);
    std::cout<<ins<<"\n";

    Program prog;
    prog.add(Instructions(OpCode::MOV, 0, 5));
    prog.add(Instructions(OpCode::MOV, 1, 0));
    prog.add(Instructions(OpCode::ADD, 1, 0));
    prog.add(Instructions(OpCode::DEC, 0));
    prog.add(Instructions(OpCode::JNZ, 0, 2));
    prog.add(Instructions(OpCode::STORE, 1, 0));
    prog.add(Instructions(OpCode::LOAD, 2, 0));
    prog.add(Instructions(OpCode::HALT));
    std::cout<<prog;

    std::cout<<static_cast<int>(ins.getOpCode())<<" "<<ins.getA()<<" "<<ins.getB()<<" "<<prog.at(0)<<" "<<prog.size()<<"\n";

   Cpu cpu(prog);
    cpu.step();
    std::cout<<cpu<<"\n";
    cpu.run();
    std::cout<<cpu<<"\n";
    std::cout<<cpu.getRegister(1)<<" "<<cpu.isHalted()<<"\n";

    Memory m(8);
    m.write(0, 15);
    Memory copy = m;
    copy.write(0, 99);
    Memory other;
    other = m;
    std::cout << m << copy << other;

    return 0;
}
