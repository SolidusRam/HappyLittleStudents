#include "stampe.h"

void print_player( Player *player) {
    Player *temp = player;
    printf("Nikname: %s\n", temp->username);
    printf("CFU accumulated: %d\n", temp->cfu_score);
    printf("Personaggio: %s\n", temp->character.name);
    printf("CFU Cards:\n");
    print_cards(temp->hand);
}