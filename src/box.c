#include <stdio.h>
#include <stdint.h>
#include "../includes/char_converter.h"
#include "../includes/box.h"

Box read_box(FILE* fp, int box_num) {
    Box box;
    int start = (box_num < 7) ? 0x4000 : 0x6000;
    int index = (box_num < 7) ? (box_num - 1) : (box_num - 7);

    fseek(fp, start + (0x462 * index), SEEK_SET);
    fread(&box, sizeof(Box), 1, fp);

    for (int i = 0; i < box.pokemon_count; i++) {
        box.pokemons[i] = reformat_box_pokemon(box.pokemons[i]);
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