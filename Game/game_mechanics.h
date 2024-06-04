#ifndef HAPPYLITTLESTUDENTS_GAME_MECHANICS_H
#define HAPPYLITTLESTUDENTS_GAME_MECHANICS_H


#include "Strutture/Strutture.h"
#include "effects.h"

void draw(Player*,CFU_Cards**);

DMG_cards *draw_DMG(DMG_cards*);

void check_action(int action,Player *current,Player *head_player);

void peek_players(Player *current,Player *head_player);

void playCFU(Player *,CFU_Cards ***scarti,Board*,int nplayer);

int check_card(int choice,CFU_Cards*hand);

int validate(CFU_Cards*card);

void suggerimento(CFU_Cards *mano,Board board);

void addCardToIngameCards(Board *board, CFU_Cards *card);

void desc_order( int n,int basescore[n],int effects[n],Player *players[n]);

void effects(Player*head,CFU_Cards* mazzo,CFU_Cards **scarti,Board*,int numplayers);

void player_has_instant(Player*head,CFU_Cards **scarti,Board*board);

void print_board(Player *head,Board *board);

void salva_dmg(DMG_cards *dmgCards);

#endif //HAPPYLITTLESTUDENTS_GAME_MECHANICS_H
