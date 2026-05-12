#include <math.h>
#include <stdint.h>
#include "../includes/box_pokemon.h"
#include "../includes/pokemon_species.h"
#include "../includes/derived_values.h"

int compute_hp(int base, int iv, int ev, int level) {
    float hp = floor(((base + iv) * 2 + floor(ceil(sqrt(ev))/4)) * level / 100) + level + 10;
    return (int)hp;
}

int compute_stat(int base, int iv, int ev, int level) {
    float stat = floor(((base + iv) * 2 + floor(ceil(sqrt(ev))/4)) * level / 100) + 5;
    return (int)stat;
}

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