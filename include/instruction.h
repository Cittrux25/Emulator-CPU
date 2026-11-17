//
// Created by User on 11/16/2026.
//

#pragma once
#include <iostream>
#include <string>

enum class OpCode {
    MOV, ADD, DEC, JNZ, LOAD, STORE, HALT
};

class instructions {
    OpCode opcode;
    int a;
    int b;
    std::string opcodeName() const;
public:
    explicit instructions(OpCode op, int x=0, int y=0);
    OpCode getOpCode() const;
    int getA() const;
    int getB() const;
    friend std::ostream& operator<<(std::ostream& os, const instructions& in);
};