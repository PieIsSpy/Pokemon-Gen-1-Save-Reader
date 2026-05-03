#ifndef TRAINER_H
#define TRAINER_H

/*
    This struct represents a Trainer.

    @param name name of the trainer
    @param id id of the trainer
*/
typedef struct {
    uint8_t name[11];
    uint16_t id;
} Trainer;

Trainer read_trainer(FILE* fp);
void print_trainer(Trainer trainer);

#endif