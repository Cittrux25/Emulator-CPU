//
// Created by User on 11/16/2026.
//

#include "registers.h"

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
}