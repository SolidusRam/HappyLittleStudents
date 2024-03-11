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
    do {
        switch (action) {
            case 1:
                //gioca la carta CFU
                break;
            case 2:
                //Stampa le informazioni del giocatore
                peek_players(current,head_player);
                action=ask_for_action();
                break;
            case 3:
                //esci dal gioco
                printf("Chiusura del gioco ... \n");
                exit(333);
                break;
            default:
                printf("Azione non consentita\n");
                exit(1);
        }
    } while (action==2);
}

void peek_players(Player *current,Player *head_player){

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

void playCFU(Player *player,Board *board,int nplayer){

    CFU_Cards *temp=player->hand;

    printf("Hai in mano queste carte:\n");
    print_cards(temp);

    //Suggerimento sulla carta da giocare
    suggerimento(temp,*board);

    //chiedo il numero della carta da giocare
    //stampa

    int scelta=1;

    /*
    do {
        scelta=ask_for_card();

    } while (check_card(scelta,player->hand));

     for (int i = 1; i < scelta; ++i) {
        temp = temp->next;
    }
    */


    addCardToIngameCards(board,temp);
    //aggiungo punteggio in base alla carta giocata
    int score=0;
    score=board->ingame_cards->cfu_points;

    //aggiungo bonus in base al personaggio
    int bonus=board->draftedDMG->type;
    int perso = player->character.bonus[bonus];

    board->temporay_scores[nplayer]=score;


}

int check_card(int choice,CFU_Cards*hand){
    CFU_Cards *tmp=hand;
    int isvalid=0;

    for (int i = 1; i < choice; ++i) {
        tmp=tmp->next;
    }
    isvalid = validate(tmp);

    return !isvalid;
}

int validate(CFU_Cards*card){
    if(card->effect<AUMENTA)
    {
        //Stampo le informazioni della carta (la carta va bene)
        return 1;
    }
    else
    {
        //la carta è una carta instantanea
        printf("La carta che vuoi giocare è una carta instantanea, "
               "seleziona una carta valida per questo step del gioco\n");
        return 0;
    }
}

void suggerimento(CFU_Cards*mano, Board board){
    for (int i = 0; i < HAND; ++i) {
        if (mano->effect>=AUMENTA)
        {
            printf("La carta %s per l'opzione %d può essere giocata "
                   "dopo il calcolo del punteggio\n",mano->name,i);
            board.flags[i]=1;
        }
        mano = mano->next;
    }
}

int bubbleSort(CFU_Cards ** head, int count)
{
    CFU_Cards ** h;
    int i, j, swapped;

    for (i = 0; i <= count; i++) {

        h = head;
        swapped = 0;

        for (j = 0; j < count - i - 1; j++) {

            CFU_Cards * p1 = *h;
            CFU_Cards * p2 = p1->next;

            if (p1->cfu_points > p2->cfu_points) {

                /* update the link after swapping */
                *h = swap(p1, p2);
                swapped = 1;
            }

            h = &(*h)->next;
        }

        /* break if the loop ended without any swap */
        if (swapped == 0)
            break;
    }
}

void addCardToIngameCards(Board *board, CFU_Cards *card) {
    CFU_Cards *newNode;
    newNode = card;
    newNode->next = board->ingame_cards;
    board->ingame_cards = newNode;
}
