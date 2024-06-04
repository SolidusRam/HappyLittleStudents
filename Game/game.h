#ifndef HAPPYLITTLESTUDENTS_GAME_H
#define HAPPYLITTLESTUDENTS_GAME_H

#include "Input/file_reading.h"
#include "Strutture/Strutture.h"
#include "Input/user_input.h"
#include "Output/stampe.h"
#include "Game/game_mechanics.h"
#include "Input/salvataggi.h"

#include <string.h>


void game();
void setup_game(CFU_Cards **,DMG_cards**,Player **,Character[],int);

int turn(CFU_Cards**,DMG_cards*,Player *,int ,int ,CFU_Cards **scarti);

int game_over();

void fillCFUCards(Player *player, CFU_Cards ** deck_head_ref) ;

bool conteggi(Board *board,Player **head,DMG_cards *dmgCards);

void win_check(Player* head,int numplayers,DMG_cards *scarti);

int dmg_count( int *dmg);

void tie_turn(CFU_Cards **deck_head_ref,DMG_cards *drafted,Player *head, CFU_Cards*scarti);

#endif //HAPPYLITTLESTUDENTS_GAME_H
