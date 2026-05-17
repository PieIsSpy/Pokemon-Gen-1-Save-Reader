#include <stdio.h>
#include <stdint.h>
#include "../includes/box.h"
#include "../includes/checksum.h"

/*
    This function recalculates the main data checksum starting from
    player name to tileset type.

    @param fp the file to recalculate its checksum
*/
void recalculate_main_checksum(FILE* fp) {
    uint8_t checksum = 0xff;
    uint8_t data;

    fseek(fp, 0x2598, SEEK_SET);
    // for each byte from player name to tileset type, subtract to checksum
    for (int i = 0x2598; i <= 0x3522; i++) {
        fread(&data, sizeof(uint8_t), 1, fp);
        checksum -= data;
    }

    fseek(fp, 0x3523, SEEK_SET);
    fwrite(&checksum, sizeof(uint8_t), 1, fp);
}

/*
    This function recalculates edited box's checksum
    and the overall bank checksum by summing each 
    boxes' checksums.

    @param fp the the to recalculate its checksum
    @param box_num the number of the box that was edited
*/
void recalculate_bank_checksum(FILE* fp, int box_num) {
    uint8_t total_checksum = 0;
    uint8_t box_checksum = 0;
    uint8_t data;

    int box_offset = seek_box_offset(fp, box_num);
    fseek(fp, box_offset, SEEK_SET);

    // for each byte from the offset up to its last byte, add to the checksum
    for (int i = 0; i < 0x462; i++) {
        fread(&data, sizeof(uint8_t), 1, fp);
        box_checksum += data;
    }
    box_checksum = ~box_checksum;

    int starting_box_checksum_offset = (box_num < 7) ? 0x5A4D : 0x7A4D;
    int box_checksum_offset = starting_box_checksum_offset + ((box_num < 7) ? (box_num - 1) : (box_num - 7));
    fseek(fp, box_checksum_offset, SEEK_SET);
    fwrite(&box_checksum, sizeof(uint8_t), 1, fp);

    fseek(fp, starting_box_checksum_offset, SEEK_SET);

    // for each checksums of each boxes, recalculate its overall bank checksum
    for (int i = 0; i < 7; i++) {
        fread(&data, sizeof(uint8_t), 1, fp);
        total_checksum += data;
    }
    total_checksum = ~total_checksum;

    int overall_checksum_offset = (box_num < 7) ? 0x5A4C : 0x7A4C;
    fseek(fp, overall_checksum_offset, SEEK_SET);
    fwrite(&total_checksum, sizeof(uint8_t), 1, fp);
}

/*
    This function either recalculates the checksum
    of the main data or either bank 2 or 3.

    @param fp the file to recalculate its checksum
    @param box_num the number of the box that was edited
*/
void recalculate_checksum(FILE* fp, int box_num) {
    uint16_t cur_box;
    fseek(fp, 0x284C, SEEK_SET);
    fread(&cur_box, 0x2, 1, fp);
    cur_box = swap16(cur_box);
    cur_box = cur_box >> 8;

    // check first if the target box is the current box
    if (box_num - 1 == (cur_box & 0x7F)) {
        recalculate_main_checksum(fp);
    }

    // else, recalculate to banks 2 or 3
    else {
        recalculate_bank_checksum(fp, box_num);
    }
}