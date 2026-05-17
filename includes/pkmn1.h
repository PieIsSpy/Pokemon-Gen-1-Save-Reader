#ifndef PKMN1_H
#define PKMN1_H

#include <stdint.h>
#include "../includes/box_pokemon.h"

#pragma pack(1)
/*
    This struct saves a Pokemon's `BoxPokemon` structure, its nickname
    and its original trainer name

    @param pokemon the `BoxPokemon` structure info of the Pokemon
    @param nickname the nickname of the Pokemon
    @param ot_name the name of its original trainer
*/
typedef struct {
    BoxPokemon pokemon;
    uint8_t nickname[11];
    uint8_t ot_name[11];
} PKMN1;
#pragma pack()

void save_pkmn1(PKMN1 pkmn);
PKMN1 read_pkmn1(char* filename);
PKMN1 create_pkmn1(BoxPokemon pkmn, uint8_t* nickname, uint8_t* ot_name);
void print_pkmn1(PKMN1 pkmn);

#endif