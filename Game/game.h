#ifndef HAPPYLITTLESTUDENTS_GAME_H
#define HAPPYLITTLESTUDENTS_GAME_H
#include <string.h>

#include "Strutture/Strutture.h"

void loadgame();

void fill_characters(int);

Player *create_player(char *username,CFU_Cards *hand,Character character);

#endif //HAPPYLITTLESTUDENTS_GAME_H
