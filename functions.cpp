#include <stdint.h>

#ifdef NUM_DIGS_BASELINE
uint32_t num_digs(uint32_t n)
{
    uint32_t r = 1;
    for (;;) {
        if (n < 10) return r;
        n /= 10;
        r++;
    }
}
#endif

#ifdef NUM_DIGS_PARALLEL
uint32_t num_digs(uint32_t n)
{
    return 1 +
        (n >= 10) +
        (n >= 100) +
        (n >= 1000) +
        (n >= 10000) +
        (n >= 100000) +
        (n >= 1000000) +
        (n >= 10000000) +
        (n >= 100000000) +
        (n >= 1000000000);
}
#endif

#ifdef NUM_DIGS_MULTIPLY
uint32_t num_digs(uint32_t n)
{
    uint32_t result = 1;
    uint64_t q = 10;
    for (;;) {
        if (n < q) return result;
        q *= 10;
        result++;
    }
}
#endif


int int_log2(uint32_t x) { return 31 - __builtin_clz(x|1); }

#ifdef NUM_DIGS_TABLE
uint32_t num_digs(uint32_t n)
{
    static uint32_t table[] = {9, 99, 999, 9999, 99999,
    999999, 9999999, 99999999, 999999999};
    int y = (9 * int_log2(n)) >> 5;
    y += n > table[y];
    return y + 1;
}
#endif


#ifdef NUM_DIGS_TABLE2
uint32_t num_digs(uint32_t n) {
    static const uint64_t table[] = {
        4294967296,  8589934582,  8589934582,  8589934582,  12884901788,
        12884901788, 12884901788, 17179868184, 17179868184, 17179868184,
        21474826480, 21474826480, 21474826480, 21474826480, 25769703776,
        25769703776, 25769703776, 30063771072, 30063771072, 30063771072,
        34349738368, 34349738368, 34349738368, 34349738368, 38554705664,
        38554705664, 38554705664, 41949672960, 41949672960, 41949672960,
        42949672960, 42949672960};
    return (n + table[int_log2(n)]) >> 32;
}
#endif

#ifdef NUM_DIGS_TABLE2_PARALLEL0
uint32_t num_digs(uint32_t n) {
    static const uint64_t table[] = {
        4294967296,  8589934582,  8589934582,  8589934582,  12884901788,
        12884901788, 12884901788, 17179868184, 17179868184, 17179868184,
        21474826480, 21474826480, 21474826480, 21474826480, 25769703776,
        25769703776, 25769703776, 30063771072, 30063771072, 30063771072,
        34349738368, 34349738368, 34349738368, 34349738368, 38554705664,
        38554705664, 38554705664, 41949672960, 41949672960, 41949672960,
        42949672960, 42949672960};
    if (n == 0) {
        return 1;
    }
    return (n + table[31 - __builtin_clz(n)]) >> 32;
}
#endif


#ifdef NUM_DIGS_TABLE2_PARALLEL1
uint32_t num_digs(uint32_t n) {
    static const uint64_t table[] = {
        4294967296,  8589934582,  8589934582,  8589934582,  12884901788,
        12884901788, 12884901788, 17179868184, 17179868184, 17179868184,
        21474826480, 21474826480, 21474826480, 21474826480, 25769703776,
        25769703776, 25769703776, 30063771072, 30063771072, 30063771072,
        34349738368, 34349738368, 34349738368, 34349738368, 38554705664,
        38554705664, 38554705664, 41949672960, 41949672960, 41949672960,
        42949672960, 42949672960};
    if (n < 10) {
        return 1;
    }
    return (n + table[31 - __builtin_clz(n)]) >> 32;
}
#endif


#ifdef NUM_DIGS_TABLE2_PARALLEL2
uint32_t num_digs(uint32_t n) {
    static const uint64_t table[] = {
        4294967296,  8589934582,  8589934582,  8589934582,  12884901788,
        12884901788, 12884901788, 17179868184, 17179868184, 17179868184,
        21474826480, 21474826480, 21474826480, 21474826480, 25769703776,
        25769703776, 25769703776, 30063771072, 30063771072, 30063771072,
        34349738368, 34349738368, 34349738368, 34349738368, 38554705664,
        38554705664, 38554705664, 41949672960, 41949672960, 41949672960,
        42949672960, 42949672960};
    if (n < 100) {
        return 1 + (n >= 10);
    }
    return (n + table[31 - __builtin_clz(n)]) >> 32;
}
#endif


#ifdef NUM_DIGS_TABLE2_PARALLEL3
uint32_t num_digs(uint32_t n) {
    static const uint64_t table[] = {
        4294967296,  8589934582,  8589934582,  8589934582,  12884901788,
        12884901788, 12884901788, 17179868184, 17179868184, 17179868184,
        21474826480, 21474826480, 21474826480, 21474826480, 25769703776,
        25769703776, 25769703776, 30063771072, 30063771072, 30063771072,
        34349738368, 34349738368, 34349738368, 34349738368, 38554705664,
        38554705664, 38554705664, 41949672960, 41949672960, 41949672960,
        42949672960, 42949672960};
    if (n < 1000) {
        return 1 + (n >= 10) + (n >= 100);
    }
    return (n + table[31 - __builtin_clz(n)]) >> 32;
}
#endif

#ifdef NUM_DIGS_TABLE2_PARALLEL4
uint32_t num_digs(uint32_t n) {
    static const uint64_t table[] = {
        4294967296,  8589934582,  8589934582,  8589934582,  12884901788,
        12884901788, 12884901788, 17179868184, 17179868184, 17179868184,
        21474826480, 21474826480, 21474826480, 21474826480, 25769703776,
        25769703776, 25769703776, 30063771072, 30063771072, 30063771072,
        34349738368, 34349738368, 34349738368, 34349738368, 38554705664,
        38554705664, 38554705664, 41949672960, 41949672960, 41949672960,
        42949672960, 42949672960};
    if (n < 10000) {
        return 1 + (n >= 10) + (n >= 100) + (n >= 1000);
    }
    return (n + table[31 - __builtin_clz(n)]) >> 32;
}
#endif



#ifdef NUM_DIGS_BIGDIV2
uint32_t num_digs(uint32_t n)
{
    uint32_t result = 1;
    for(;;) {
        if (n < 10) return result+0;
        if (n < 100) return result+1;
        n /= 100u;
        result += 2;
    }
}
#endif

#ifdef NUM_DIGS_BIGDIV2_PARALLEL
uint32_t num_digs(uint32_t n)
{
    uint32_t result = 1;
    for(;;) {
        if (n < 100) {
            return result + (n >= 10);
        }
        n /= 100u;
        result += 2;
    }
}
#endif

#ifdef NUM_DIGS_BIGDIV3
uint32_t num_digs(uint32_t n)
{
    uint32_t result = 1;
    for(;;) {
        if (n < 10) return result+0;
        if (n < 100) return result+1;
        if (n < 1000) return result+2;
        n /= 1000u;
        result += 3;
    }
}
#endif

#ifdef NUM_DIGS_BIGDIV3_PARALLEL
uint32_t num_digs(uint32_t n)
{
    uint32_t result = 1;
    for(;;) {
        if (n < 1000) {
            return result + (n >= 10)+(n >= 100);
        }
        n /= 1000u;
        result += 3;
    }
}
#endif

#ifdef NUM_DIGS_BIGDIV4
uint32_t num_digs(uint32_t n)
{
    uint32_t result = 1;
    for(;;) {
        if (n < 10) return result+0;
        if (n < 100) return result+1;
        if (n < 1000) return result+2;
        if (n < 10000) return result+3;
        n /= 10000u;
        result += 4;
    }
}
#endif

#ifdef NUM_DIGS_BIGDIV4_PARALLEL
uint32_t num_digs(uint32_t n)
{
    uint32_t result = 1;
    for(;;) {
        if (n < 10000) {
            return result + (n >= 10)+(n >= 100)+(n >= 1000);
        }
        n /= 10000u;
        result += 4;
    }
}
#endif

#ifdef NUM_DIGS_BIGDIV5
uint32_t num_digs(uint32_t n)
{
    uint32_t result = 1;
    for(;;) {
        if (n < 10) return result+0;
        if (n < 100) return result+1;
        if (n < 1000) return result+2;
        if (n < 10000) return result+3;
        if (n < 100000) return result+4;
        n /= 100000u;
        result += 5;
    }
}
#endif

#ifdef NUM_DIGS_BIGDIV5_PARALLEL
uint32_t num_digs(uint32_t n)
{
    uint32_t result = 1;
    for(;;) {
        if (n < 100000) {
            return result + (n >= 10)+(n >= 100)+(n >= 1000)+(n >= 10000);
        }
        n /= 100000u;
        result += 5;
    }
}
#endif
