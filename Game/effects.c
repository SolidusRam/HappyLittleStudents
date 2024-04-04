

#include "effects.h"

void effect_NESSUNO(Board *board, int index)
{
    board->temporay_scores+= board->ingame_cards[index]->cfu_points;
}

//funzione che permette di scartare una carta e aggiungere il suo valore al punteggio temporaneo
void effect_SCARTAP(Player *current,CFU_Cards **scarti,Board *board,int index)
{
    int score=0;
    printf("Scarta una carta\n");
    print_cards(current->hand);
    int choice;
    scanf("%d",&choice);
    while(choice<1 || choice>HAND)
    {
        printf("Scelta non valida, riprova\n");
        scanf("%d",&choice);
    }
    score=current->hand[choice-1].cfu_points;
    board->temporay_scores[index]+=score;
    add_card_to_scarti(scarti,&current->hand[choice-1]);
    remove_card_from_hand(current,choice-1);
    if(board->molt==true)
    {
        printf("Effetto DOPPIOE attivo, il punteggio viene raddoppiato\n");
        board->temporay_scores[index]+=score;
    }
}

//guarda la mano di un altro giocatore e ruba una carta a scelta
void effect_RUBA(Player *current, Player *head, Board *board)
{
    int choice;
    printf("Da quale giocatore vuoi rubare una carta?\n");
    peek_players(current,head);
    scanf("%d",&choice);
    while(choice<1 || choice>board->numplayers-1)
    {
        printf("Scelta non valida, riprova\n");
        scanf("%d",&choice);
    }
    Player *player_to_steal=head;
    for (int i = 0; i < choice-1; ++i) {
        player_to_steal=player_to_steal->next;
    }
    printf("Carte di %s\n",player_to_steal->username);
    print_cards(player_to_steal->hand);
    printf("Quale carta vuoi rubare?\n");
    int card_choice;
    scanf("%d",&card_choice);
    while (card_choice<1 || card_choice>HAND)
    {
        printf("Numero non valido\n");
        scanf("%d",&card_choice);
    }

    for (int i = 0; i < card_choice-1; ++i) {
        player_to_steal->hand= (CFU_Cards *) player_to_steal->hand->next;
    }
    add_card_to_hand(current,player_to_steal->hand);
    remove_card_from_hand(player_to_steal,card_choice-1);
}

//scambia la carta giocata con quella di un altro giocatore a scelta
//la carta da scambiare e fra quelle in gioco
void effect_SCAMBIADS(Board *board,int index)
{
    int choice;
    printf("Con quale carta vuoi scambiare la tua?"
           "(Devi scegliere una carta senza effetto\n");
    for (int i = 0; i < board->numplayers; ++i) {
        print_card_info(board->ingame_cards[i]);
    }
    scanf("%d",&choice);
    while (choice<1 || choice>board->numplayers-1)
    {
        if(choice==index)
        {
            printf("Non puoi scambiare con te stesso\n");
        }
        printf("Scelta non valida, riprova\n");
        scanf("%d",&choice);
    }
    //scambio
    swap(board->ingame_cards[index],board->ingame_cards[choice-1]);
}

//Scarta una carta CFU punto con effetto e aggiungi il suo punteggio a quello del turno
void effect_SCARTAE(Player *current,Player*head,CFU_Cards* mazzo,CFU_Cards **scarti,Board *board,int index)
{
    int score=0;
    printf("Scarta una carta\n");
    print_cards(current->hand);
    CFU_Cards *mano=current->hand;
    int choice;
    scanf("%d",&choice);
    //scorro la lista mano per vedere se il giocatore può scartare la carta
    //quindi controllo se ha in mano almeno una carta con effetto
    int count=0;
    for (int i = 0; i < HAND-1; ++i) {
        if(mano->effect!=NESSUNO)
        {
           count++;
        }
        mano= (CFU_Cards *) mano->next;
    }

    if(count==0)
    {
        printf("Non hai in mano carte con effetto, l'effetto non viene attivato\n");
        return;
    }
    while(choice<1 || choice>HAND)
    {
        printf("Numero non valido, riprova\n");
        scanf("%d",&choice);
    }
    //controllo che la carta scelta abbia un effetto
    //scorro la lista mano fino alla carta scelta
    mano=current->hand;
    for (int i = 0; i < HAND-1; ++i) {
        if(mano->effect==NESSUNO)
        {
            printf("Devi scartare una carta con effetto\n");
            scanf("%d",&choice);
            mano=current->hand;
        }
        mano= (CFU_Cards *) mano->next;
    }

    score=current->hand[choice-1].cfu_points;
    board->temporay_scores[index]+=score;
    add_card_to_scarti(scarti,&current->hand[choice-1]);
    remove_card_from_hand(current,choice-1);

    if(board->molt==true)
    {
        board->temporay_scores[index]+=score;
    }
}


//scarta da 1 a 3 carte dalla tua mano
void effect_SCARTAC(Player *current, CFU_Cards **scarti)
{
    //chiedo quante carte si vogliono scartare
    int choice = 0;
    printf("Quante carte vuoi scartare?\n");
    scanf("%d",&choice);
    while (choice<1 || choice>3)
    {
        printf("Numero non valido, riprova\n");
        scanf("%d",&choice);
    }
    for (int i = 0; i < choice; ++i) {
        printf("Scelta %d\n",i+1);
        print_cards(current->hand);
        int card_choice;
        scanf("%d",&card_choice);
        while (card_choice<1 || card_choice>HAND)
        {
            printf("Numero non valido, riprova\n");
            scanf("%d",&card_choice);
        }
        add_card_to_scarti(scarti,&current->hand[card_choice-1]);
        remove_card_from_hand(current,card_choice-1);
    }
}

//effetto SCAMBIAP
//scambia il punteggio maggiore e minore dopo il calcolo del punteggio di base
void effect_SCAMBIAP(Board *board)
{
    int max=0;
    int min=0;
    int max_index=0;
    int min_index=0;
    for (int i = 0; i < board->numplayers; ++i) {
        if(board->base_scores[i]>max)
        {
            max=board->base_scores[i];
            max_index=i;
        }
        if(board->base_scores[i]<min)
        {
            min=board->base_scores[i];
            min_index=i;
        }
    }
    int temp=board->base_scores[max_index];
    board->base_scores[max_index]=board->base_scores[min_index];
    board->base_scores[min_index]=temp;

    printf("I punteggi sono stati scambiati\n");
}

//effetto DOPPIOE
//raddoppia gli effetti delle carte che aumentano o diminuiscono il punteggio (per tutti)

void effect_DOPPIOE(Board *board)
{
    board->molt=true;
}

//effetto SBIRCIA
//guarda due carte in cima al mazzo e scegli una da aggiungere alla tua mano e scarta l'altra

void effect_SBIRCIA(Player *current, CFU_Cards *mazzo, CFU_Cards **scarti)
{
    CFU_Cards *temp=mazzo;
    printf("Guarda le due carte in cima al mazzo\n");
    printf("Carta 1\n");
    print_card_info(temp);
    printf("Carta 2\n");
    print_card_info((CFU_Cards *) temp->next);
    printf("Quale carta vuoi prendere?\n");
    int choice;
    scanf("%d",&choice);
    while(choice<1 || choice>2)
    {
        printf("Scelta non valida, riprova\n");
        scanf("%d",&choice);
    }
    if(choice==1)
    {
        //aggiungo la carta 1 alla mano
        add_card_to_hand(current,temp);
        mazzo=temp->next;
        //scarto l'altra carta
        add_card_to_scarti(scarti,temp->next);
        //rimuovo la carta 2 dal mazzo facedo si che la carta 3 diventi la prima
        CFU_Cards *temp2= (CFU_Cards *) temp->next;
        mazzo= (CFU_Cards *) temp2->next;
    }
    else
    {
        //aggiungo la carta 2 alla mano
        add_card_to_hand(current, (CFU_Cards *) temp->next);
        mazzo=temp;
        //scarto l'altra carta
        add_card_to_scarti(scarti,temp);
        //rimuovo la carta 1 dal mazzo facedo si che la carta 3 diventi la prima
        CFU_Cards *temp2= (CFU_Cards *) temp->next;
        mazzo= (CFU_Cards *) temp2->next;

    }
}

void effect_ANNULLA(Board *board)
{
    for (int i = 0; i < board->numplayers; ++i) {
        if(board->ingame_cards[i]->effect>=AUMENTA)
        {
            printf("Effetti annullati questo turno\n");
            board->ingame_cards[i]->effect=NESSUNO;
        }
    }
    board->annulla=true;
}
/*
 * typedef enum effects{NESSUNO,SCARTAP,RUBA,SCAMBIADS,SCARTAE,SCARTAC,
                     SCAMBIAP,DOPPIOE,SBIRCIA,SCAMBIAC,ANNULLA,AUMENTA,DIMINUISCI,
                     INVERTI,SALVA,DIROTTA};
*/