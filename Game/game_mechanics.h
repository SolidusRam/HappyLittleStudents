#ifndef HAPPYLITTLESTUDENTS_GAME_MECHANICS_H
#define HAPPYLITTLESTUDENTS_GAME_MECHANICS_H


#include "Strutture/Strutture.h"

void draw(Player*,CFU_Cards**);

void draw_DMG(DMG_cards*);

void check_action(int action,Player *current,Player *head_player);

void peek_players(Player *current,Player *head_player);

void playCFU(Player *,Board*,int nplayer);

int check_card(int choice,CFU_Cards*hand);

int validate(CFU_Cards*card);

void suggerimento(CFU_Cards *mano,Board board);

void addCardToIngameCards(Board *board, CFU_Cards *card);

//Function to perform bubble sort on the linked list
int bubbleSort(CFU_Cards ** head, int count);
#endif //HAPPYLITTLESTUDENTS_GAME_MECHANICS_H
