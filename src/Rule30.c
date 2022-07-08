#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>

// For best performance compile with:
// gcc -o PRNG Rule30.c -O2 -finline-functions

// For abitrary state sizes, will need an array of N booleans, this means 8 bits per cell (assuming each is a boolean)
// If we instead use an usigned long long, we can get 1 bit per cell and use bitwise operations to update the state

// Helper macros
#define N_TH(x, n)  x >> n & 1 // Get the N-th bit
#define SET(x, n)   x |= (1 << n)

// Constants
#define EPOCHS      5000000UL
#define BITS        64
#define OUT         false
#define MODE        "w"
#define PRINT       false
#define LEAST_SIG   true // Fill least significant bits

typedef uint64_t Rule30;

static inline void Iterate(Rule30* __restrict state) {
    Rule30 end_ = N_TH(*state, 0) ^ (N_TH(*state, 63) | N_TH(*state, 62)) << 63;
    *state = (*state & ~(1ULL << 63)) | (end_ << 63);
   
    // Hackish trick to prevent overflow of active cells
    // wrap around end cell

    *state = (*state >> 1) ^ (*state | (*state << 1));
}

// Yield the center cell's current state
static inline uint64_t Yield(Rule30 state) {
    return N_TH(state, 64/2); 
}

void PrintRule30(State state) {
    for (int i = 64; i--;) {
        const char cell = N_TH(state, i) ? '1' : '0';
        printf("%c", cell);
    }
    printf("\n");
}

uint64_t Generate_64(Rule30* __restrict rand, size_t bits) {
    uint64_t y = 0ULL;

    for (int j = 0; j <= bits; j++) {
#if LEAST_SIG
        y = (y & ~(1ULL << j)) | (Yield(*rand) << j);
#else
        y = (y & ~(1ULL << bits - j)) | (Yield(*rand) << bits - j);
#endif
        Iterate(rand);
#if PRINT
        PrintRule30(*rand);
#endif
    }

    return y;
}

int main(void) {
    assert(sizeof(Rule30) == 8);
    Rule30 rand = (uint64_t)time(NULL) * time(NULL) * time(NULL);
#if OUT
    FILE* outfile = fopen("out.txt", MODE);
#endif
    clock_t t;
    t = clock();
    for (size_t i = 0; i < EPOCHS; ++i) {
        uint64_t x = Generate_64(&rand, BITS);
#if PRINT
        printf("%llu \n", x);
#endif 
#if OUT
        fprintf(outfile, "%llu\n", x);
#endif
    }
    t = clock() - t;
    double t_ = ((double)t/CLOCKS_PER_SEC);
    printf("Time taken to generate %d random %d-bit pseudo-random numbers: %f seconds\n", EPOCHS, BITS, t_);
#if OUT
    fclose(outfile);
#endif
}
