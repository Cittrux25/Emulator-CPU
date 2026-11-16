//
// Created by User on 11/16/2026.
//

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

#ifndef OOP_REGISTERS_H
#define OOP_REGISTERS_H

#endif //OOP_REGISTERS_H
