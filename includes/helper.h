#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include "../includes/box.h"
#include "../includes/pkmn1.h"

void withdraw_box_pokemon(FILE* fp, int box_num, int pokemon_num);
int box_pokemon_options();
void box_options(FILE* fp, Box box, int box_num);
void choose_box_pokemon(FILE* fp, Box box, int box_num);
void choose_box(FILE* fp);

#endif