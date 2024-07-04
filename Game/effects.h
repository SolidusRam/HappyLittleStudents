#ifndef HAPPYLITTLESTUDENTS_EFFECTS_H
#define HAPPYLITTLESTUDENTS_EFFECTS_H

#include "Strutture/Strutture.h"
#include "Game/game_mechanics.h"
#include "Game/game.h"

void effect_NESSUNO();

/**
 *
 * Scambia la carta punto giocata nel turno da un giocatore G1
 * con quella di un giocatore G2, con G1 e G2 scegli dal giocatore che ha giocato
 * la carta SCAMBIAC
 *
 */
void effect_SCAMBIAC(Player *current, Player *head, Board *board);

/**
 * Guarda due carte in cima al mazzo, prendine una e scarta l’altra
 * @param current il giocatore corrente
 * @param mazzo il mazzo di carte
 * @param scarti il mazzo di carte scartate
 */
void effect_SBIRCIA(Player *current, CFU_Cards *mazzo, CFU_Cards **scarti);

/**
 * Scambia il punteggio del turno maggiore e minore dopo il calcolo del punteggio di base
 * @param board il tabellone
 */
void effect_SCAMBIAP(Board *board);

/**
 * Scambia la carta punto giocata nel turno da un giocatore G1
 * con quella di un giocatore G2, con G1 e G2 scegli dal giocatore che ha giocato
 * la carta SCAMBIADS
 */
void effect_SCAMBIADS(Player *current,Player *head,Board *board,int index);

//Scarta da uno a tre carte dalla tua mano
/**
 * Scarta da uno a tre carte dalla tua mano
 */
void effect_SCARTAC(Player *current, CFU_Cards **scarti);

/**
 * Scarta una carta CFU punto con effetto e aggiungi il suo punteggio a quello del turno
 * La carta scartata deve obbligatoriamente avere un effetto
 */
void effect_SCARTAE(Player *current,Player*head,CFU_Cards* mazzo,CFU_Cards **scarti,Board *board,int index);

//Scarta una carta CFU punto e aggiungi il suo punteggio a quello del turno
/**
 * Scarta una carta CFU punto e aggiungi il suo punteggio a quello del turno
 */
void effect_SCARTAP(Player *current,CFU_Cards **scarti,Board *board,int index);

/**
 * Guarda la mano di un collega e ruba una carta a scelta.
 */
void effect_RUBA(Player *current, Player *head, Board *board);

//Annulla gli effetti di tutte le carte punto durante il turno
/**
 * Annulla gli effetti di tutte le carte punto durante il turno
 * Imposta il flag annulla a true
 */
void effect_ANNULLA(Board *board);

/**
 * Aumenta di 2 CFU il punteggio del turno di un giocatore a scelta
 */
void effect_AUMENTA(Player *current, Player *head, Board *board);

/**
 * Diminuisci di 2 CFU il punteggio del turno di un giocatore a scelta
 */
void effect_DIMINUISCI(Player *current, Player *head, Board *board);

/**
 * Inverti punteggio minimo e massimo del turno
 */
void effect_INVERTI(Board *board);

/**
 * Metti la carta Ostacolo che stai per prendere in fondo al mazzo
 */
void effect_SALVA();

/**
 * Dai la carta che stai per prendere a un altro giocatore a tua scelta
 */
void effect_DIROTTA(Player *current, Player *head, Board *board);

/**
 * Raddoppia gli effetti delle carte che aumentano o diminuiscono il punteggio (per tutti)
 * Imposta il flag molt a true
 */
void effect_DOPPIOE(Board *board);

/**
 * Applica gli effetti delle carte CFU punto
 * reinderizzando in uno switch case
 * @param current_player il giocatore corrente
 * @param head la testa della lista dei giocatori
 * @param mazzo il mazzo di carte
 * @param scarti il mazzo di carte scartate
 * @param board il tabellone
 * @param effect l'effetto della carta giocata
 * @param card_index l'indice della carta giocata nel tabellone
 */
void effects_application(Player *current_player, Player* head, CFU_Cards* mazzo, CFU_Cards **scarti, Board *board, int effect, int card_index) ;

/**
 * Applica gli effetti delle carte instantanee
 * reinderizzando in uno switch case
 */
void instant_effects(Player *current_player, Player* head, DMG_cards **dmgCards, Board *board, int effect) ;

#endif //HAPPYLITTLESTUDENTS_EFFECTS_H
