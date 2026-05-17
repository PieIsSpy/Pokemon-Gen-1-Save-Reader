#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include "../includes/char_converter.h"
#include "../includes/box_pokemon.h"
#include "../includes/pkmn1.h"

/*
    This function saves a `PKMN1` struct into a .pkmn1 file with the filename:
    <nickname>_<dmY>_<HMS>.

    @param pkmn the `PKMN` Pokemon to save as a file
*/
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

/*
    This function reads a .pkmn1 file and creates a `PKMN1` struct from reading it.

    @param filename the file to read
    @returns the constructed `PKMN1` struct
*/
PKMN1 read_pkmn1(char* filename) {
    FILE* fp = fopen(filename, "rb");
    PKMN1 pkmn = {0};

    if (fp != NULL) {
        fread(&pkmn, sizeof(PKMN1), 1, fp);
    }
    return pkmn;
}

/*
    This function creates a PKMN1 struct from the given `BoxPokemon`, nickname and
    original trainer name.

    @param pkmn the `BoxPokemon` struct of the Pokemon
    @param nickname the nickname of the Pokemon
    @param ot_name the name of the Pokemon's original trainer
    @returns the `PKMN1` struct created
*/
PKMN1 create_pkmn1(BoxPokemon pkmn, uint8_t* nickname, uint8_t* ot_name) {
    PKMN1 save;
    save.pokemon = pkmn;
    memcpy(save.nickname, nickname, sizeof(uint8_t) * 11);
    memcpy(save.ot_name, ot_name, sizeof(uint8_t) * 11);

    return save;
}

/*
    This function prints out the given `PKMN1` structure.
    
    @param pkmn the Pokemon to be printed
*/
void print_pkmn1(PKMN1 pkmn) {
    print_box_pokemon(pkmn.pokemon, pkmn.nickname, pkmn.ot_name);
}