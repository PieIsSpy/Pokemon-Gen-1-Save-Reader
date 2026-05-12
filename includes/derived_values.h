#ifndef DERIVED_VALUES_H
#define DERIVED_VALUES_H

#include "../includes/box_pokemon.h"
#include "../includes/pokemon_species.h"

/*
    This struct represents the Derived Values of
    a BoxPokemon.

    @param HP the derived HP value
    @param Atk the derived Attack value
    @param Def the derived Defense value
    @param Spd the derived Speed value
    @param Spe the derived Special value
*/
typedef struct {
    int HP;
    int Atk;
    int Def;
    int Spd;
    int Spe;
} DerivedValues;

int compute_hp(int base, int iv, int ev, int level);
int compute_stat(int base, int iv, int ev, int level);
DerivedValues compute_dvs(BoxPokemon pkmn, PokemonSpecies species);

#endif