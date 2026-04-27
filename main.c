#include <stdio.h>

char convert_char(char c) {
    if (c >= 0xffffff80 && c <= 0xffffff99) {
        return c - 0xffffff80 + 65;
    }

    if (c >= 0xffffffa0 && c <= 0xffffffb9) {
        return c - 0xffffffa0 + 97;
    }

    return 0;
}

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