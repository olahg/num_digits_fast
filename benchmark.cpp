#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <map>
#include <limits>
#include <algorithm>
#include <chrono>
#include <vector>
#include <random>

#include "functions.cpp"


long run_test(std::vector<unsigned int>& data, char* output)
{
    char* next = output;
    auto start = std::chrono::steady_clock::now();
    for (auto k: data) {
        next += num_digs(k);
        char* tmp = next-1;
        do {
            *tmp-- = (k % 10) + '0';
            k /= 10;
        } while (k);
    }
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main(int argc, char** argv)
{
    FILE* fin = fopen(argv[1], "rt");
    if (fin == nullptr) {
        fprintf(stderr, "Can't open %s\n", argv[1]);
        exit (1);
    }
    std::vector<unsigned int> data;
    data.reserve(1024*1024*16);
    for (;;) {
        unsigned int number;
        unsigned int occurrances;
        if (fscanf(fin, "%u %u", &occurrances, &number) != 2) {
            break;
        }
        while (occurrances--) {
            data.push_back(number);
        }
    }
    fclose(fin);
//    std::mt19937 rnd(20220139);
    std::random_device rnd;
    std::shuffle(data.begin(), data.end(), rnd);
    long bestTime = 0x7fffffffffffffffllu;

    char* output = (char*)calloc(1+data.size()*10,1);


    for (int j = 0; j < 500; j++) {
        char* tmp = output;
        long elapsed = run_test(data, tmp);
        if (elapsed < bestTime) {
            bestTime = elapsed;
        }
    }
    if (data.size() < 50) {
        printf("%s\n", output);
    }
    free(output);
    printf("%s | %ld us | (%lf numbers/us)\n", argv[0], bestTime, (double) data.size() / bestTime);
    return 0;
}
