#ifndef TRAINER_H
#define TRAINER_H

/*
    This struct represents a Trainer.

    @param name name of the trainer
    @param id id of the trainer
*/
typedef struct {
    char name[11];
    uint16_t id;
} Trainer;

Trainer read_trainer(FILE* fp);

#endif