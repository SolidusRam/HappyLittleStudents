#ifndef _PR1_PROGETTO_STRUTTURE_H
#define _PR1_PROGETTO_STRUTTURE_H

#define MAX_CHAR 32
#define HAND 5
#define DMG_POINTS 5

typedef enum effects{NESSUNO,SCARTAP,RUBA,SCAMBIADS,SCARTADS,SCARTAE,SCARTAC,
                     SCAMBIAP,DOPPIOE,SBIRCIA,SCAMBIAC,ANNULLA,AUMENTA,DIMINUISCI,
                     INVERTI,SALVA,DIROTTA};

typedef enum dmg_type{STUDIO,SOPRAVVIVENZA,SOCIALE,ESAME};

typedef struct Cfu_cards {
    //delete this later
    int num;
    //
    char name[MAX_CHAR];
    int cfu_points;
    enum effects effect;
    struct CFU_Cards *next;
}CFU_Cards;

typedef struct Dmg_cards{
    char name [MAX_CHAR];
    char desc[MAX_CHAR];
    enum dmg_type type;
    struct Dmg_cards *next;
}Dmg_cards;


typedef struct Character{
    char name[MAX_CHAR];
    int bonus[4];
}Character;

typedef struct Player{
    char username[MAX_CHAR];
    int cfu_score;
    CFU_Cards hand[HAND];
    Dmg_cards dmg[DMG_POINTS];
    struct Player *next;

}Player;




#endif //_PR1_PROGETTO_STRUTTURE_H
