#ifndef HAPPYLITTLESTUDENTS_GAME_MECHANICS_H
#define HAPPYLITTLESTUDENTS_GAME_MECHANICS_H


#include "Strutture/Strutture.h"
#include "effects.h"

void draw(Player*,CFU_Cards**);

void draw_DMG(DMG_cards*);

void check_action(int action,Player *current,Player *head_player);

void peek_players(Player *current,Player *head_player);

void playCFU(Player *,Board*,int nplayer);

int check_card(int choice,CFU_Cards*hand);

int validate(CFU_Cards*card);

void suggerimento(CFU_Cards *mano,Board board);

void addCardToIngameCards(Board *board, CFU_Cards *card);

int desc_order( int n,int a[n]);

void effects(Player*head,CFU_Cards* mazzo,CFU_Cards **scarti,Board*,int numplayers);

void effects_application(Player *current,Player*head,CFU_Cards* mazzo,CFU_Cards **scarti,Board*, int effect);


#endif //HAPPYLITTLESTUDENTS_GAME_MECHANICS_H
