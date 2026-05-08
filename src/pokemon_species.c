#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../includes/pokemon_species.h"

PokemonSpecies fetch_species_info(uint8_t hex) {
    FILE* csv = fopen("pkmn1.csv", "r");
    PokemonSpecies species = {0};

    if (csv != NULL) {
        char buffer[1024];
        int row = 0;
        int column = 0;
        bool isFound = false;

        // iterate for each rows
        while (fgets(buffer, 1024, csv)) {
            column = 0;
            row++;

            // skip column headers
            if (row == 1)
                continue;

            // tokenize each columns, then iterate through them
            char* value = strtok(buffer, ",");
            while (value) {
                // if its not the indexNumber, skip to next row
                if (column == 0 && hex != atoi(value)) {
                    break;
                }

                // else, iterate through the other columns and store it to their respective struct field member
                isFound = true;
                switch (column)
                {
                    case 1:
                        species.dexNum = atoi(value);
                        break;

                    case 2:
                        strcpy(species.speciesName, value);
                        break;

                    case 3:
                        strcpy(species.type1, value);
                        break;

                    case 4:
                        strcpy(species.type2, value);
                        break;

                    case 5:
                        species.baseHP = atoi(value);
                        break;

                    case 6:
                        species.baseAtk = atoi(value);
                        break;
                    
                    case 7:
                        species.baseDef = atoi(value);
                        break;

                    case 8:
                        species.baseSpd = atoi(value);
                        break;

                    case 9:
                        species.baseSpe = atoi(value);
                        break;
                }
                
                value = strtok(NULL, ",");
                column++;
            }

            // after finding the correct species info, break immediately
            if (isFound) {
                break;
            }
        }

        fclose(csv);
    }

    return species;
}