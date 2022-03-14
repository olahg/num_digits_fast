#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <algorithm>
#include <chrono>

#include "functions.cpp"

void check(uint64_t t, uint32_t expected)
{
    uint32_t n = (uint32_t) t;
    unsigned int v = num_digs(n);
    if (v != expected) {
        printf("Check failed: num_digs(%u) expected %u, but got %u\n", n, expected, v);
        exit (1);
    }
}


int main(int argc, char** argv)
{
    auto start = std::chrono::steady_clock::now();
    check(0, 1);
    uint64_t from = 1;
    uint64_t checks = 1;

    for (unsigned int expected = 1; expected < 11; expected++) {
        uint64_t end = std::min(from*10,(1lu<<32));
        for (uint64_t t = from; t < end; t++) {
            check(t, expected);
            checks++;
        }
        from *= 10;
    }
    assert(checks == (1lu<<32));
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    fprintf(stderr, "It took %12ld ms for %s to finish\n", elapsed, argv[0]);
    return 0;
}
