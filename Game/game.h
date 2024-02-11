#ifndef HAPPYLITTLESTUDENTS_GAME_H
#define HAPPYLITTLESTUDENTS_GAME_H
#include <string.h>
#include "Input/file_reading.h"
#include "Strutture/Strutture.h"
#include "Input/user_input.h"
#include "Output/stampe.h"

void game();
void setup_game(CFU_Cards *,DMG_cards*,Player *,Character[],int);

int turn(CFU_Cards *,DMG_cards*,Player *);
int game_over();

Player *create_player(CFU_Cards **);

void fillCFUCards(Player *player, CFU_Cards ** deck_head_ref) ;
void draw(Player*,CFU_Cards**);

void draw_DMG(DMG_cards*);

#endif //HAPPYLITTLESTUDENTS_GAME_H
