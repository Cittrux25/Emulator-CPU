//
// Created by User on 11/19/2026.
//

#ifndef OOP_MEMORY_H
#define OOP_MEMORY_H
#pragma once
#include <cstddef>
#include <iostream>

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


#endif //OOP_MEMORY_H
