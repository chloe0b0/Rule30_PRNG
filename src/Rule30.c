#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>

// For abitrary state sizes, will need an array of N booleans, this means 64 bits per cell (assuming each is a boolean)
// If we instead use an usigned long long, we can get 1 bit per cell and use bitwise operations to update the state

// Helper macros
#define N_TH(x, n)  x >> n & 1 // Get the N-th bit
#define SET(x, n)   x |= (1 << n)

// Constants
#define EPOCHS  500000000UL
#define BITS    64
#define OUT     false

typedef uint64_t State;

static inline void Iterate(State* __restrict state) {
    State end_ = N_TH(*state, 0) ^ (N_TH(*state, 63) | N_TH(*state, 62)) << 63;
    *state = (*state & ~(1ULL << 63)) | (end_ << 63);
    State n_state = (*state >> 1ULL) ^ (*state | (*state << 1ULL));
   
    // Hackish trick to prevent overflow of active cells
    // wrap around end cell

    *state = n_state;
}

// Yield the center cell's current state
static inline uint64_t Yield(State state) {
    return N_TH(state, 64/2); 
}

uint64_t Generate_64(State* __restrict rand, size_t bits) {
    uint64_t y = 0ULL;

    for (int j = 0; j < bits; ++j) {
        y = (y & ~(1ULL << j)) | (Yield(*rand) << j);
        Iterate(rand);
    }

    return y;
}

void PrintState(State state) {
    for (int i = 64; i--;) {
        const char cell = N_TH(state, i) ? '1' : ' ';
        printf("%c", cell);
    }
    printf("\n");
}

int main(void) {
    assert(sizeof(State) == 8);
    State rand = (uint64_t)time(NULL) * time(NULL) * time(NULL);
#if OUT
    FILE* outfile = fopen("out.txt", "a");
#endif
    clock_t t;
    t = clock();
    for (size_t i = EPOCHS; --i;) {
        uint64_t x = Generate_64(&rand, BITS);
#if OUT
        fprintf(outfile, "%lu\n", x);
#endif
    }
    t = clock() - t;
    double t_ = ((double)t/CLOCKS_PER_SEC);
    printf("Time taken to generate %d random %d-bit pseudo-random numbers: %f seconds\n", EPOCHS, BITS, t_);
#if OUT
    fclose(outfile);
#endif
}
