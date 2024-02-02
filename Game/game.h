#ifndef HAPPYLITTLESTUDENTS_GAME_H
#define HAPPYLITTLESTUDENTS_GAME_H
#include <string.h>
#include "Input/file_reading.h"
#include "Strutture/Strutture.h"

void setup_game();

Player *create_player(CFU_Cards **);

void fillCFUCards(Player *player, CFU_Cards ** deck_head_ref) ;

#endif //HAPPYLITTLESTUDENTS_GAME_H
