#include <stdio.h>

/*
    This function converts a standard text char into an ASCII char.
    If the standard text char cannot be represented by a valid ASCII char,
    then it will return 0 instead.

    @param c the read character
    @returns the converted ASCII value
*/
char convert_char(char c) {
    /*
        A = 0xffffff80
        Z = 0xffffff99
    */
    if (c >= 0xffffff80 && c <= 0xffffff99) {
        return c - 0xffffff80 + 65;
    }

    /*
        a = 0xffffffa0
        z = 0xffffffb9
    */
    if (c >= 0xffffffa0 && c <= 0xffffffb9) {
        return c - 0xffffffa0 + 97;
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

        for (int i = 0; i < 11; i++)
            printf("%04x ", name[i]);

        printf("\n");

        printf("Name: %s", convert_text(name, 11));
        
    }
    else {
        printf("ERROR: FileNotFoundException");
    }

    fclose(fp);
    return 0;
}