#include <stdio.h>
#include "input/file_reading.h"
#include "Strutture/Strutture.h"
#include "Game/game.h"
#include "Input/salvataggi.h"

//funzione di setup del gioco modidicata per il test
void setup_game_test(CFU_Cards **cfuCards,DMG_cards **dmgCards,Player **head_player,Character character[4],int num_players)
{
    //operazioni di lettura
    *cfuCards=card_reading();
    *dmgCards=dmg_reading();
    printf("lettura finita \n");
    //mix
    shuffleCFU(cfuCards);
    shuffleDmg(dmgCards);
    printf("shuffle finito \n");

    //lettura personaggi
    character_reading(character);

    shuffle_characters(character,num_players);

    //creazione personaggio
    //sto chiedendo anche l'username

    //creo il primo player
    *head_player = create_player();
    Player *current = *head_player;
    current->character=character[0];
    //player_username(current->username);
    fillCFUCards(current,cfuCards);

    //forzatura sull'effetto
    current->hand->effect=SBIRCIA;

    for (int i = 1; i < num_players; i++) {
        current->next = create_player();
        current=current->next;
        current->character=character[i];
        fillCFUCards(current,cfuCards);
    }
    current->next=NULL;
     /*
      *
        for (int i = 0; i < num_players-1; ++i) {
        current->next = create_player();
        current=current->next;
        current->character=character[i];
        player_username(current->username);
        fillCFUCards(current,cfuCards);
        }
        current->next=NULL;
      *
      * */

}

int main() {


    Character characters[4];
    int num_players = 2;

    CFU_Cards *cfuCards= malloc(sizeof(CFU_Cards)*TOTALCFU);
    CFU_Cards *scarti= malloc(sizeof(CFU_Cards)*TOTALCFU);

    DMG_cards *dmgCards= malloc(sizeof(DMG_cards)*TOTALDMG);

    Player *players =malloc(sizeof(Player)*TOTALDMG);


    setup_game_test(&cfuCards,& dmgCards, &players, characters, num_players);
    print_cards(cfuCards);
    turn(&cfuCards,dmgCards, players, 1, num_players,scarti);

    int ff = 000;

    free_cards(scarti);
    free_cards(cfuCards);



    free_players(players);

    return 0;
}

