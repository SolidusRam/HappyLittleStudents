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




    //chiedo se si vuole leggere e caricare il file di salvataggio
    game_start();
    //1 carica il file di salvataggio. 2 inizia la partita con un nuovo gioco
    int load=choose2();
//    int load=2;


    //lettura salvataggio buggata
    if (load==1)
    {
        lettura_salvataggio(&players,&cfuCards,&dmgCards,&scarti);

    }
    if(load==2)
    {
        //chiedo il numero di giocatori della partita
        num_players=players_number();

        setup_game(&cfuCards,&dmgCards,&players,characters,num_players);

//        num_players=2;
//        setup_game_test(&cfuCards,&dmgCards,&players,characters,num_players);

        //pesco le carte dal mazzo direttamente nel setup
    }




    printf("inizio della partita\n");

    turn(&cfuCards,dmgCards,players,0,num_players ,&scarti);


//    int turn_number=0;
//
//    while (turn_number<10){
//        turn(&cfuCards,dmgCards,players,turn_number,num_players ,&scarti);
//
//        dmgCards=dmgCards->next;
//
//        turn_number++;
//    }




    /*
    int check=0;
    //turno da reiterare per variabile di ritorno
    for(int turn_number=0;check==0;turn_number++)
    {
        check=turn(&cfuCards,dmgCards,players,turn_number,numplyers );
    }
    */


    //memory free
//    free_cards(scarti);
//    free_cards(cfuCards);
//    free_players(players);
    //questo non funziona
    //free_dmg_cards(dmgCards);
    game_over();

    return 0;
}

