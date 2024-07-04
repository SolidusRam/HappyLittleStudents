#ifndef HAPPYLITTLESTUDENTS_GAME_H
#define HAPPYLITTLESTUDENTS_GAME_H

#include "Input/file_reading.h"
#include "Strutture/Strutture.h"
#include "Input/user_input.h"
#include "Output/stampe.h"
#include "Game/game_mechanics.h"
#include "Input/salvataggi.h"

#include <string.h>


/**
 * Funzione che inizializza il gioco per un nuovo salvataggio
 *
 * @param cfuCards puntatore alla testa della lista di carte CFU
 * @param dmgCards puntatore alla testa della lista di carte DMG
 * @param head_player puntatore alla testa della lista di giocatori
 * @param character array di personaggi
 * @param num_players numero di giocatori
 */
void setup_game(CFU_Cards **,DMG_cards**,Player **,Character[],int);

void setup_game_test(CFU_Cards **,DMG_cards**,Player **,Character[],int);

/**
 * Funzione che gestisce i turni dei giocatori
 * @param sav nome del file di salvataggio
 * @return true se la partita è finita, false altrimenti
 */
bool turn(CFU_Cards**,DMG_cards*,Player *,int ,int ,CFU_Cards **scarti,char* sav);

int game_over();

/**
 * Funzione che riempie la mano di un giocatore con le carte CFU
 * @param player lista dei giocatori
 * @param deck_head_ref mazzo di carte
 */
void fillCFUCards(Player *player, CFU_Cards ** deck_head_ref) ;

/**
 * Funzione che controlla se un giocatore ha vinto
 * Oppure se c'è un giocatore che ha perso
 * @param player lista dei giocatori
 * @param deck_head_ref mazzo di carte
 */
Player * win_check(Player* head,int numplayers,DMG_cards *scarti,Board *board);

/**
 * La funzione controlla se il giocatore ha la combinazione
 * di carte ostacolo che lo fa eliminare dal gioco
 * @param count flag che indica se il giocatore è eliminato
 * @return 1 se il giocatore è eliminato, 0 altrimenti
 */
int dmg_count( int *count);

#endif //HAPPYLITTLESTUDENTS_GAME_H
