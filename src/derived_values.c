#include <math.h>
#include <stdint.h>
#include "../includes/box_pokemon.h"
#include "../includes/pokemon_species.h"
#include "../includes/derived_values.h"

/*
    This function computes for the `BoxPokemon`'s Derived HP value.

    @param base the base HP of the `PokemonSpecies`
    @param iv the HP IV of the `BoxPokemon`
    @param ev the HP EV of the `BoxPokemon`
    @param level the level of the `BoxPokemon`
    @returns the computed derived HP
*/
int compute_hp(int base, int iv, int ev, int level) {
    float hp = floor(((base + iv) * 2 + floor(ceil(sqrt(ev))/4)) * level / 100) + level + 10;
    return (int)hp;
}

/*
    This function computes for other stats derivations of the `BoxPokemon` that is not the HP stat.

    @param base the base stat of the `PokemonSpecies`
    @param iv the stat IV of the `BoxPokemon`
    @param ev the stat EV of the `BoxPokemon`
    @param level the level of the `BoxPokemon`
    @returns the computed derived stat
*/
int compute_stat(int base, int iv, int ev, int level) {
    float stat = floor(((base + iv) * 2 + floor(ceil(sqrt(ev))/4)) * level / 100) + 5;
    return (int)stat;
}

/*
    This function computes for the derived values of a given `BoxPokemon`
    and returns a struct containing them.

    @param pkmn the `BoxPokemon` to compute for
    @param species the species information of `BoxPokemon`
    @returns the computed derived stats of a `BoxPokemon`
*/
DerivedValues compute_dvs(BoxPokemon pkmn, PokemonSpecies species) {
    DerivedValues DVs = {0};
    uint8_t atkIV = (pkmn.ivs & 0xF000) >> 12;
    uint8_t defIV = (pkmn.ivs & 0x0F00) >> 8;
    uint8_t spdIV = (pkmn.ivs & 0x00F0) >> 4;
    uint8_t speIV = pkmn.ivs & 0x000F;
    uint8_t hpIV = (atkIV & 1) << 3 | (defIV & 1) << 2 | (spdIV & 1) << 1 | (speIV & 1);

    DVs.HP = compute_hp(species.baseHP, hpIV, pkmn.hpEV, pkmn.level);
    DVs.Atk = compute_stat(species.baseAtk, atkIV, pkmn.atkEV, pkmn.level);
    DVs.Def = compute_stat(species.baseDef, defIV, pkmn.defEV, pkmn.level);
    DVs.Spd = compute_stat(species.baseSpd, spdIV, pkmn.spdEV, pkmn.level);
    DVs.Spe = compute_stat(species.baseSpe, speIV, pkmn.speEV, pkmn.level);

    return DVs;
}