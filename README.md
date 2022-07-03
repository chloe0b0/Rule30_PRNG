# Rule30 as a PRNG
Using rule30 as a Pseudo-random number generator



## Objective
Create a PRNG with good statistical properties and a very small state space

Uses 64 bit state size

## Goals
- Demonstrate good randomness
- be as fast as possible
- have a very small state size 

## Analysis
Below are various graphs displaying the implementation's quality of randomness and uniformity.

### Generating a 0 or 1
![](./img/1s.png)

### Generating 32 bit numbers
![](./img/32bit.png)

### Generating 64 bit numbers
![](./img/64bit.png)

### Generated 244x244 Bitmap
![](./img/bitmap.png)
