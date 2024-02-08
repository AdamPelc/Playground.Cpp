#include <iostream>

int foo(int a, int b) {
    __asm volatile("# LLVM-MCA-BEGIN foo":::"memory");
    auto x = a + b;
    x += a * b;
    x += a / b;
    __asm volatile("# LLVM-MCA-END":::"memory");
    return x;
}
