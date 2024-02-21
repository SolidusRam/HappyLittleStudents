#include "salvataggi.h"

void printFileContents(Player **head_player) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Cannot open file %s\n", FILENAME);
        return;
    }

    int numPlayers;
    fread(&numPlayers, sizeof(int), 1, file);

    printf("Number of players: %d\n", numPlayers);

    *head_player= create_player();
    Player *current = *head_player;

    for (int i = 0; i < numPlayers; i++) {

        int numCarteDanno;


        fread(current, sizeof(Player), 1, file);

        CFU_Cards *current_card = malloc(sizeof(CFU_Cards));
        current->hand=current_card;

        DMG_cards *current_dmg= malloc(sizeof(DMG_cards));
        current->dmg=current_dmg;

        for (int j=0;j<HAND;j++) {

            fread(current_card, sizeof(CFU_Cards), 1, file);
            if (j < 4) { // if not the last card
                current_card->next = malloc(sizeof(CFU_Cards));
                current_card = current_card->next;
            } else {
                current_card->next = NULL; // end of the list
            }

        }

        fread(&numCarteDanno, sizeof(int), 1, file);

        for (int j = 0; j < numCarteDanno; ++j) {
            fread(current_dmg, sizeof(DMG_cards), 1, file);
            if (j < numCarteDanno) { // if not the last card
                current_dmg->next = malloc(sizeof(DMG_cards));
                current_dmg = current_dmg->next;
            } else {
                current_dmg->next = NULL; // end of the list
            }
        }

        if (i < numPlayers - 1) { // if not the last player
            current->next = create_player();
            current = current->next;
        } else {
            current->next = NULL; // end of the list
        }

    }
    int pazzodicazzo=1000;
}

