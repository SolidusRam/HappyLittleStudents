#ifndef HAPPYLITTLESTUDENTS_GAME_H
#define HAPPYLITTLESTUDENTS_GAME_H
#include <string.h>
#include "Input/file_reading.h"
#include "Strutture/Strutture.h"

void startgame();

Player *create_player();

void fillCFUCards(Player *player, CFU_Cards **deck_head_ref) ;

#endif //HAPPYLITTLESTUDENTS_GAME_H
