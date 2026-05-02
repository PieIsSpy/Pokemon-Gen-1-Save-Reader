#include <stdint.h>
#include "../includes/char_converter.h"
#include "../includes/bit_manipulations.h"

/*
    This function converts a standard text char into an ASCII char.
    If the standard text char cannot be represented by a valid ASCII char,
    then it will return 0 instead.

    @param c the read character
    @returns the converted ASCII value
*/
char convert_char(char c) {
    char c_offset = c - STANDARD_CHAR_OFFSET;

    char letter_convert = c_offset - 63;
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
    This function converts an entire string from standard text chars
    into ASCII chars using `convert_char()`.

    @param string the string to be converted
    @param length the length of the string
    @returns the converted string in ASCII values
*/
char* convert_text(char* string, int length) { 
    for (int i = 0; i < length; i++) {
        string[i] = convert_char(string[i]);
    }

    return string;
}