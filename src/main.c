#include <stdio.h>
#include <stdint.h>
#include "../includes/char_converter.h"
#include "../includes/bit_manipulations.h"
#include "../includes/trainer.h"
#include "../includes/box_pokemon.h"
#include "../includes/box.h"
#include "../includes/helper.h"

int main() {
    FILE *fp;
    Trainer trainer;
    char filename[255];

    printf("Target Filename: ");
    scanf(" %s", filename);

    printf("\n");

    fp = fopen(filename, "rb");

    if (fp != NULL) {
        printf("Save File Recognized \n");
        trainer = read_trainer(fp);

        print_trainer(trainer);
        printf("\n");

        choose_box(fp);
    }
    else {
        printf("ERROR: FileNotFoundException \n");
    }

    fclose(fp);
    return 0;
}