//
// Created by User on 11/19/2026.
//
#include "memory.h"

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
