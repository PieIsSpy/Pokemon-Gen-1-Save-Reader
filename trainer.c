/*
    This struct represents a Trainer.

    @param name name of the trainer
    @param id id of the trainer
*/
struct Trainer {
    char name[11];
    char id[2];
} typedef Trainer;

/*
    This function gets the trainer's name and id from the save file
    and stores them into a `Trainer` struct and returns it.

    @param fp the save file to be read
    @returns the trainer read from the save file.
*/
Trainer read_trainer(FILE* fp) {
    Trainer trainer;

    fseek(fp, 0x2598, SEEK_SET);
    fread(trainer.name, sizeof(trainer.name), 1, fp);
    strcpy(trainer.name, convert_text(trainer.name, 11));

    fseek(fp, 0x2605, SEEK_SET);
    fread(trainer.id, sizeof(trainer.id), 1, fp);

    return trainer;
}