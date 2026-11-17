//
// Created by User on 11/17/2026.
//
#pragma once
#include "instruction.h"
#include <vector>
#include <iostream>
#include <cstddef>

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
