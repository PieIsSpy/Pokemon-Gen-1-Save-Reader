#include <stdio.h>
#include <stdint.h>
#include "../includes/box.h"
#include "../includes/bit_manipulations.h"
#include "../includes/box_pokemon.h"
#include "../includes/pkmn1.h"

void box_pokemon_options(PKMN1 pkmn) {
    int action;

    printf("1] Save\n");
    printf("2] Exit\n");
    while (action < 1 || action > 2) {
        printf("Action: ");
        scanf(" %d", &action);
        printf("\n");

        if (action == 1) {
            save_pkmn1(pkmn);
        }
    }
}

void choose_box_pokemon(Box box) {
    int target_pokemon;
    PKMN1 pkmn;

    while (target_pokemon != -1) {
        printf("Enter target pokemon (-1 to exit): ");
        scanf(" %d", &target_pokemon);
        printf("\n");

        if (target_pokemon != -1 && (target_pokemon < 1 || target_pokemon > box.pokemon_count)) {
            printf("Not a valid pokemon\n");
            printf("\n");
        }
        else if (target_pokemon >= 1 && target_pokemon <= box.pokemon_count) {
            pkmn = create_pkmn1(box.pokemons[target_pokemon - 1], box.pokemon_names[target_pokemon - 1], box.ot_names[target_pokemon - 1]);
            print_box_pokemon(pkmn.pokemon, pkmn.nickname, pkmn.ot_name);
            printf("\n");
            box_pokemon_options(pkmn);
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
            choose_box_pokemon(box);
        }
    }
}