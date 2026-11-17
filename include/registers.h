//
// Created by User on 11/16/2026.
//
#ifndef OOP_REGISTERS_H
#define OOP_REGISTERS_H

#pragma once
#include <iostream>

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

#endif //OOP_REGISTERS_H
