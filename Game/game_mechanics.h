#ifndef HAPPYLITTLESTUDENTS_GAME_MECHANICS_H
#define HAPPYLITTLESTUDENTS_GAME_MECHANICS_H


#include "Strutture/Strutture.h"

void draw(Player*,CFU_Cards**);

void draw_DMG(DMG_cards*);

void check_action(int action,Player *current,Player *head_player);

void peek_players(Player *current,Player *head_player);

void playCFU(Player *current);

#endif //HAPPYLITTLESTUDENTS_GAME_MECHANICS_H
