#include "game_mechanics.h"


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

    //se nel mazzo non ci sono piu' carte, le carte vengono mescolate
    if(head==NULL)
    {
        printf("Mazzo carte ostacolo vuoto, le carte vengono mescolate\n");
        head=dmg_reading();
//        shuffleDmg(&head);

    }


    //per ora solo stampa
    if(head!=NULL) {
        printf("Carta ostacolo pescata:\n");
        printf("Name: %s\n", head->name);
        printf("Description: %s\n", head->desc);
        printf("Type: %d\n", head->type);
        printf("\n");
    }
    else
    {
        printf("Il mazzo delle carte danno e vuoto\n");
        //funzione di rimescolamento
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
    int count=1;
    while(temp!=NULL)
    {
        if(current->character.name!=temp->character.name)
        {
            printf("[%d] %s ha %d punti dallo scorso turno, e questi danni\n",count,temp->username,temp->cfu_score);
            print_dmg_cards(temp->dmg);
            count++;
        }
        temp=temp->next;
    }
}

void peek_all_players(Player *head_player) {

    printf("Stampo le informazioni riguardanti i giocatori:\n");
    Player *temp=head_player;
    int count=1;
    while(temp!=NULL)
    {
        printf("[%d] %s ha %d punti dallo scorso turno, e tot danni\n",count,temp->username,temp->cfu_score);
        print_dmg_cards(temp->dmg);
        count++;
        temp=temp->next;
    }
}


void playCFU(Player *player,CFU_Cards ***scarti,Board *board,int nplayer,int turn_number){

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


    do {
        scelta=ask_for_card();
        clear();
    } while (check_card(scelta,player->hand));

     for (int i = 1; i < scelta; ++i) {
        temp_cards = (CFU_Cards *) temp_cards->next;
    }


    //aggiungo la carta in gioco
    board->ingame_cards[nplayer]=temp_cards;


    //aggiungo punteggio in base alla carta giocata
    int score=0;
    score=board->ingame_cards[nplayer]->cfu_points;

    //aggiungo bonus in base al personaggio
    int tipo=board->draftedDMG->type;
    int bonus_char = player->character.bonus[tipo];

    //board->temporay_scores[nplayer]=score+bonus_char;
    board->temporay_scores[nplayer]=score;
    board->base_scores[nplayer]=score;

    printf("\n");
    printf("%s ha giocato la carta %s e ha ottenuto %d punti\n",player->username,board->ingame_cards[nplayer]->name,board->base_scores[nplayer]);
    printf("\n");
    write_log(player->username,turn_number,board->ingame_cards[nplayer]->name,1);



    //aggiungo la carta agli scarti e la rimuovo dalla mano


    //rimuovo la carta dalla mano
    remove_card_from_hand(current,temp_cards);


    add_card_to_scarti(*scarti,temp_cards);


}

int check_card(int choice,CFU_Cards*hand){
    CFU_Cards *tmp=hand;
    int isvalid=0;

    for (int i = 1; i < choice; ++i) {
        tmp= (CFU_Cards *) tmp->next;
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

        printf("Giocatore: %s, si attiva l'effetto la carta %d\n",players[j]->character.name,effect[j]);
        printf("Nome carta %s\n",board->ingame_cards[j]->name);
        effects_application(players[j], head, mazzo, scarti, board, effect[j],j);
        if(board->annulla)
        {
            printf("L'effetto ANNULLA e' stato giocato, nessun effetto si attiva\n");
            board->annulla=false;
            break;
        }
    }
}

//controlla se il giocatore ha carte instantanee scorrendo la mano del giocatore
//in caso positivo aggiorna il flag di board
void player_has_instant(Player*head,Board*board,DMG_cards *dmgCards,CFU_Cards **scarti){

    Player *player=head;
    CFU_Cards *card=player->hand;

    //se annullla è attivo non si attivano gli effetti
    if (board->annulla) {
        return;
    }

    //controllo per ogni carta in mano se è una carta instantanea
    while(player!=NULL)
    {
        card=player->hand;
        while(card!=NULL)
        {
            if(card->effect>=AUMENTA && card->effect<=INVERTI)
            {
                printf("Il giocatore %s ha giocato una carta instantanea\n"
                       "Vuoi giocare la carta instantanea?\n"
                       "%s con effetto %d\n"
                       "Si:[1] No:[2]",player->username,card->name, card->effect);
                int choice=choose2();
                if(choice==1)
                {
                    //questa funzione deve poter essere attivata con meno parametri
                    instant_effects(player,head,&dmgCards,board,card->effect);
                    add_card_to_scarti(scarti,card);
                } else {
                    printf("La carta instantanea non e' stata giocata\n");
                }
            }
            card=(CFU_Cards *) card->next;
        }
        player=player->next;
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



bool conteggi(Board*board,Player**head,CFU_Cards **scarti)
{

    int max=board->temporay_scores[0];
    int min=board->temporay_scores[0];
    int mincount=0;
    int index_min=0;

    Player *current=*head;

    //ciclo per trovare il punteggio massimo e minimo controllo anche in caso di pareggio
    for (int i = 0; i < board->numplayers; i++) {
        if(board->temporay_scores[i]>max)
        {
            max=board->temporay_scores[i];
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
            write_log(current->username,0,NULL,4);
            if(max!=NONTIE)
            {
                current->cfu_score+=board->temporay_scores[i];
            }
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
        //controllo se il giocatore perdente ha la carta salva oppure la carta dirotta

        CFU_Cards *temp=current->hand;
        while(temp!=NULL)
        {
            if(temp->effect==SALVA)
            {
                printf("%s hai in mano la carta SALVA vuoi giocarla questo turno? SI[1]NO[2]\n",current->username);
                int n=choose2();
                if(n==1)
                {
                    effect_SALVA();
                    add_card_to_scarti(scarti,temp);
                    return false;
                }
            }
            if(temp->effect==DIROTTA)
            {
                printf("%s hai in mano la carta DIROTTA vuoi giocarla questo turno? SI[1]NO[2]\n",current->username);
                int n=choose2();
                if(n==1)
                {
                    effect_DIROTTA(current,*head,board);
                    add_card_to_scarti(scarti,temp);
                    return false;
                }
            }

            temp=(CFU_Cards *) temp->next;
        }

        printf("\n");
        printf("```````````````````````````````\n");
        printf("Il giocatore %s ha preso la carta danno\n",current->username);
        printf("```````````````````````````````\n");
        printf("\n");
        write_log(current->username,0,board->draftedDMG->name,5);
        add_dmg(current,board->draftedDMG);

    }else
    {
        //aggiungo i giocatori in pareggio in una lista all'interno della struttura board
        //il turno verrà ripetuto fra i giocatori in pareggio
        board->lowest_score=min;
        return true;
    }

    return false;
}
