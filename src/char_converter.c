#include <stdint.h>
#include <stdlib.h>
#include "../includes/char_converter.h"
#include "../includes/bit_manipulations.h"

/*
    This function converts a proprietary character into a valid ASCII character.
    If a proprietary character cannot be represented by a valid ASCII character,
    then it will return 0 instead.

    @param c the read character
    @returns the converted ASCII value
*/
char convert_char(uint8_t c) {
    char letter_convert = c - 63;
    int is_letter = (letter_convert >= 65 && letter_convert <= 90) || (letter_convert >= 97 && letter_convert <= 122);

    // return as a letter
    if (is_letter) {
        return letter_convert;
    }

    // 0x50 marks the end of a string
    if (c == 0x50) {
        return 0;
    }

    // anything else will be represented as space for now
    return 32;
}

/*
    This function converts an array of proprietary characters
    into valid ASCII characters using `convert_char()`.

    @param string the string to be converted
    @param length the length of the string
    @returns the converted string in ASCII values
*/
char* convert_text(uint8_t* string, int length) {
    char* converted_string = malloc(sizeof(char) * length);
    for (int i = 0; i < length; i++) {
        converted_string[i] = convert_char(string[i]);
    }

    return converted_string;
}