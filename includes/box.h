#ifndef BOX_H
#define BOX_H

typedef struct {
    uint8_t pokemon_count;
    uint8_t species_ids[20];
    uint8_t padding;
    BoxPokemon pokemons[20];
    char ot_names[11][20];
    char pokemon_names[11][20];
} Box;

#endif