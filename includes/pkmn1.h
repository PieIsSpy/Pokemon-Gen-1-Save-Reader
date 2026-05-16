#ifndef PKMN1_H
#define PKMN1_H

#include <stdint.h>
#include "../includes/box_pokemon.h"

typedef struct {
    BoxPokemon pokemon;
    uint8_t nickname[11];
    uint8_t ot_name[11];
} PKMN1;

void save_pkmn1(PKMN1 pkmn);
PKMN1 create_pkmn1(BoxPokemon pkmn, uint8_t* nickname, uint8_t* ot_name);

#endif