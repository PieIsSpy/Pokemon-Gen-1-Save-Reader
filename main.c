#include <stdio.h>
#define STANDARD_CHAR_OFFSET 0xffffff00

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

    if (is_letter) {
        return letter_convert;
    }

    return 0;
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

int main() {
    FILE *fp;
    char name[11];

    fp = fopen("debug\\target2.sav", "r");

    if (fp != NULL) {
        printf("Save File Recognized \n");
        fseek(fp, 0x2598, SEEK_SET);
        fread(name, sizeof(name), 1, fp);

        printf("Name: %s \n", convert_text(name, 11));
        
    }
    else {
        printf("ERROR: FileNotFoundException \n");
    }

    fclose(fp);
    return 0;
}