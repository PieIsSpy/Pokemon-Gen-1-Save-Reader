#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/char_converter.h"
#include "../includes/box_pokemon.h"
#include "../includes/box.h"
#include "../includes/pkmn1.h"

/*
    This function finds the offset for a given box number

    @param fp the file to search through
    @param box_num the box number to find
    @return the offset of the box
*/
int seek_box_offset(FILE* fp, int box_num) {
    uint16_t cur_box;
    fseek(fp, 0x284C, SEEK_SET);
    fread(&cur_box, 0x2, 1, fp);
    cur_box = swap16(cur_box);
    cur_box = cur_box >> 8;

    // check first if the target box is the current box
    if (box_num - 1 == (cur_box & 0x7F)) {
        return 0x30C0;
    }

    // otherwise, check if the trainer has already switched to other boxes
    else if ((cur_box >> 7) == 1) {
        int start = (box_num < 7) ? 0x4000 : 0x6000;
        int index = (box_num < 7) ? (box_num - 1) : (box_num - 7);

        return start + (0x462 * index);
    }

    return 0;
}

/*
    This function reads a specified box in the save file.

    @param fp the save file to read
    @param box_num the box number to read
*/
Box read_box(FILE* fp, int box_num) {
    Box box = {0};
    int offset;

    if (box_num >= 1 && box_num <= 12) {
        offset = seek_box_offset(fp, box_num);
        fseek(fp, offset, SEEK_SET);

        fread(&box, sizeof(Box), 1, fp);
    }

    return box;
}

void write_box(FILE* fp, Box box, int box_num) {
    int offset = seek_box_offset(fp, box_num);
    fseek(fp, offset, SEEK_SET);
    fwrite(&box, sizeof(Box), 1, fp);
}

/*
    This function summarizes the contents of a box and prints it.

    @param box the box to print
*/
void print_box(Box box) {
    printf("Pokemon Count: %d\n", box.pokemon_count);
    for (int i = 0; i < box.pokemon_count; i++) {
        char* nickname = convert_text(box.pokemon_names[i], 11);
        printf("%d] %s\n", i+1, nickname);
        free(nickname);
    }
    printf("\n");
}

/*
    This function deletes a `BoxPokmeon` from a `Box`.

    @param box the box to be edited
    @param index the index of the Pokemon to be deleted
    @returns the edited box
*/
Box delete_box_pokemon(Box box, int index) {
    BoxPokemon dummy = {0};
    int i;

    // shift everything down
    for (i = index; i < box.pokemon_count - 1; i++) {
        box.species_ids[i] = box.species_ids[i+1];
        box.pokemons[i] = box.pokemons[i+1];
        memcpy(box.pokemon_names[i], box.pokemon_names[i+1], sizeof(uint8_t) * 11);
        memcpy(box.ot_names[i], box.ot_names[i+1], sizeof(uint8_t) * 11);
    }

    // replace the end with 0s and terminating id
    box.species_ids[i] = 0xFF;
    box.pokemons[i] = dummy;
    memset(box.pokemon_names[i], 0, 11);
    memset(box.ot_names[i], 0, 11);

    box.pokemon_count -= 1;

    return box;
}

Box add_box_pokemon(Box box, PKMN1 pkmn) {
    box.species_ids[box.pokemon_count] = pkmn.pokemon.speciesId;
    box.pokemons[box.pokemon_count] = pkmn.pokemon;
    memcpy(box.pokemon_names[box.pokemon_count], pkmn.nickname, sizeof(uint8_t) * 11);
    memcpy(box.ot_names[box.pokemon_count], pkmn.ot_name, sizeof(uint8_t) * 11);

    box.pokemon_count += 1;

    if (box.pokemon_count < 20) {
        box.species_ids[box.pokemon_count] = 0xFF;
    }

    return box;
}