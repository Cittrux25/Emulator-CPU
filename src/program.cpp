//
// Created by User on 11/17/2026.
//
#include "program.h"
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
}