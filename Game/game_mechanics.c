#include "game_mechanics.h"


/**
 * Pesco le carte un difetto a fine round per ogni giocatore
 *
 * @param head lista dei giocatori
 * @param deck_head_ref mazzo delle carte
 *
 * */
void draw(Player *head, CFU_Cards **deck_head_ref)
{

    int counter=0;
    CFU_Cards *temp= head->hand;


    while (temp!=NULL)
    {
        counter++;
        temp = (CFU_Cards *) temp->next;
    }
    for (int i = counter; i < HAND; i++) {
        //pesco una carta dal mazzo
        CFU_Cards *new_card= *deck_head_ref;
        *deck_head_ref= (CFU_Cards *) (*deck_head_ref)->next;
        new_card->next=NULL;
        add_card_to_hand(head,new_card);

    }

}

DMG_cards *draw_DMG(DMG_cards *head){
    //per ora solo stampa
    if(head!=NULL) {
        printf("Name: %s\n", head->name);
        printf("Description: %s\n", head->desc);
        printf("Type: %d\n", head->type);
        printf("\n");
    }
    else
    {
        printf("Il mazzo delle carte danno e vuoto\n");
        exit(3);
    }

    return head;
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

    CFU_Cards *temp_cards=player->hand;
    Player *current=player;

    printf("Hai in mano queste carte:\n");
    print_cards(temp_cards);

    //Suggerimento sulla carta da giocare
    //suggerimento(temp_cards,*board);
    temp_cards=player->hand;

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
    board->ingame_cards[nplayer]=temp_cards;


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


    //rimuovo la carta dalla mano
    remove_card_from_hand(current,temp_cards);


    add_card_to_scarti(*scarti,temp_cards);


//
//    printf("-----------------------\n");
//    printf("-----------------------\n");
//    printf("%s \n",player->username);
//    print_cards(player->hand);
//    printf("-----------------------\n");


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
void effects(Player*head, CFU_Cards* mazzo, CFU_Cards **scarti, Board *board, int numplayer){
    int base_score[numplayer];
    int effect[numplayer];
    Player* players[numplayer];
    int i=0;
    Player *current=head;
    while(current!=NULL)
    {
        base_score[i]=board->base_scores[i];
        effect[i]=board->ingame_cards[i]->effect;
        players[i]=current;
        i++;
        current=current->next;
    }
    desc_order(numplayer, base_score, effect, players);
    for (int j = 0; j < numplayer; ++j) {

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

        printf("%s ha ottenuto %d punti questo turno \n",current->username,board->temporay_scores[i]);
        current=current->next;
    }
    printf("\n");

    printf("Punteggi totali: \n");
    current=head;
    for (int i = 0; i < board->numplayers; ++i) {
        printf("%s ha ottenuto %d punti totali\n",current->username,current->cfu_score);
        current=current->next;
    }
    printf("\n");
    current=head;
    for (int i = 0; i < board->numplayers; ++i) {
        if(i==index_max)
        {
            printf("Il giocatore con il punteggio piu' alto e' %s con %d punti\n",current->username,max);
        }
        if(i==index_min)
        {
            printf("Il giocatore con il punteggio piu' basso e' %s con %d punti\n",current->username,min);
        }
        current=current->next;
    }


}


//sposta la carta danno in fondo al mazzo
void salva_dmg(DMG_cards *dmgCards){
    DMG_cards *current=dmgCards;
    DMG_cards *prev=NULL;
    while(current->next!=NULL)
    {
        prev=current;
        current=current->next;
    }
    prev->next=NULL;
    current->next=dmgCards;
    dmgCards=current;
}


/**
 * La funzione trova il giocatore con il punteggio più alto e più basso e assegna la carta danno al giocatore con il punteggio più basso.
 * In caso di pareggio per il punteggio più basso nessun giocatore prende la carta danno e si ripete il turno fra i giocatori in pareggio.
 * In caso di pareggio per il punteggio più alto entrambi vincono il turno.
 *
 */

bool conteggi(Board*board,Player**head,DMG_cards *dmgCards)
{

    /* controllo se la carta salva è stata giocata
    if (board->salva) {printf("La carta SALVA è stata giocata, nessun giocatore prende la carta danno\n");
        return 0;
    }
    */

    int max=board->temporay_scores[0];
    int min=board->temporay_scores[0];
    int mincount=0;
    int index_max=0;
    int index_min=0;
    int tiemin=0;
    int check=0;

    Player *current=*head;

    //ciclo per trovare il punteggio massimo e minimo controllo anche in caso di pareggio
    for (int i = 0; i < board->numplayers; i++) {
        if(board->temporay_scores[i]>max)
        {
            max=board->temporay_scores[i];
            index_max=i;
        }
        if(board->temporay_scores[i]<min)
        {
            min=board->temporay_scores[i];
            mincount=1;
            index_min=i;
        }else if(board->temporay_scores[i]==min)
        {
            mincount++;
        }
        current=current->next;
    }


    //assegno i punti ai giocatori vincitori
    current=*head;
    for (int i = 0; i < board->numplayers; ++i) {
        if(board->temporay_scores[i]==max)
        {
            printf("Il giocatore %s ha vinto il turno con %d punti\n",current->username,board->temporay_scores[i]);
            current->cfu_score+=board->temporay_scores[i];
        }
        current=current->next;
    }

    //controllo se c'è un pareggio per il punteggio minore
    //aggiungo il caso in cui minore e maggiore sono uguali
    //in questo caso nessun giocatore prende la carta danno
    if(min==max)
    {
        return false;
    }

    current=*head;
    //nessun pareggio per il punteggio minore
    if(mincount==1)
    {
        //assegno la carta danno al giocatore con il punteggio minore

        for (int i = 0; i < index_min; ++i) {
            current=current->next;
        }
        printf("\n");
        printf("```````````````````````````````\n");
        printf("Il giocatore %s ha preso la carta danno\n",current->username);
        printf("```````````````````````````````\n");
        printf("\n");
        add_dmg(current,board->draftedDMG);

    }else
    {
        //pareggio per il punteggio minore
        //turno di spareggio fra i giocatori in pareggio
        //tie_turn(cfuCards, dmgCards, tie_players, scarti);
        return true;
    }

    return false;
}
