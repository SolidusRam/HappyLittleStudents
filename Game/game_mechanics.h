#ifndef HAPPYLITTLESTUDENTS_GAME_MECHANICS_H
#define HAPPYLITTLESTUDENTS_GAME_MECHANICS_H


#include "Strutture/Strutture.h"
#include "effects.h"

/**
 * Pesco le carte un difetto a fine round per ogni giocatore
 *
 * @param head lista dei giocatori
 * @param deck_head_ref mazzo delle carte
 *
 * */
void draw(Player*,CFU_Cards**);

/**
 * Pesco la carta Ostacolo
 * nel caso in cui il mazzo sia vuoto, le carte vengono ripescate dal file
 * @param head lista delle carte ostacolo
 * @return
 */
DMG_cards *draw_DMG(DMG_cards*);

/**
 * Permette al giocatore le 3 azioni contestuali
 * 1. Gioca una carta
 * 2. Mostra lo stato dei giocatori
 * 3. Esci dal gioco
 * @param action azione scelta
 * @param current giocatore corrente
 * @param head_player lista dei giocatori
 * @return
 */
void check_action(int action,Player *current,Player *head_player);

/**
 * Stampa le informazioni dei giocatori
 * @param current giocatore corrente
 * @param head_player lista dei giocatori
 */
void peek_players(Player *current,Player *head_player);

/**
 * Funzione che permette al giocatore di giocare una carta
 * Aggiunge la carta giocata alla lista delle carte scartate e nel tabellone
 * @param current giocatore corrente
 * @param scarti lista delle carte scartate
 * @param board tabellone di gioco
 * @param nplayer numero di giocatori
 * @param turn_number numero del turno
 */
void playCFU(Player *,CFU_Cards ***scarti,Board*,int nplayer,int turn_number);

/**
 * Controllo se la carta scelta è valida (ha un effetto non instant)
 */
int check_card(int choice,CFU_Cards*hand);

int validate(CFU_Cards*card);

/**
 * Funzione che riodina un array in ordine decrescente
 * Utilizzata per ordinare i giocatori in base al punteggio
 */
void desc_order( int n,int basescore[n],int effects[n],Player *players[n]);

/**
 * Funzione che attiva gli effetti delle carte in gioco in ordine
 */
void effects(Player*head,CFU_Cards* mazzo,CFU_Cards **scarti,Board*,int numplayers);

/**
 * controlla se il giocatore ha carte instantanee scorrendo la mano del giocatore
 * permette poi di giocare la carta instantanea
 */
void player_has_instant(Player*head,Board*board,DMG_cards *dmgCards,CFU_Cards **scarti);

/**
 * Funzione lo stato del gioco
 * @param head lista dei giocatori
 * @param board tabellone di gioco
 */
void print_board(Player *head,Board *board);

/**
 * La funzione trova il giocatore con il punteggio più alto e più basso e assegna la carta danno al giocatore con il punteggio più basso.
 * In caso di pareggio per il punteggio più basso nessun giocatore prende la carta danno e si ripete il turno fra i giocatori in pareggio.
 * In caso di pareggio per il punteggio più alto entrambi vincono il turno.
 *
 */
bool conteggi(Board *board,Player **head,CFU_Cards **scarti);

/**
 * Funzione che mostra tutti i giocatori
 * utilizzata per gli effetti
 * @param head_player lista dei giocatori
 */
void peek_all_players(Player *head_player);

#endif //HAPPYLITTLESTUDENTS_GAME_MECHANICS_H
