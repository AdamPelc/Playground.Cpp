#include "fibonacci.h"

value_t fibonacci(index_t position) {
    if (position <= 1) {
        return position;
    }

    value_t previous = 0;
    value_t current  = 1;

    for (index_t idx = 2; idx <= position; ++idx) {
        value_t next = previous + current;
        previous     = current;
        current      = next;
    }

    return current;
}
