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

void check_action(int action,Player *current,Player *head_player)
{
    switch (action) {
        case 1:
            //gioca la carta CFU

            break;
        case 2:
            //Stampa le informazioni del giocatore
            peek_players(current,head_player);
            break;
        case 3:
            //esci dal gioco
            printf("Chiusura del gioco ... \n");
            exit(333);
            break;
        default:
            printf("Azione non consentita\n");
    }
    if(action==2){
        action=ask_for_action();
        check_action(action,current,head_player);
    }

}

void peek_players(Player *current,Player *head_player){\

    printf("Stampo le informazioni riguardanti i giocatori:\n");
    Player *temp=head_player;
    while(temp!=NULL)
    {
        if(current->character.name!=temp->character.name)
        {
            printf("%s ha %d punti e tot danni\n",temp->username,temp->cfu_score);
        }
        temp=temp->next;
    }
}
void playCFU(Player *current){

}
