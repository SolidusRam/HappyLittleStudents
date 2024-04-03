

#include "effects.h"

void effect_NESSUNO()
{
    printf("Nessun effetto\n");
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
    board->temporay_scores[index]=score;
    add_card_to_scarti(scarti,&current->hand[choice-1]);
    remove_card_from_hand(current,choice-1);
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