#include <stdio.h>
#include <stdlib.h>
#include "input/file_reading.h"
#include "Strutture/Strutture.h"


int main() {
    DMG_cards * cards = dmg_reading();
    if (cards == NULL) {
        return 1;
    }

    /*
    print_cards(head);

    printf("-----");
    shuffleCFU(&head);

    print_cards(head);
    */

    print_dmg_cards(cards);

    free_dmg_cards(cards);

    return 0;
}
