#ifndef HAPPYLITTLESTUDENTS_EFFECTS_H
#define HAPPYLITTLESTUDENTS_EFFECTS_H

#include "Strutture/Strutture.h"
#include "Game/game_mechanics.h"
#include "Game/game.h"

void effect_NESSUNO();

//Scambia questa carta con quella di un altro giocatore, purché senza effetto
void effect_SCAMBIAC(Player *current,Player*head,CFU_Cards* mazzo,CFU_Cards **scarti,Board *board,int card_index);

//Guarda due carte in cima al mazzo, prendine una e scarta l’altra
void effect_SBIRCIA(Player *current,Player*head,CFU_Cards* mazzo,CFU_Cards **scarti,Board *board);

//Scambia il punteggio del turno maggiore e minore dopo il calcolo del punteggio di base
void effect_SCAMBIAP(Player *current,Player*head,CFU_Cards* mazzo,CFU_Cards **scarti,Board *board);

//Scarta da uno a tre carte dalla tua mano
void effect_SCAMBIADS(Board *board,int index);

//Scarta da uno a tre carte dalla tua mano
void effect_SCARTAC(Player *current,Player*head,CFU_Cards* mazzo,CFU_Cards **scarti,Board *board);

//Scarta una carta CFU punto con effetto e aggiungi il suo punteggio a quello del turno
void effect_SCARTAE(Player *current,Player*head,CFU_Cards* mazzo,CFU_Cards **scarti,Board *board);

//Scambia la carta punto giocata nel turno da un giocatore G1 con quella di un giocatore G2, con G1 e G2
void effect_SCARTADS(Player *current,CFU_Cards **scarti,Board *board,int index);

//Scarta una carta CFU punto e aggiungi il suo punteggio a quello del turno
void effect_SCARTAP(Player *current,CFU_Cards **scarti,Board *board,int index);

//Guarda la mano di un collega e ruba una carta a scelta.
void effect_RUBA(Player *current, Player *head, Board *board);

//Annulla gli effetti di tutte le carte punto durante il turno
void effect_ANNULLA(Player *current,Player*head,CFU_Cards* mazzo,CFU_Cards **scarti,Board *board);

//Raddoppia gli effetti delle carte che aumentano o diminuiscono il punteggio (per tutti)
void effect_AUMENTA(Player *current,Player*head,CFU_Cards* mazzo,CFU_Cards **scarti,Board *board);

//Raddoppia gli effetti delle carte che aumentano o diminuiscono il punteggio (per tutti)
void effect_DIMINUISCI(Player *current,Player*head,CFU_Cards* mazzo,CFU_Cards **scarti,Board *board);

//Inverti punteggio minimo e massimo del turno
void effect_INVERTI(Player *current,Player*head,CFU_Cards* mazzo,CFU_Cards **scarti,Board *board);

//Mettila carta Ostacolo che stai per prendere in fondo al mazzo
void effect_SALVA(Player *current,Player*head,CFU_Cards* mazzo,CFU_Cards **scarti,Board *board);

//Dai la carta che stai per prendere a un altro giocatore a tua scelta
void effect_DIROTTA(Player *current,Player*head,CFU_Cards* mazzo,CFU_Cards **scarti,Board *board);

//Raddoppia gli effetti delle carte che aumentano o diminuiscono il punteggio (per tutti)
void effect_DOPPIOE(Player *current,Player*head,CFU_Cards* mazzo,CFU_Cards **scarti,Board *board);


void effects_application(Player *current_player, Player* head, CFU_Cards* mazzo, CFU_Cards **scarti, Board *board, int effect, int card_index) {
    // Switch on the effect code
    switch (effect) {
        case NESSUNO:
            effect_NESSUNO();
            break;
        case SCARTAP:
            effect_SCARTAP(current_player, scarti, board,card_index);
            break;
        case RUBA:
            effect_RUBA(current_player, head, board);
            break;
        case SCAMBIADS:
            effect_SCAMBIADS(board,card_index);
            break;
        case SCARTADS:
            effect_SCARTADS(current_player,scarti,board,card_index);
            break;
        case SCARTAE:
            effect_SCARTAE(current_player, head, mazzo, scarti, board);
            break;
        case SCARTAC:
            effect_SCARTAC(current_player, head, mazzo, scarti, board);
            break;
        case SCAMBIAP:
            effect_SCAMBIAP(current_player, head, mazzo, scarti, board);
            break;
        case DOPPIOE:
            effect_DOPPIOE(current_player, head, mazzo, scarti, board);
            break;
        case SBIRCIA:
            effect_SBIRCIA(current_player, head, mazzo, scarti, board);
            break;
        case SCAMBIAC:
            effect_SCAMBIAC(current_player, head, mazzo, scarti, board, card_index);
            break;
        case ANNULLA:
            effect_ANNULLA(current_player, head, mazzo, scarti, board);
            break;
        case AUMENTA:
            effect_AUMENTA(current_player, head, mazzo, scarti, board);
            break;
        case DIMINUISCI:
            effect_DIMINUISCI(current_player, head, mazzo, scarti, board);
            break;
        case INVERTI:
            effect_INVERTI(current_player, head, mazzo, scarti, board);
            break;
        case SALVA:
            effect_SALVA(current_player, head, mazzo, scarti, board);
            break;
        case DIROTTA:
            effect_DIROTTA(current_player, head, mazzo, scarti, board);
            break;

        default:
            printf("Errore nell'applicazione dell'effetto, codice effetto non consentito\n");
            exit(333);
    }
}

#endif //HAPPYLITTLESTUDENTS_EFFECTS_H
