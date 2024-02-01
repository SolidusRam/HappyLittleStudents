#include <stdio.h>
#include "input/file_reading.h"
#include "Strutture/Strutture.h"
#include "Game/game.h"




int main() {


    CFU_Cards * cards = card_reading();

    //print_cards(cards);

    Player *player= create_player();

    fillCFUCards(player,&cards);
    print_player(player);

    printf("-----");
    //print_cards(cards);
    free_players(player);
    free_cards(cards);
/*
    printf("-----");
    shuffleCFU(&head);

    print_cards(head);


    print_dmg_cards(cards);

    free_dmg_cards(cards);
    */

/*
    Character characters[4];
    character_reading(characters, 4);

    // Print to check
    for (int i = 0; i < 4; i++) {
        printf("%s: ", characters[i].name);
        for (int j = 0; j < 4; j++) {
            printf("%d ", characters[i].bonus[j]);
        }
        printf("\n");
    }
*/
    return 0;
}
