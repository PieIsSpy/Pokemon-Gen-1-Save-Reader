#include <stdio.h>
#include <stdint.h>
#include "../includes/char_converter.h"
#include "../includes/bit_manipulations.h"
#include "../includes/trainer.h"

int main() {
    FILE *fp;
    Trainer trainer;
    char filename[255];

    printf("Target Filename: ");
    scanf(" %s", filename);

    fp = fopen(filename, "r");

    if (fp != NULL) {
        printf("Save File Recognized \n");
        trainer = read_trainer(fp);

        print_trainer(trainer);
    }
    else {
        printf("ERROR: FileNotFoundException \n");
    }

    fclose(fp);
    return 0;
}