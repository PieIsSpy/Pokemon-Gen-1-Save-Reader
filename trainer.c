struct Trainer {
    char name[11];
    char id[2];
} typedef Trainer;

Trainer read_trainer(FILE* fp) {
    Trainer trainer;

    fseek(fp, 0x2598, SEEK_SET);
    fread(trainer.name, sizeof(trainer.name), 1, fp);

    fseek(fp, 0x2605, SEEK_SET);
    fread(trainer.id, sizeof(trainer.id), 1, fp);

    return trainer;
}