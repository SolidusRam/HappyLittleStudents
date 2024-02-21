#include "game_mechanics.h"

void draw(Player *head, CFU_Cards **deck_head_ref)
{
    Player *current_player =head;

    while(current_player!=NULL)
    {
        printf("Current player: %p\n", current_player);
        // Count the number of cards in the player's hand
        int hand_size = 0;
        CFU_Cards *current = current_player->hand;


        while (current != NULL) {
            printf("Current card: %p, Next card: %p\n", current, current->next);
            hand_size++;
            current =  current->next;
        }

        // Draw cards from the deck until the player has 5 cards
        while (hand_size < HAND) {
            if (*deck_head_ref == NULL) {
                //aggiungere la funzione di mescolamento quando le carte sono finite
                printf("finite le carte inizio un nuovo mescolamento\n");
                return;
            }

            // Remove the card from the top of the deck
            CFU_Cards *card = *deck_head_ref;
            *deck_head_ref = (CFU_Cards *) card->next;

            printf("Drawn card: %p, Next card in deck: %p\n", card, *deck_head_ref);

            // Add the card to the player's hand
            card->next = (struct CFU_Cards *) current_player->hand;
            current_player->hand = card;

            printf("Card added to player's hand. Current hand: %p\n", current_player->hand);

            hand_size++;
        }
        current_player=current_player->next;
    }
}

void draw_DMG(DMG_cards *head){
    //per ora solo stampa
    if(head!=NULL) {
        printf("Name: %s\n", head->name);
        printf("Description: %s\n", head->desc);
        printf("Type: %d\n", head->type);
        printf("\n");
    }

}
