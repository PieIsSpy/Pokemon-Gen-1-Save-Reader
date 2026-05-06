#include <string.h>
#include <stdint.h>
#include "../includes/bit_manipulations.h"
#include "../includes/box_pokemon.h"

/*
    This function reformats a `Pokemon`
    by byte swapping its multibyte fields.

    @param pkmn the `Pokemon` to reformat
    @return the reformatted `Pokemon`
*/
BoxPokemon reformat_box_pokemon(BoxPokemon pkmn) {
    pkmn.curHP = swap16(pkmn.curHP);
    pkmn.tid = swap16(pkmn.tid);
    memcpy(pkmn.exp, swap24(pkmn.exp), sizeof(uint24_t));
    pkmn.hpEV = swap16(pkmn.hpEV);
    pkmn.atkEV = swap16(pkmn.atkEV);
    pkmn.defEV = swap16(pkmn.defEV);
    pkmn.spdEV = swap16(pkmn.spdEV);
    pkmn.speEV = swap16(pkmn.speEV);
    pkmn.ivs = swap16(pkmn.ivs);

    return pkmn;
}