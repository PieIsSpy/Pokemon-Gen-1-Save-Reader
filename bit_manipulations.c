/*
    This function reverses the byte order of a 16 bit
    unsigned int.
    
    from @AmaneKai :troll_face:
    
    @param x the 16 bit unsigned int to be bit swapped
    @returns the bit swapped 16 bit unsigned int
*/
uint16_t swap16(uint16_t x) {
    return (x >> 8) | (x << 8);
}