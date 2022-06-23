#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>

// For abitrary state sizes, will need an array of N booleans, this means 8 bits per cell (assuming each is a boolean)
// If we instead use an usigned long long, we can get 1 bit per cell and use bitwise operations to update the state

// Helper macros
#define N_TH(x, n)  x >> n & 1 // Get the N-th bit
#define SET(x, n)   x |= (1u << n)

typedef uint32_t State;

State Iterate(State state){
    State n_state = (state >> 1) ^ (state | (state << 1));
   
    // Hackish trick to prevent overflow of active cells
    if (N_TH(state, 31)){
        n_state ^= 1ULL << 31;
    }
    return n_state;
}

// Yield the center cell's current state
uint32_t Yield(State state){
    return N_TH(state, 31); 
}

uint32_t Generate_32(State rand){
    uint32_t y = 0u;

    for (int j = 0; j < 32; ++j){
        if (Yield(rand)){ SET(y, j); }
        rand = Iterate(rand);
    }

    return y;
}

double Generate_Double(State rand){
    return (double)(Generate_32(rand) >> 11) * (1.0/90040991.0);
}

void PrintState(State state){
    for (int i = 64; i--;){
        const char cell = N_TH(state, i) ? '1' : ' ';
        printf("%c", cell);
    }
    printf("\n");
}

int main(void){
    assert(sizeof(State) == 4);
    State rand = (uint32_t)time(NULL) * 2509821950215;

    for (int i = 0; i < 10; ++i){
        printf("%lu\n", Generate_32(rand));
        rand = Iterate(rand);
    }

}

