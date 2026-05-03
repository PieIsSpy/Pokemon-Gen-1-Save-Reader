#ifndef BOX_H
#define BOX_H

#include "bit_manipulations.h"
#include "box_pokemon.h"

#pragma pack(1)
/*
    This structure represents a `Box` that can at most store 20 `Pokemon`s.

    @param pokemon_count stores the current number of pokemon present in the box
    @param species_ids the list of Pokemon species inside the box
    @param padding unused padding
    @param pokemons the list of `Pokemon` data structures inside the box
    @param ot_names the list of Pokemons' Orignal Trainer names
    @param pokemon_names the list of Pokemon nicknames
*/
typedef struct {
    uint8_t pokemon_count;
    uint8_t species_ids[20];
    uint8_t padding;
    BoxPokemon pokemons[20];
    uint8_t ot_names[20][11];
    uint8_t pokemon_names[20][11];
} Box;
#pragma pack()

Box read_box(FILE* fp, int box_num);
void print_box(Box box);

#endif