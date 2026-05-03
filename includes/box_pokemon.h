#ifndef BOX_POKEMON_H
#define BOX_POKEMON_H

#pragma pack(1)
/*
    This structure represents a `Pokemon` stored in a `Box`.

    @param indexNum the index number of the Pokemon species
    @param curHP the current HP of the Pokemon
    @param levelRedundant a redundant level holder
    @param status the status condition of the Pokemon
    @param type1 the 1st type of the Pokemon
    @param type2 the 2nd type of the Pokemon
    @param catchRate the catch rate of the Pokemon species (when it was caught)
    @param move1 index number of move1
    @param move2 index number of move2
    @param move3 index number of move3
    @param move4 index number of move4
    @param tid the original trainer's ID
    @param exp the experience points accumulated
    @param hpEV the HP EV of the pokemon
    @param atkEV the attack EV of the pokemon
    @param defEV the defense EV of the pokemon
    @param spdEV the speed EV of the pokemon
    @param speEV the special EV of the pokemon
    @param ivs the IVs of the Pokemon
    @param move1PP the PP info of move1
    @param move2PP the PP info of move2
    @param move3PP the PP info of move3
    @param move4PP the PP info of move4
*/
typedef struct {
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
} BoxPokemon;
#pragma pack()

#endif