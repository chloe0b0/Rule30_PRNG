#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>

// For abitrary state sizes, will need an array of N booleans, this means 32 bits per cell (assuming each is a boolean)
// If we instead use an usigned long long, we can get 1 bit per cell and use bitwise operations to update the state

// Helper macros
#define N_TH(x, n)  x >> n & 1 // Get the N-th bit
#define SET(x, n)   x |= (1 << n)

// Constants
#define EPOCHS  500
#define BITS    15

typedef uint32_t State;

static inline State Iterate(State state){
    State n_state = (state >> 1) ^ (state | (state << 1));
   
    // Hackish trick to prevent overflow of active cells
    if (N_TH(state, 31)){
        n_state ^= (1UL << 31);
    }
    return n_state;
}

// Yield the center cell's current state
static inline uint32_t Yield(State state){
    return N_TH(state, 32/2); 
}

uint64_t Generate_64(State rand, size_t bits){
    uint64_t y = 0ULL;

    for (int j = 0; j < bits; ++j){
        y = (y & ~(1ULL << j)) | (Yield(rand) << j);
        rand = Iterate(rand);
    }

    return y;
}

void PrintState(State state){
    for (int i = 32; i--;){
        const char cell = N_TH(state, i) ? '1' : '0';
        printf("%c", cell);
    }
    printf("\n");
}

int main(void){
    assert(sizeof(State) == 4);
    State rand = (uint32_t)time(NULL) * time(NULL) * time(NULL);

    clock_t t;
    t = clock();
    for (int i = EPOCHS; --i;){
        rand = Iterate(rand);
        uint64_t x = Generate_64(rand, BITS);
        printf("%lu \n", x);
    }
    t = clock() - t;
    double t_ = ((double)t/CLOCKS_PER_SEC);
    printf("Time taken to generate %d random %d-bit pseudo-random numbers: %f seconds\n", EPOCHS, BITS, t_);
}
