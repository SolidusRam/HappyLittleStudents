#include "game.h"


void startgame()
{
    CFU_Cards *CfuCards=card_reading();
    DMG_cards *dmgCards=dmg_reading();

    Player *player = create_player();

}

Player *create_player()
{
    Player *newPlayer = (Player*)malloc(sizeof(Player));
    //username preso da input
    newPlayer->cfu_score = 0;
    newPlayer->next=NULL;
    return newPlayer;
}

void fillCFUCards(Player *player, CFU_Cards **deck_head_ref) {
    for (int i = 0; i < 5; i++) {
        if (*deck_head_ref == NULL) {
            printf("Not enough cards in the deck\n");
            return;
        }

        // Remove the card from the top of the deck
        CFU_Cards *card = *deck_head_ref;
        *deck_head_ref = card->next;

        // Add the card to the player's CFU cards
        card->next = player->hand;
        player->hand = card;
    }
}
