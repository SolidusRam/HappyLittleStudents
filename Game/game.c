#include "game.h"


void setup_game()
{
    //operazioni di lettura
    CFU_Cards *cfuCards=card_reading();
    DMG_cards *dmgCards=dmg_reading();
    printf("lettura finita \n");
    //mix
    shuffleCFU(&cfuCards);
    shuffleDmg(&dmgCards);
    printf("shuffle finito \n");

    //change this later
    int num_players= 4;
    //

    Player *head_player = create_player(&cfuCards);
    Player *current =head_player;
    printf("primo player creato");

    for (int i = 0; i < num_players-1; ++i) {
        current->next = create_player(&cfuCards);
        current=current->next;
    }
    current->next=NULL;


    print_player(head_player);
    print_cards(cfuCards);

    free_players(head_player);
    free_cards(cfuCards);
    free_dmg_cards(dmgCards);

}

Player *create_player(CFU_Cards **cards)
{
    Player *newPlayer = (Player*)malloc(sizeof(Player));
    if(newPlayer==NULL)
    {
        printf("Errore di memoria per player");
        return NULL;
    }
    //nome da ottenere tramite input
    newPlayer->username[0]='vuoto';
    //da generare con lassegnazione
    newPlayer->hand=NULL;
    fillCFUCards(newPlayer,cards);
    newPlayer->dmg=NULL;
    newPlayer->cfu_score = 0;
    //manca il character da assegnare diversamente
    newPlayer->next=NULL;
    return newPlayer;
}

void fillCFUCards(Player *player, CFU_Cards **deck_head_ref) {
    for (int i = 0; i < HAND; i++) {
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
