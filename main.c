#define STANDARD_CHAR_OFFSET 0xffffff00
#include <stdio.h>
#include "char_converter.c"

int main() {
    FILE *fp;
    char name[11];
    char id[2];

    fp = fopen("debug\\target.sav", "r");

    if (fp != NULL) {
        printf("Save File Recognized \n");
        fseek(fp, 0x2598, SEEK_SET);
        fread(name, sizeof(name), 1, fp);

        printf("Name: %s \n", convert_text(name, 11));

        fseek(fp, 0x2605, SEEK_SET);
        fread(id, sizeof(id), 1, fp);
        printf("ID: %d \n", id);
        
    }
    else {
        printf("ERROR: FileNotFoundException \n");
    }

    fclose(fp);
    return 0;
}