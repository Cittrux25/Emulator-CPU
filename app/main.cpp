#include <iostream>
#include <registers.h>

int main() {
    Registers reg;
    reg.set(0, 5);
    reg.incrementPc();
    std::cout<<reg<<"\n";
    return 0;
}