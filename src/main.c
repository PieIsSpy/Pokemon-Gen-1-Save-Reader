#include <stdio.h>
#include <stdint.h>
#include "../includes/char_converter.h"
#include "../includes/bit_manipulations.h"
#include "../includes/trainer.h"
#include "../includes/box_pokemon.h"
#include "../includes/box.h"

int main() {
    FILE *fp;
    Trainer trainer;
    char filename[255];
    int target_box;
    Box box;

    printf("Target Filename: ");
    scanf(" %s", filename);

    printf("\n");

    fp = fopen(filename, "r");

    if (fp != NULL) {
        printf("Save File Recognized \n");
        trainer = read_trainer(fp);

        print_trainer(trainer);
        printf("\n");

        while (target_box != -1) {
            printf("Enter target box: ");
            scanf(" %d", &target_box);
            printf("\n");

            if (target_box != -1 && (target_box < 1 || target_box > 12)) {
                printf("Not a valid box number\n");
                printf("\n");
            }
            else if (target_box >= 1 && target_box <= 12) {
                printf("Box %d\n", target_box);
                box = read_box(fp, target_box);
                print_box(box);
            }
        }
    }
    else {
        printf("ERROR: FileNotFoundException \n");
    }

    fclose(fp);
    return 0;
}