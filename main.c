#include <stdio.h>

int main() {
    FILE *fp;

    fp = fopen("debug\\target.sav", "r");

    if (fp != NULL) {
        printf("I exist! \n");
        printf("Position: %d \n", ftell(fp));
        fseek(fp, 0x2598, SEEK_SET);
        printf("Position: %d", ftell(fp));
    }
    else {
        printf("Where am i?");
    }

    fclose(fp);
    return 0;
}