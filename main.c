#include <stdio.h>
#include "input/file_reading.h"
#include "Strutture/Strutture.h"
#include "Game/game.h"
#include "Input/salvataggi.h"


int main() {

    Character characters[4]={0};
    int num_players=0;

    //inzializzo le varibili
    //definire meglio il numero delle carte per allocare bene la memoria

    CFU_Cards *cfuCards=NULL;//= malloc(sizeof(CFU_Cards)*TOTALCFU);
    CFU_Cards *scarti=NULL;//= malloc(sizeof(CFU_Cards)*TOTALCFU);

    DMG_cards *dmgCards=NULL;//= malloc(sizeof(DMG_cards)*TOTALDMG);

    Player *players=NULL;

    char nome_sav[MAX_CHAR];

    init_log();



    //chiedo se si vuole leggere e caricare il file di salvataggio
    game_start();
    //1 carica il file di salvataggio. 2 inizia la partita con un nuovo gioco
    int load=choose2();


    if (load==1)
    {
        //chiedo all'utente quale file vuole utilizzare
        strcpy(nome_sav,list_saves());
        lettura_salvataggio(&players,&cfuCards,&dmgCards,&scarti,&num_players,nome_sav);

    }
    if(load==2)
    {
        setup_game_test(&cfuCards,&dmgCards,&players,characters,4);
        //chiedo il numero di giocatori della partita
        num_players=players_number();

        setup_game(&cfuCards,&dmgCards,&players,characters,num_players);

        //chiedo all'utente il nuovo nome del salvataggio
        printf("Inserisci il nome per il nuovo salvataggio\n");
        player_username(nome_sav);
        strcat(nome_sav,".sav");
        printf("Il salvataggio sara' chiamato %s\n",nome_sav);

        newSave(nome_sav);
//        pesco le carte dal mazzo direttamente nel setup
    }




    printf("inizio della partita\n");

    int turn_number=1;

    while (turn_number<2){
        turn(&cfuCards,dmgCards,players,turn_number,num_players ,&scarti,nome_sav);

        dmgCards=dmgCards->next;

        turn_number++;
    }



    //memory free
    free_cards(scarti);
    free_cards(cfuCards);
    free_players(players);
    game_over();

    return 0;
}

