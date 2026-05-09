#ifndef POKEMON_SPECIES_H
#define POKEMON_SPECIES_H

typedef struct {
    int dexNum;
    char speciesName[13];
    char growthRate[12];
    char type1[9];
    char type2[9];
    int baseHP;
    int baseAtk;
    int baseDef;
    int baseSpd;
    int baseSpe;
} PokemonSpecies;

PokemonSpecies fetch_species_info(uint8_t hex);

#endif