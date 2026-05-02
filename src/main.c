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

        printf("Name: %s \n", convert_text(trainer.name, 11));
        printf("ID: %d \n", trainer.id);
        
    }
    else {
        printf("ERROR: FileNotFoundException \n");
    }

    fclose(fp);
    return 0;
}