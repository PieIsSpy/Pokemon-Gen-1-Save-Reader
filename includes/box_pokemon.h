#ifndef BOX_POKEMON_H
#define BOX_POKEMON_H

#pragma pack(1)
struct BoxPokemon {
    uint8_t indexNum;
    uint16_t curHP;
    uint8_t levelRedundant; // what the hell even is this
    uint8_t status;
    uint8_t type1;
    uint8_t type2;
    uint8_t catchRate;
    uint8_t move1;
    uint8_t move2;
    uint8_t move3;
    uint8_t move4;
    uint16_t tid;
    uint24_t exp;
    uint16_t hpEV;
    uint16_t atkEV;
    uint16_t defEV;
    uint16_t spdEV;
    uint16_t speEV;
    uint16_t ivs;
    uint8_t move1PP;
    uint8_t move2PP;
    uint8_t move3PP;
    uint8_t move4PP;
} typedef BoxPokemon;
#pragma pack()

#endif