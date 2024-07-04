#include <stdio.h>
#include "input/file_reading.h"
#include "Strutture/Strutture.h"
#include "Game/game.h"
#include "Input/salvataggi.h"


int main() {

    Character characters[4]={0};
    int num_players=0;

    //inzializzo le varibili

    CFU_Cards *cfuCards=NULL;
    CFU_Cards *scarti=NULL;

    DMG_cards *dmgCards=NULL;

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
        //setup_game_test(&cfuCards,&dmgCards,&players,characters,4);
        //chiedo il numero di giocatori della partita
        num_players=players_number();

        setup_game(&cfuCards,&dmgCards,&players,characters,num_players);

        //chiedo all'utente il nuovo nome del salvataggio
        printf("Inserisci il nome del tuo nuovo SALVATAGGIO \n");
        player_username(nome_sav);
        strcat(nome_sav,".sav");
        printf("Il salvataggio sara' chiamato %s\n",nome_sav);

        newSave(nome_sav);
//        pesco le carte dal mazzo direttamente nel setup
    }



    printf("inizio della partita\n");

    int turn_number=1;

    bool win=false;
    while (win==false){
        win=turn(&cfuCards,dmgCards,players,turn_number,num_players ,&scarti,nome_sav);

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

