#ifndef CHECKSUM_H
#define CHECKSUM_H

#include <stdio.h>

void recalculate_main_checksum(FILE* fp);
void recalculate_bank_checksum(FILE* fp, int box_num);
void recalculate_checksum(FILE* fp, int box_num);

#endif