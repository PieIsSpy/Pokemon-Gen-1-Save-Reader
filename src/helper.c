#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "../includes/box.h"
#include "../includes/bit_manipulations.h"
#include "../includes/box_pokemon.h"
#include "../includes/pkmn1.h"
#include "../includes/helper.h"
#include "../includes/checksum.h"

/*
    This function withdraws a Pokemon from a Box and saves it into a .pkmn1 file.

    @param fp the save file to edit
    @param box_num the box number to edit
    @param pokemon_num the pokemon to withdraw
*/
void withdraw_box_pokemon(FILE* fp, int box_num, int pokemon_num) {
    Box box = read_box(fp, box_num);
    PKMN1 pkmn = create_pkmn1(box.pokemons[pokemon_num-1], box.pokemon_names[pokemon_num-1], box.ot_names[pokemon_num-1]);
    save_pkmn1(pkmn);
    box = delete_box_pokemon(box, pokemon_num-1);
    write_box(fp, box, box_num);
    recalculate_checksum(fp, box_num);
}

/*
    This function lets the user choose to whether withdraw a Pokemon or not.
*/
int box_pokemon_options() {
    int action = 0;

    printf("1] Withdraw\n");
    printf("2] Exit\n");
    while (action < 1 || action > 2) {
        printf("Action: ");
        scanf(" %d", &action);
        printf("\n");
    }

    return action;
}

/*
    This function lets the user choose whether to withdraw or deposit a Pokemon.

    @param fp the save file to edit
    @param box the box to edit
    @param box_num the number of the box chosen
*/
void box_options(FILE* fp, Box box, int box_num) {
    int action = 0;
    char filename[250] = {0};

    printf("1] Deposit\n");
    printf("2] Withdraw\n");
    printf("3] Cancel\n");
    while (action < 1 || action > 3) {
        printf("Action: ");
        scanf(" %d", &action);
        printf("\n");

        if (action == 1) {
            // printf("Target Filename: ");
            // scanf(" %s", filename);
            printf("test\n");
        }
        else if (action == 2) {
            choose_box_pokemon(fp, box, box_num);
        }
    }
}

/*
    This function lets the user choose which Pokemon to withdraw.

    @param fp the save file to edit
    @param box the box to edit
    @param box_num the number of the box
*/
void choose_box_pokemon(FILE* fp, Box box, int box_num) {
    int target_pokemon = 0;
    int action = 0;

    while (target_pokemon != -1) {
        PKMN1 pkmn;
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
            action = box_pokemon_options();

            if (action == 1) {
                withdraw_box_pokemon(fp, box_num, target_pokemon);
            }
        }
    }
}

/*
    This function lets the user choose a box to edit.

    @param fp the save file to edit
*/
void choose_box(FILE* fp) {
    int target_box = 0;
    while (target_box != -1) {
        Box box;
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
            printf("\n");
            box_options(fp, box, target_box);
        }
    }
}