#ifndef POKEMON_SPECIES_H
#define POKEMON_SPECIES_H

/*
    This structure represents a `Pokemon`'s species information.

    @param dexNum the national dex number of the Pokemon
    @param speciesName the name of the Pokemon species
    @param type1 the 1st type of the Pokemon
    @param type2 the 2nd type of the Pokemon
    @param baseHP the base HP stat of the Pokemon
    @param baseAtk the base Attack stat of the Pokemon
    @param baseDef the base Defense stat of the Pokemon
    @param baseSpd the base Speed stat of the Pokemon
    @param baseSpe the base Special stat of the Pokemon
*/
typedef struct {
    int dexNum;
    char speciesName[13];
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