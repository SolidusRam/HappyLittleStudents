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
            printf("%s ha %d punti dallo scorso turno, e tot danni\n",temp->username,temp->cfu_score);
            DMG_cards *tmpdmg=temp->dmg;
            while (tmpdmg!=NULL)
            {
                printf("Carta danno: %s\n",current->dmg->name);
                tmpdmg=tmpdmg->next;
            }
        }
        temp=temp->next;
    }
}


void playCFU(Player *player,CFU_Cards ***scarti,Board *board,int nplayer){

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


    //aggiungo la carta in gioco
    board->ingame_cards[nplayer]=temp;


    //aggiungo punteggio in base alla carta giocata
    int score=0;
    score=board->ingame_cards[nplayer]->cfu_points;

    //aggiungo bonus in base al personaggio
    int tipo=board->draftedDMG->type;
    int bonus_char = player->character.bonus[tipo];

    board->temporay_scores[nplayer]=score+bonus_char;
    board->base_scores[nplayer]=score;

    printf("\n");
    printf("%s ha giocato la carta %s e ha ottenuto %d punti\n",player->username,board->ingame_cards[nplayer]->name,board->base_scores[nplayer]);
    printf("\n");



    //aggiungo la carta agli scarti e la rimuovo dalla mano
    temp->next= (struct CFU_Cards *) **scarti;
    **scarti=temp;

    //rimuovo la carta dalla mano
    remove_card_from_hand(player,temp);
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

// Function to sort the arrays in descending order
void desc_order(int n, int base_score[n], int effect[n], Player* players[n]){
    int i, j;
    // Iterate over each element of the base_score array
    for (i = 0; i < n; i++) {
        // For each element, iterate over the remaining elements
        for (j = i + 1; j < n; j++) {
            // If the current element is less than the next element
            if (base_score[i] < base_score[j]) {
                // Swap the base_score elements
                int temp_score = base_score[i];
                base_score[i] = base_score[j];
                base_score[j] = temp_score;

                // Swap the corresponding effect elements
                int temp_effect = effect[i];
                effect[i] = effect[j];
                effect[j] = temp_effect;

                // Swap the corresponding players
                Player* temp_player = players[i];
                players[i] = players[j];
                players[j] = temp_player;
            }
        }
    }
}
/* gli effetti vengono giocati in base al punteggio delle carte in ordine decrecente
 * base score è il punteggio della carta giocata e ne determina l'ordine
 *
 */
void effects(Player*head, CFU_Cards* mazzo, CFU_Cards **scarti, Board *board, int numplayers){
    int base_score[numplayers];
    int effect[numplayers];
    Player* players[numplayers];
    Player *current=head;

    for (int i = 0; i < numplayers; i++) {
        base_score[i]=board->base_scores[i];
        effect[i]=board->ingame_cards[i]->effect;
        players[i]=current;
        current=current->next;
    }

    desc_order(numplayers, base_score, effect, players);
    for (int j = 0; j < numplayers; ++j) {

        printf("Giocatore: %s, gioca la carta con effetto %d\n",players[j]->character.name,effect[j]);
        printf("Nome carta %s",board->ingame_cards[j]->name);
        effects_application(players[j], head, mazzo, scarti, board, effect[j],j);

    }
}

//controlla se il giocatore ha carte instantanee scorrendo la mano del giocatore
//in caso positivo aggiorna il flag di board
void player_has_instant(Player*head,CFU_Cards **scarti,Board*board){

    Player *current=head;
    for (int i = 0; i < board->numplayers; ++i)
    {
        CFU_Cards *temp=current->hand;
        for (int j = 0; j < HAND; ++j) {
            if(temp->effect>=AUMENTA)
            {
                printf("Il giocatore %s ha una carta instantanea\n",current->username);
                printf("Vuoi giocarla? 1 per si, 0 per no\n");
                int choice;
                scanf("%d",&choice);
                while (choice!=1 && choice!=0)
                {
                    printf("Scelta non valida, riprova\n");
                    scanf("%d",&choice);
                }
                if(choice==1)
                {
                    add_card_to_scarti(scarti,temp);
                    effects_application(current,head,NULL,scarti,board,temp->effect,0);
                }
            }
            temp = temp->next;
        }
        current=current->next;
    }
}


void print_board(Player *head,Board *board){
    int max=board->temporay_scores[0];
    int min=board->temporay_scores[0];
    int index_max=0;
    int index_min=0;
    printf("Punteggi temporanei: \n");
    Player *current=head;
    for (int i = 0; i < board->numplayers; ++i) {
        if(board->temporay_scores[i]>max)
        {
            max=board->temporay_scores[i];
            index_max=i;
        }
        if(board->temporay_scores[i]<min)
        {
            min=board->temporay_scores[i];
            index_min=i;
        }

        current->cfu_score=board->temporay_scores[i];
        printf("%s ha ottenuto %d punti questo turno \n",current->username,board->temporay_scores[i]);
        current=current->next;
    }
    printf("\n");
    printf("Il giocatore con il punteggio più alto è %s con %d punti\n",head->username,max);
    printf("Il giocatore con il punteggio più basso è %s con %d punti\n",head->username,min);

}
