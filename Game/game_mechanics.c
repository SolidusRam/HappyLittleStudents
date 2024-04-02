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


    //aggiungo la carta in gioco
    board->ingame_cards[nplayer]=temp;


    //aggiungo punteggio in base alla carta giocata
    int score=0;
    score=board->ingame_cards[nplayer]->cfu_points;

    //aggiungo bonus in base al personaggio
    int tipo=board->draftedDMG->type;
    int bonus_char = player->character.bonus[tipo];

    board->temporay_scores[nplayer]=score+bonus_char;
    board->effects_order[nplayer]=score;

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

int desc_order( int n,int a [n])
{
    int i, j, t = 0;

    // iterates the array elements
    for (i = 0; i < n; i++) {

        // iterates the array elements from index 1
        for (j = i + 1; j < n; j++) {

            // comparing the array elements, to set array
            // elements in descending order
            if (a[i] < a[j]) {
                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
    // printing the output
    for (i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}


void effects(Player*head,CFU_Cards* mazzo,CFU_Cards **scarti,Board *board,int numplayer){

    int effects[numplayer];
    int annulla=0;

    copy_array(board->effects_order,effects,numplayer,0);

    desc_order(numplayer,effects);
    //scorro le carte dal punteggio
    for (int i = 0; i < numplayer; i++) {

        CFU_Cards *tmp=board->ingame_cards;

        //scorro le carte in gioco e gioco la carta seguendo l'ordine
        for (int j = 0; j < numplayer; j++) {
            if (effects[i] == tmp->cfu_points) {
                //play effect
                Player *tmp_player=head;
                for (int k = j; k > 0; k--) {
                    tmp_player=tmp_player->next;
                }
                printf("found %s con effetto %d di punti %d giocata da %s\n",tmp->name,
                        tmp->effect,tmp->cfu_points,tmp_player->character.name);
                effects_application(tmp_player,head,mazzo,scarti,&board,tmp->effect);


                break;

            } else{
                tmp = tmp->next;
            }
        }
    }
}

void effects_application(Player *current,Player*head,CFU_Cards*mazzo,CFU_Cards **scarti,Board *board,int effect){


    switch (effect) {

        /*Scambia la carta punto giocata nel turno da un giocatore G1 con quella di un giocatore G2, con G1 e G2
        scelti dal giocatore che ha giocato la carta SCAMBIAC*/
        case SCAMBIAC:
            //scegli giocatore

            break;
        //Guarda due carte in cima al mazzo, prendine una e scarta l’altra
        case SBIRCIA:
            sbircia(mazzo,scarti,head);
            break;
//        Raddoppia gli effetti delle carte che aumentano o diminuiscono il punteggio (per tutti)
        case DOPPIOE:
            break;
//        Scambia il punteggio del turno maggiore e minore dopo il calcolo del punteggio di base
        case SCAMBIAP:
            break;
//            Scarta da uno a tre carte dalla tua mano
        case SCARTAC:

            break;
//        4 [SCARTAE] Scarta una carta CFU punto con effetto e aggiungi il suo punteggio a quello del turno
        case SCARTAE:
            break;
//        3 [SCAMBIADS] Scambia questa carta con quella di un altro giocatore, purché senza effetto
        case SCAMBIADS:
            break;
//            2 [RUBA] Guarda la mano di un collega e ruba una carta a scelta.

        case RUBA:
            break;
           // 1 [SCARTAP] Scarta una carta CFU punto e aggiungi il suo punteggio a quello del turno

        case SCARTAP:
            break;

        case NESSUNO:
            break;
        default:
            printf("Errore nell'applicazione dell'effetto,codice effetto non consentito\n");
            exit(333);
            break;
        
    }
}
