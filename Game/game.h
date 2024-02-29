#ifndef HAPPYLITTLESTUDENTS_GAME_H
#define HAPPYLITTLESTUDENTS_GAME_H
#include <string.h>
#include "Input/file_reading.h"
#include "Strutture/Strutture.h"
#include "Input/user_input.h"
#include "Output/stampe.h"
#include "Game/game_mechanics.h"
#include "Input/salvataggi.h"


void game();
void setup_game(CFU_Cards **,DMG_cards**,Player **,Character[],int);

int turn(CFU_Cards**,DMG_cards*,Player *,int );

int game_over();

void fillCFUCards(Player *player, CFU_Cards ** deck_head_ref) ;


#endif //HAPPYLITTLESTUDENTS_GAME_H
