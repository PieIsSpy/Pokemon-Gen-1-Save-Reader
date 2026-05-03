#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "../includes/char_converter.h"
#include "../includes/bit_manipulations.h"
#include "../includes/trainer.h"

/*
    This function gets the trainer's name and id from the save file
    and stores them into a `Trainer` struct and returns it.

    @param fp the save file to be read
    @returns the trainer read from the save file.
*/
Trainer read_trainer(FILE* fp) {
    Trainer trainer;

    fseek(fp, 0x2598, SEEK_SET);
    fread(trainer.name, sizeof(trainer.name), 1, fp);

    fseek(fp, 0x2605, SEEK_SET);
    fread(&trainer.id, sizeof(trainer.id), 1, fp);
    trainer.id = swap16(trainer.id);

    return trainer;
}

void print_trainer(Trainer trainer) {
    printf("Name: %s \n", convert_text(trainer.name, 11));
    printf("ID: %d \n", trainer.id);
}