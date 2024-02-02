#ifndef HAPPYLITTLESTUDENTS_GAME_H
#define HAPPYLITTLESTUDENTS_GAME_H
#include <string.h>
#include "Input/file_reading.h"
#include "Strutture/Strutture.h"
#include "Input/user_input.h"

void game();
void setup_game(CFU_Cards *,DMG_cards*);

int turn();
int game_over();

Player *create_player(CFU_Cards **);

void fillCFUCards(Player *player, CFU_Cards ** deck_head_ref) ;

#endif //HAPPYLITTLESTUDENTS_GAME_H
