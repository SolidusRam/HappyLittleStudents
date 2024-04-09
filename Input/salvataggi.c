#include "salvataggi.h"

void lettura_salvataggio(int *numPlayers,Player **head_player,CFU_Cards**mazzo,DMG_cards**danno,CFU_Cards **scarti ){
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Cannot open file %s\n", FILENAME);
        return;
    }

    fread( numPlayers, sizeof(int), 1, file);


    printf("Number of players: %d\n", *numPlayers);

    *head_player= create_player();
    Player *current = *head_player;
    //inizio lettura player
    for (int i = 0;  i < *numPlayers; i++) {

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
            DMG_cards *new_card = malloc(sizeof(DMG_cards));
            if (new_card == NULL) {
                printf("Impossibile allocare memoria.\n");
                return;
            }

            fread(new_card, sizeof(DMG_cards), 1, file);
            new_card->next = NULL;

            if (j == 0) {
                current->dmg = new_card; // First card
            } else {
                current_dmg->next = new_card; // Subsequent cards
            }

            current_dmg = new_card;
        }
        if (numCarteDanno == 0) {
            current->dmg = NULL;
        }

        if (i < numPlayers - 1) { // if not the last player
            current->next = create_player();
            current = current->next;
        } else {
            current->next = NULL; // end of the list
        }

    }
    //letti player completamente
    //inizio lettura mazzo
    int numCarte;
    fread(&numCarte, sizeof(int ),1,file);

    CFU_Cards *prev_card = NULL;
    for (int i = 0; i < numCarte; i++) {
        CFU_Cards *new_card = malloc(sizeof(CFU_Cards));
        if (new_card == NULL) {
            printf("Impossibile allocare memoria.\n");
            return ;
        }

        fread(new_card, sizeof(CFU_Cards), 1, file);
        new_card->next = NULL;

        if (prev_card == NULL) {
            *mazzo = new_card; // Prima carta
        } else {
            prev_card->next = new_card; // Carte successive
        }

        prev_card = new_card;
    }
    //fine lettura mazzo

    int numScarti;
    fread(&numScarti, sizeof(int ),1,file);

    CFU_Cards *prev_scarto = NULL;
    for (int i = 0; i < numScarti; i++) {
        CFU_Cards *new_card = malloc(sizeof(CFU_Cards));
        if (new_card == NULL) {
            printf("Impossibile allocare memoria.\n");
            return;
        }

        fread(new_card, sizeof(CFU_Cards), 1, file);
        new_card->next = NULL;

        if (prev_scarto == NULL) {
            *scarti = new_card; // Prima carta
        } else {
            prev_scarto->next = new_card; // Carte successive
        }

        prev_scarto = new_card;
    }
    //fine lettura scarti
    //inizio lettura danno
    int numDanno;
    fread(&numDanno, sizeof(int ),1,file);

    DMG_cards *prev_dmg = NULL;
    for (int i = 0; i < numDanno; i++) {
        DMG_cards *new_card = malloc(sizeof(DMG_cards));
        if (new_card == NULL) {
            printf("Impossibile allocare memoria.\n");
            return;
        }

        fread(new_card, sizeof(DMG_cards), 1, file);
        new_card->next = NULL;

        if (prev_dmg == NULL) {
            *danno = new_card; // Prima carta
        } else {
            prev_dmg->next = new_card; // Carte successive
        }

        prev_dmg = new_card;
    }
    //fine lettura danno
    fclose(file);
}

void scrittura_salvataggio(Player **head_player, CFU_Cards **mazzo, DMG_cards **danno, CFU_Cards **scarti) {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("Cannot open file %s\n", FILENAME);
        return;
    }

    Player *current = *head_player;
    int numPlayers = 0;
    while (current != NULL) {
        numPlayers++;
        current = current->next;
    }
    fwrite(&numPlayers, sizeof(int), 1, file);

    current = *head_player;
    for (int i = 0; i < numPlayers; i++) {
        fwrite(current, sizeof(Player), 1, file);

        CFU_Cards *current_card = current->hand;
        for (int j = 0; j < HAND; j++) {
            fwrite(current_card, sizeof(CFU_Cards), 1, file);
            current_card = current_card->next;
        }

        int numCarteDanno = 0;
        DMG_cards *current_dmg = current->dmg;
        while (current_dmg != NULL) {
            numCarteDanno++;
            current_dmg = current_dmg->next;
        }
        fwrite(&numCarteDanno, sizeof(int), 1, file);

        current_dmg = current->dmg;
        for (int j = 0; j < numCarteDanno; j++) {
            fwrite(current_dmg, sizeof(DMG_cards), 1, file);
            current_dmg = current_dmg->next;
        }

        current = current->next;
    }

    // Write deck
    int numCarte = 0;
    CFU_Cards *current_deck_card = *mazzo;
    while (current_deck_card != NULL) {
        numCarte++;
        current_deck_card = current_deck_card->next;
    }
    fwrite(&numCarte, sizeof(int), 1, file);

    current_deck_card = *mazzo;
    for (int i = 0; i < numCarte; i++) {
        fwrite(current_deck_card, sizeof(CFU_Cards), 1, file);
        current_deck_card = current_deck_card->next;
    }

    // Write discards
    int numScarti = 0;
    CFU_Cards *current_discard_card = *scarti;
    while (current_discard_card != NULL) {
        numScarti++;
        current_discard_card = current_discard_card->next;
    }
    fwrite(&numScarti, sizeof(int), 1, file);

    current_discard_card = *scarti;
    for (int i = 0; i < numScarti; i++) {
        fwrite(current_discard_card, sizeof(CFU_Cards), 1, file);
        current_discard_card = current_discard_card->next;
    }

    // Write damage
    int numDanno = 0;
    DMG_cards *current_dmg_card = *danno;
    while (current_dmg_card != NULL) {
        numDanno++;
        current_dmg_card = current_dmg_card->next;
    }
    fwrite(&numDanno, sizeof(int), 1, file);

    current_dmg_card = *danno;
    for (int i = 0; i < numDanno; i++) {
        fwrite(current_dmg_card, sizeof(DMG_cards), 1, file);
        current_dmg_card = current_dmg_card->next;
    }
    int debug=1000;
    fclose(file);
}
