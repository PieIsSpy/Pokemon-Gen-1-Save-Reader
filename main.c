#include <stdio.h>

int main() {
    FILE *fp;
    char name[10];

    fp = fopen("debug\\target.sav", "r");

    if (fp != NULL) {
        printf("Save File Recognized \n");
        printf("Position: %d \n", ftell(fp));
        fseek(fp, 0x2598, SEEK_SET);
        printf("Position: %d \n", ftell(fp));
        fread(name, sizeof(name), 1, fp);
        printf("Name: %s", name);
    }
    else {
        printf("ERROR: FileNotFoundException");
    }

    fclose(fp);
    return 0;
}