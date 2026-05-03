#include <stdio.h>
#include <stdint.h>
#include "../includes/char_converter.h"
#include "../includes/bit_manipulations.h"
#include "../includes/trainer.h"

int main() {
    FILE *fp;
    Trainer trainer;

    fp = fopen("debug\\target.sav", "r");

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