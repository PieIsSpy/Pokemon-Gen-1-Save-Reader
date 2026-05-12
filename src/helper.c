#include <stdio.h>
#include <stdint.h>
#include "../includes/box.h"
#include "../includes/bit_manipulations.h"
#include "../includes/box_pokemon.h"

void choose_pokemon(Box box) {
    int target_pokemon;

    while (target_pokemon != -1) {
        printf("Enter target pokemon (-1 to exit): ");
        scanf(" %d", &target_pokemon);
        printf("\n");

        if (target_pokemon != -1 && (target_pokemon < 1 || target_pokemon > box.pokemon_count)) {
            printf("Not a valid pokemon\n");
            printf("\n");
        }
        else if (target_pokemon >= 1 && target_pokemon <= box.pokemon_count) {
            print_box_pokemon(box.pokemons[target_pokemon - 1], box.pokemon_names[target_pokemon - 1], box.ot_names[target_pokemon - 1]);
        }
    }
}

void choose_box(FILE* fp) {
    int target_box;
    Box box;
    while (target_box != -1) {
        printf("Enter target box (-1 to exit): ");
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
            choose_pokemon(box);
        }
    }
}