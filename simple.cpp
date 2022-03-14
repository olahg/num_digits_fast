#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <chrono>

#include "functions.cpp"


int main(int argc, char** argv)
{
    int from = atoi(argv[1]);
    int range = atoi(argv[2]);
    assert (0 < from);
    assert (from < 0x7fffffff);
    assert (0 < range);
    assert (range < 0x7fffffff);

    uint32_t s = (uint32_t) from;
    uint32_t e = s + range;
    unsigned long long dummy = 0;
    long bestTime = 0x7fffffffffffffffllu;
    for (int j = 0; j < 500; j++) {
        auto start = std::chrono::steady_clock::now();
        for (uint32_t j = s; j <= e; j++) {
            #ifdef OP_XOR
            dummy ^= num_digs(j);
            #else
            dummy += num_digs(j);
            #endif
        }
        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        if (elapsed < bestTime) {
            bestTime = elapsed;
        }
    }
    printf("%s | %ld us [%u-%u] %llu\n", argv[0], bestTime, s, e, dummy);
    return 0;
}
