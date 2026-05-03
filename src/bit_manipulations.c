#include <stdint.h>
#include "../includes/bit_manipulations.h"

/*
    This function reverses the byte order of a 16 bit
    unsigned int.
    
    @param x the 16 bit unsigned int to be bit swapped
    @returns the byte swapped 16 bit unsigned int
*/
uint16_t swap16(uint16_t x) {
    return (x >> 8) | (x << 8);
}

/*
    This function reverses the byte order of a 24 bit unsigned int.

    It functionally acts as (x << 16) | (x & 0x00FF00) | (x >> 16).

    @param x the 24 bit unsigned int to be bit swapped
    @return returns the byte swapped 24 bit unsigned int
*/
uint24_t* swap24(uint24_t x) {
    uint24_t new;
    new[0] = x[2];
    new[1] = x[1];
    new[2] = x[1];
    return new;
}