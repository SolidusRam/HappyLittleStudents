#include <stdio.h>
#include "input/file_reading.h"
#include "Strutture/Strutture.h"
#include "Game/game.h"
#include "Input/salvataggi.h"


int main() {

    //game();
    Player *giocatori;
    DMG_cards *danno;
    CFU_Cards *mazzo ;
    CFU_Cards *scarti;
    lettura_salvataggio(&giocatori,&mazzo,&danno,&scarti);

        /*
        DMG_cards * cards = dmg_reading();
        if (cards == NULL) {
            return 1;
        }


        print_cards(head);

        printf("-----");
        shuffleCFU(&head);

        print_cards(head);


        print_dmg_cards(cards);

        free_dmg_cards(cards);


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
