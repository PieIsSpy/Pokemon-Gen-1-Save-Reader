#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include "../includes/char_converter.h"
#include "../includes/box_pokemon.h"
#include "../includes/pkmn1.h"

void save_pkmn1(PKMN1 pkmn) {
    FILE* save;
    char filename[250];
    char* converted_nickname = convert_text(pkmn.nickname, 11);
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char buffer[100];

    strftime(buffer, sizeof(buffer), "%d%m%Y_%H%M%S", t);
    
    strcpy(filename, converted_nickname);
    strcat(filename, "_");
    strcat(filename, buffer);
    strcat(filename, ".pkmn1");
    save = fopen(filename, "wb");
    fwrite(&pkmn, sizeof(PKMN1), 1, save);
    printf("Saved %s\n", filename);

    free(converted_nickname);
    fclose(save);
}

PKMN1 create_pkmn1(BoxPokemon pkmn, uint8_t* nickname, uint8_t* ot_name) {
    PKMN1 save;
    save.pokemon = pkmn;
    memcpy(save.nickname, nickname, sizeof(uint8_t) * 11);
    memcpy(save.ot_name, ot_name, sizeof(uint8_t) * 11);

    return save;
}