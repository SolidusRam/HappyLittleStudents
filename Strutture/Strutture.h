#ifndef _PR1_PROGETTO_STRUTTURE_H
#define _PR1_PROGETTO_STRUTTURE_H

#include "Input/user_input.h"

#include "time.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"

#define MAX_CHAR 32
#define DESC_MAX_CHAR 128
#define HAND 5
#define NONTIE 999
#define TOTALCFU 74
#define TOTALDMG 28

typedef enum effects{NESSUNO,SCARTAP,RUBA,SCAMBIADS,SCARTAE,SCARTAC,
                     SCAMBIAP,DOPPIOE,SBIRCIA,SCAMBIAC,ANNULLA,AUMENTA,DIMINUISCI,
                     INVERTI,SALVA,DIROTTA};

typedef enum dmg_type{STUDIO,SOPRAVVIVENZA,SOCIALE,ESAME};

/**
 * Per ogni carta sarà necessario salvare le seguenti informazioni:
 * • Nome della carta (32 caratteri, compreso terminatore)
 * • Il numero di CFU della carta
 * • Enumerazione effetto carta (vedi slide 34, 35, 45)
 * • Puntatore alla prossima carta
 */
typedef struct Cfu_cards {
    char name[MAX_CHAR];
    int cfu_points;
    enum effects effect;
    struct CFU_Cards *next;
}CFU_Cards;

/**
 * Per ogni carta sarà necessario salvare le seguenti informazioni:
• Nome della carta (32 caratteri, compreso terminatore)
• Descrizione della carta (128 caratteri, compreso terminatore)
• Enumerazione con il tipo di ostacolo:
• 1} STUDIO
• 2) SOPRAVVIVENZA
• 3) SOCIALE
• 4) ESAME
• Puntatore alla prossima carta
 */
typedef struct DMG_cards{
    char name [MAX_CHAR];
    char desc[DESC_MAX_CHAR];
    enum dmg_type type;
    struct DMG_cards *next;
}DMG_cards;

/**
 * Per ogni personaggio sarà necessario salvare le seguenti informazioni:
• Nome del personaggio (32 caratteri, compreso terminatore)
• Un array di interi di dimensione pari al numero di tipologie di ostacoli
• All’interno ci saranno salvati bonus/malus con corrispondenza biunivoca tra enumerazione e indic
 */

typedef struct Character{
    char name[MAX_CHAR];
    int bonus[4];
}Character;


/**
 * Per ogni giocatore sarà necessario salvare le seguenti informazioni:
 * • Nome utente (32 caratteri, compreso terminatore)
 *• Struttura personaggio
 *• Il numero di CFU accumulati
 *• Una lista di carte CFU
 *• Una lista di carte ostacolo
 *• Puntatore al prossimo giocatore
 *
 */

typedef struct Player{
    char username[MAX_CHAR];
    Character character;
    int cfu_score;
    CFU_Cards *hand;
    DMG_cards *dmg;
    struct Player *next;

}Player;

typedef struct Board{
    int *temporay_scores;
    int *base_scores;
    CFU_Cards **ingame_cards;
    DMG_cards *draftedDMG;
    int *flags;
    int lowest_score;
    bool molt;                   //molt è un flag che indica se il giocatore ha giocato una carta DOPPIOE o AUMENTA o DIMINUISCI
    bool annulla;               //flag che indica se il giocatore ha giocato una carta ANNULLA
    int numplayers;
    bool win;
}Board;


/**
 * Funzione che mischia le carte del mazzo
 * @param head puntatore alla testa del mazzo
 */
void shuffleCFU(CFU_Cards**);
void shuffleDmg(DMG_cards **);

/**
 * Funzione che mischia i personaggi dal dato array
 * @param characters array dei personaggi
 */
void shuffle_characters(Character*,size_t);

Player *create_player();

/**
 * Funzione che inizializza la board
 * ogni turno la board viene inizializzata con i valori base
 * @param head puntatore alla testa del mazzo
 */
void initializeBoard(Board* board,int numplayers);

void free_cards(CFU_Cards* head);
void free_dmg_cards(DMG_cards * head);
void free_players(Player *head);


//funzioni per stampa di controllo
void print_cards(CFU_Cards*);
void print_dmg_cards(DMG_cards *);

void swap(CFU_Cards * ptr1, CFU_Cards * ptr2);

int copy_array(int a[], int b[], int n, int i);

void add_card_to_hand(Player *player, CFU_Cards *new_card);

void add_card_to_scarti(CFU_Cards **scarti, CFU_Cards *card);

void remove_card_from_hand(Player *player, CFU_Cards *card);

void print_card_info(CFU_Cards *card);
void add_dmg(Player*player, DMG_cards *new_card);

void delete_player(Player **head, Player *player, CFU_Cards **scarti, DMG_cards **dmg);

int count_players(Player *head);


#endif //_PR1_PROGETTO_STRUTTURE_H
