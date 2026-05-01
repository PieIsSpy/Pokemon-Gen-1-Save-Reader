#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "char_converter.c"
#include "trainer.c"

int main() {
    FILE *fp;
    Trainer trainer;

    fp = fopen("debug\\target.sav", "r");

    if (fp != NULL) {
        printf("Save File Recognized \n");
        trainer = read_trainer(fp);

        printf("Name: %s \n", trainer.name);
        printf("ID: %d \n", trainer.id);
        
    }
    else {
        printf("ERROR: FileNotFoundException \n");
    }

    fclose(fp);
    return 0;
}