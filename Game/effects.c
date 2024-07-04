

#include "effects.h"

void effects_application(Player *current_player, Player* head, CFU_Cards* mazzo, CFU_Cards **scarti, Board *board, int effect, int card_index) {
    // Switch on the effect code
    switch (effect) {
        case NESSUNO:
            printf("Effetto NESSUNO\n");
            effect_NESSUNO();
            break;
        case SCARTAP:
            printf("Effetto SCARTAP\n");
            effect_SCARTAP(current_player, scarti, board,card_index);
            break;
        case RUBA:
            printf("Effetto RUBA\n");
            effect_RUBA(current_player, head, board);
            break;
        case SCAMBIADS:
            printf("Effetto SCAMBIADS\n");
            effect_SCAMBIADS(current_player,head,board,card_index);
            break;
        case SCARTAE:
            printf("Effetto SCARTAE\n");
            effect_SCARTAE(current_player, head, mazzo, scarti, board,card_index);
            break;
        case SCARTAC:
            printf("Effetto SCARTAC\n");
            effect_SCARTAC(current_player, scarti);
            break;
        case SCAMBIAP:
            printf("Effetto SCAMBIAP\n");
            effect_SCAMBIAP(board);
            break;
        case DOPPIOE:
            printf("Effetto DOPPIOE\n");
            effect_DOPPIOE(board);
            break;
        case SBIRCIA:
            printf("Effetto SBIRCIA\n");
            effect_SBIRCIA(current_player, mazzo, scarti);
            break;
        case SCAMBIAC:
            printf("Effetto SCAMBIAC\n");
            effect_SCAMBIAC(current_player, head, board);
            break;
        case ANNULLA:
            printf("Effetto ANNULLA\n");
            effect_ANNULLA(board);
            break;
        default:
            printf("Errore nell'applicazione dell'effetto, codice effetto non consentito\n");
            exit(333);
    }

    printf("Effetto applicato\n");
}

void instant_effects(Player *current_player, Player* head, DMG_cards **dmg, Board *board, int effect) {
    switch (effect) {
        case AUMENTA:
            printf("Effetto AUMENTA\n");
            effect_AUMENTA(current_player, head, board);
            break;
        case DIMINUISCI:
            printf("Effetto DIMINUISCI\n");
            effect_DIMINUISCI(current_player, head, board);
            break;
        case INVERTI:
            printf("Effetto INVERTI\n");
            effect_INVERTI(board);
            break;
            case SALVA:
            printf("Effetto SALVA\n");
            effect_SALVA(current_player,head,board,*dmg);
        default:
            printf("Errore nell'applicazione dell'effetto, codice effetto non consentito\n");
            exit(333);
    }

    printf("Effetto applicato\n");
}

void effect_NESSUNO()
{
    }

//funzione che permette di scartare una carta e aggiungere il suo valore al punteggio temporaneo
void effect_SCARTAP(Player *current,CFU_Cards **scarti,Board *board,int index)
{
    CFU_Cards *mano=current->hand;
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
    for (int i = 1; i < choice; ++i) {
        mano= (CFU_Cards *) mano->next;
    }
    score=mano->cfu_points;
    board->temporay_scores[index]+=score;
    if(board->molt==true)
    {
        board->temporay_scores[index]+=score;
    }
    add_card_to_scarti(scarti,mano);


}

//guarda la mano di un altro giocatore e ruba una carta a scelta
void effect_RUBA(Player *current, Player *head, Board *board)
{
    int choice;
    CFU_Cards *carta_rubata=NULL;

    //chiedo a quale giocatore si vuole rubare la carta
    printf("Da quale giocatore vuoi rubare una carta?\n");
    peek_players(current,head);
    scanf("%d",&choice);
    while(choice<1 || choice>board->numplayers-1)
    {
        printf("Scelta non valida, riprova\n");
        scanf("%d",&choice);
    }
    //scorro la lista fino al giocatore scelto
    Player *player_to_steal=head;
    for (int i = 0; i < choice; ++i) {
        player_to_steal=player_to_steal->next;
    }
    carta_rubata=player_to_steal->hand;
    printf("Carte di %s\n",player_to_steal->username);
    print_cards(player_to_steal->hand);
    //chiedo quale carta si vuole rubare
    printf("Quale carta vuoi rubare?\n");
    int card_choice;
    scanf("%d",&card_choice);
    while (card_choice<1 || card_choice>HAND)
    {
        printf("Numero non valido\n");
        scanf("%d",&card_choice);
    }
    //scorro la lista fino alla carta scelta
    for (int i = 0; i < card_choice-1; ++i) {
        carta_rubata= (CFU_Cards *) carta_rubata->next;
    }
    printf("Hai rubato la carta %s a %s\n",carta_rubata->name,player_to_steal->username);


    //rimuovo la carta dalla mano del giocatore scelto e la aggiungo alla mano del giocatore corrente
    remove_card_from_hand(player_to_steal,carta_rubata);
    print_cards(player_to_steal->hand);
    add_card_to_hand(current,carta_rubata);


    printf("Hai rubato la carta %s a %s\n",carta_rubata->name,player_to_steal->username);

}

//scambia la carta giocata con quella di un altro giocatore a scelta purche senza effetto
void effect_SCAMBIADS(Player *current,Player *head,Board *board,int index)
{
    int choice;
    int scelta_effetto=0;

    CFU_Cards *carta_scambio;
    Player *player_to_steal = head;


    do {
        scelta_effetto = 0;
        printf("Scegli un giocatore con cui scambiare la carta\n");
        peek_players(current, head);
        scanf("%d", &choice);
        while (choice < 1 || choice > board->numplayers - 1) {
            printf("Scelta non valida, riprova\n");
            scanf("%d", &choice);
        }

        //scorro la lista fino al giocatore scelto
        for (int i = 0; i < choice; ++i) {
            player_to_steal = player_to_steal->next;
        }
        do {
            carta_scambio = player_to_steal->hand;
            printf("Carte di %s\n", player_to_steal->username);
            print_cards(player_to_steal->hand);

            //chiedo quale carta si vuole rubare
            printf("Quale carta vuoi scambiare?\n");
            int card_choice;
            scanf("%d", &card_choice);
            while (card_choice < 1 || card_choice > HAND) {
                printf("Numero non valido\n");
                scanf("%d", &card_choice);
            }
            //raggiungo la carta scelta
            for (int i = 0; i < card_choice - 1; ++i) {
                carta_scambio = (CFU_Cards *) carta_scambio->next;
            }
            //controllo che la carta scelta non abbia effetti
            if (carta_scambio->effect != NESSUNO) {
                printf("La carta scelta ha un effetto, non puoi scambiarla\n");
                printf("Vorresti scegliere un'altra carta?[1]\n"
                       "Oppure scegliere un altro giocatore?[2]\n"
                       "Premi 3 per uscire\n");
                scanf("%d", &scelta_effetto);
                while (scelta_effetto < 1 || scelta_effetto > 3) {
                    printf("Scelta non valida, riprova\n");
                    scanf("%d", &scelta_effetto);
                }
                if (scelta_effetto == 3) {
                    return;
                }
            }
        } while (scelta_effetto == 1);
    }while(scelta_effetto==2);


    //scambio le carte
    CFU_Cards *temp = board->ingame_cards[index];
    board->ingame_cards[index]=carta_scambio;
    remove_card_from_hand(player_to_steal,carta_scambio);
    board->temporay_scores[index]=carta_scambio->cfu_points;
    add_card_to_hand(player_to_steal,temp);

}

//Scarta una carta CFU punto con effetto e aggiungi il suo punteggio a quello del turno
void effect_SCARTAE(Player *current,Player*head,CFU_Cards* mazzo,CFU_Cards **scarti,Board *board,int index)
{

    CFU_Cards *mano=current->hand;
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
    for (int i = 1; i < choice; ++i) {
        mano= (CFU_Cards *) mano->next;
    }
    //controllo che la carta abbia un effetto
    if(mano->effect==NESSUNO)
    {
        printf("La carta scelta non ha effetti, scegli un'altra carta\n");
        printf("Scegli un altra carta[1]\n"
               "Oppure esci[2]\n");
        int scelta;
        scanf("%d",&scelta);
        while(scelta<1 || scelta>2)
        {
            printf("Scelta non valida, riprova\n");
            scanf("%d",&scelta);
        }
        if(scelta==2)
        {
            return;
        }
        effect_SCARTAE(current,head,mazzo,scarti,board,index);
    }

    score=mano->cfu_points;
    board->temporay_scores[index]+=score;
    if(board->molt==true)
    {
        board->temporay_scores[index]+=score;
    }
    add_card_to_scarti(scarti,mano);
}


//scarta da 1 a 3 carte dalla tua mano
void effect_SCARTAC(Player *current, CFU_Cards **scarti)
{
    //chiedo quante carte si vogliono scartare
    int choice = 0;
    printf("la tua mano\n");
    print_cards(current->hand);
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
        remove_card_from_hand(current,&current->hand[card_choice-1]);
    }
}

//effetto SCAMBIAP
//scambia il punteggio maggiore e minore dopo il calcolo del punteggio di base
void effect_SCAMBIAP(Board *board)
{
    int max=board->temporay_scores[0];
    int min=board->temporay_scores[0];
    int max_index=0;
    int min_index=0;

    //trovo il massimo e il minimo
    for (int i = 0; i < board->numplayers; ++i) {
        if(board->temporay_scores[i]>max)
        {
            max=board->temporay_scores[i];
            max_index=i;
        }
        if(board->temporay_scores[i]<min)
        {
            min=board->temporay_scores[i];
            min_index=i;
        }
    }

    int temp=board->temporay_scores[max_index];
    board->temporay_scores[max_index]=board->temporay_scores[min_index];
    board->temporay_scores[min_index]=temp;

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
    CFU_Cards *carta1=mazzo;
    CFU_Cards *carta2= (CFU_Cards *) mazzo->next;
    printf("Guarda le due carte in cima al mazzo\n");
    printf("Carta 1\n");
    print_card_info(carta1);
    printf("Carta 2\n");
    print_card_info((CFU_Cards *) carta2);
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
        add_card_to_hand(current, carta1);
        //scarto l'altra carta
        add_card_to_scarti(scarti,carta2);

        mazzo= (CFU_Cards *) carta2->next;
    }
    else
    {
        //aggiungo la carta 2 alla mano
        add_card_to_hand(current, (CFU_Cards *) carta2);
        //scarto l'altra carta
        add_card_to_scarti(scarti,carta1);

        mazzo= (CFU_Cards *) carta2->next;

    }
}

void effect_ANNULLA(Board *board)
{
    board->annulla=true;
}



//effetti per le carte instantanee


//Aumenta di 2 CFU il punteggio del turno di un giocatore a scelta
void effect_AUMENTA(Player *current, Player *head, Board *board)
{
    printf("Aumenta di 2 CFU il punteggio del turno di un giocatore a scelta\n");
    printf("Quale giocatore vuoi scegliere?\n"
           "Premi [0] per assegnare i CFU a te stesso\n");
    //stampa i giocatori
    peek_players(current,head);

    int choice;
    scanf("%d",&choice);
    while(choice<0 || choice>board->numplayers-1)
    {
        printf("Scelta non valida, riprova\n");
        scanf("%d",&choice);
    }
    board->temporay_scores[choice]+=2;
    if(board->molt==true)
    {
        board->temporay_scores[choice-1]+=2;
    }

    printf("I CFU sono stati aumentati\n");
}

//Diminuisci di 2 CFU il punteggio del turno di un giocatore a scelta
void effect_DIMINUISCI(Player *current, Player *head, Board *board)
{
    printf("Diminuisci di 2 CFU il punteggio del turno di un giocatore a scelta\n");
    printf("Quale giocatore vuoi scegliere?\n"
           "Premi [0] per assegnare i CFU a te stesso\n");
    //stampa i giocatori
    peek_players(current,head);

    int choice;
    scanf("%d",&choice);
    while(choice<0 || choice>board->numplayers-1)
    {
        printf("Scelta non valida, riprova\n");
        scanf("%d",&choice);
    }
    board->temporay_scores[choice]-=2;
    if(board->molt==true)
    {
        board->temporay_scores[choice-1]-=2;
    }

    printf("I CFU sono stati diminuiti\n");
}

//inverti il punteggio minimo e massimo del turno
void effect_INVERTI(Board *board)
{
    int max=board->temporay_scores[0];
    int min=board->temporay_scores[0];
    int max_index=0;
    int min_index=0;

    //trovo il massimo e il minimo
    for (int i = 0; i < board->numplayers; ++i) {
        if(board->temporay_scores[i]>max)
        {
            max=board->temporay_scores[i];
            max_index=i;
        }
        if(board->temporay_scores[i]<min)
        {
            min=board->temporay_scores[i];
            min_index=i;
        }
    }

    int temp=board->temporay_scores[max_index];
    board->temporay_scores[max_index]=board->temporay_scores[min_index];
    board->temporay_scores[min_index]=temp;

    printf("I punteggi sono stati scambiati\n");;

}

//mette la carta draftedDmg in fondo al mazzo, solo se il player è quello con il punteggio più basso
void effect_SALVA()
{
    printf("Hai giocato la carta SALVA, non prenderai la carta ostacolo questo turno\n");
}

//dai la carta che stai per prendere a un altro giocatore a tua scelta
void effect_DIROTTA(Player *current, Player *head, Board *board) {

    int scelta;
    printf("Scegli un giocatore a cui dare la carta\n");
    peek_players(current,head);
    scanf("%d",&scelta);
    while (scelta < 1 || scelta > board->numplayers - 1) {
        printf("Scelta non valida, riprova\n");
        scanf("%d", &scelta);
    }
    Player *player=head;
    for (int i = 0; i < scelta; ++i) {
        player=player->next;
    }
    printf("Si applica l'effetto della carta a %s\n",player->username);
    printf("\n");
    printf("```````````````````````````````\n");
    printf("Il giocatore %s ha preso la carta danno\n",player->username);
    printf("```````````````````````````````\n");
    printf("\n");
    add_dmg(player,board->draftedDMG);

}

//Scambia la carta punto giocata nel turno da un giocatore G1 con quella di un giocatore G2, con G1 e G2
//scelti dal giocatore che ha giocato la carta SCAMBIAC
void effect_SCAMBIAC(Player *current, Player *head, Board *board)
{
    int choiceG1;
    int choiceG2;

    printf("Scegli 2 giocatori, scambieranno carta giocata per questo turno\n");
    printf("Scegli il giocatore G1\n");
    peek_all_players(head);
    scanf("%d",&choiceG1);
    while(choiceG1<1 || choiceG1>board->numplayers)
    {
        printf("Scelta non valida, riprova\n");
        scanf("%d",&choiceG1);
    }
    printf("Scegli il giocatore G2\n");
    peek_all_players(head);
    scanf("%d",&choiceG2);
    while(choiceG2<1 || choiceG2>board->numplayers|| choiceG2==choiceG1)
    {
        printf("Scelta non valida, riprova\n");
        scanf("%d",&choiceG2);
    }

    //scambio le carte
    CFU_Cards *temp = board->ingame_cards[choiceG1-1];
    board->ingame_cards[choiceG1-1]=board->ingame_cards[choiceG2-1];
    board->ingame_cards[choiceG2-1]=temp;

}

