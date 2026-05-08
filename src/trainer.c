#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
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

/*
    This function prints a `Trainer`'s `name` and `id`.
    
    @param trainer the trainer to print
*/
void print_trainer(Trainer trainer) {
    char* name = convert_text(trainer.name, 11);
    printf("Name: %s \n", name);
    printf("ID: %d \n", trainer.id);
    free(name);
}