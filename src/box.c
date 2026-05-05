#include <stdio.h>
#include <stdint.h>
#include "../includes/char_converter.h"
#include "../includes/box.h"

Box read_box(FILE* fp, int box_num) {
    Box box = {0};
    uint16_t cur_box;
    fseek(fp, 0x284C, SEEK_SET);
    fread(&cur_box, 0x2, 1, fp);
    cur_box = swap16(cur_box);
    cur_box = cur_box >> 8;

    if (box_num >= 1 && box_num <= 12) {
        // check first if the target box is the current box
        if (box_num - 1 == (cur_box & 0x7F)) {
            fseek(fp, 0x30C0, SEEK_SET);

            fread(&box, sizeof(Box), 1, fp);
            for (int i = 0; i < box.pokemon_count; i++) {
                box.pokemons[i] = reformat_box_pokemon(box.pokemons[i]);
            }
        }

        // otherwise, check if the trainer has already switched to other boxes
        else if ((cur_box >> 7) == 1) {
            int start = (box_num < 7) ? 0x4000 : 0x6000;
            int index = (box_num < 7) ? (box_num - 1) : (box_num - 7);

            fseek(fp, start + (0x462 * index), SEEK_SET);

            fread(&box, sizeof(Box), 1, fp);
            for (int i = 0; i < box.pokemon_count; i++) {
                box.pokemons[i] = reformat_box_pokemon(box.pokemons[i]);
            }
        }
    }

    return box;
}

void print_box(Box box) {
    printf("Pokemon Count: %d\n", box.pokemon_count);
    for (int i = 0; i < box.pokemon_count; i++) {
        printf("%i] %s \n", i+1, convert_text(box.pokemon_names[i], 11));
        printf("Species index: %02x\n", box.species_ids[i]);
    }
    printf("\n");
}