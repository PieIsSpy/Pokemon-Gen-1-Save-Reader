#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "../includes/bit_manipulations.h"
#include "../includes/pokemon_species.h"
#include "../includes/char_converter.h"
#include "../includes/box_pokemon.h"

/*
    This function reformats a `Pokemon`
    by byte swapping its multibyte fields.

    @param pkmn the `Pokemon` to reformat
    @return the reformatted `Pokemon`
*/
BoxPokemon reformat_box_pokemon(BoxPokemon pkmn) {
    uint8_t* exp = swap24(pkmn.exp);

    pkmn.curHP = swap16(pkmn.curHP);
    pkmn.tid = swap16(pkmn.tid);
    memcpy(pkmn.exp, exp, sizeof(uint24_t));
    pkmn.hpEV = swap16(pkmn.hpEV);
    pkmn.atkEV = swap16(pkmn.atkEV);
    pkmn.defEV = swap16(pkmn.defEV);
    pkmn.spdEV = swap16(pkmn.spdEV);
    pkmn.speEV = swap16(pkmn.speEV);
    pkmn.ivs = swap16(pkmn.ivs);

    free(exp);

    return pkmn;
}

void print_box_pokemon(BoxPokemon pkmn, uint8_t* nickname, uint8_t* ot) {
    PokemonSpecies speciesInfo = fetch_species_info(pkmn.speciesId);
    char* nickname_convert = convert_text(nickname, 11);
    char* ot_convert = convert_text(ot, 11);

    printf("%s | %s\n", nickname_convert, speciesInfo.speciesName);
    printf("Lv. %d\n", pkmn.level);
    printf("Dex Num: %d\n", speciesInfo.dexNum);
    printf("OT: %s\n", ot_convert);
    printf("Type: %s/%s\n", speciesInfo.type1, speciesInfo.type2);
    printf("HP: %d/%d\n", pkmn.curHP, pkmn.hpEV);
    printf("Attack: %d\n", pkmn.atkEV);
    printf("Defense: %d\n", pkmn.defEV);
    printf("Special: %d\n", pkmn.speEV);
    printf("Speed: %d\n", pkmn.spdEV);
    printf("\n");

    free(nickname_convert);
    free(ot_convert);
}