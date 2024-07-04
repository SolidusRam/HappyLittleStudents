#include "game.h"

/*
void setup_game_test(CFU_Cards **cfuCards,DMG_cards **dmgCards,Player **head_player,Character character[4],int num_players)
{
    //operazioni di lettura
    *cfuCards=card_reading();
    *dmgCards=dmg_reading();
    printf("lettura finita \n");
    //mix
    shuffleCFU(cfuCards);
    shuffleDmg(dmgCards);
    printf("shuffle finito \n");

    //lettura personaggi
    character_reading(character);

    shuffle_characters(character,num_players);

    //creazione personaggio
    //sto chiedendo anche l'username


    char *testone="testOne";
    char *testtwo="testTwo";
    char *testthree="testThree";

    //creo il primo player
    *head_player = create_player();
    Player *current = *head_player;
    current->character=character[0];
    strcpy(current->username,testone);

    //player_username(current->username);
    fillCFUCards(current,cfuCards);

    for (int i = 1; i < num_players; i++) {
        current->next = create_player();
        if(i==1)
        {
            current->next->character=character[i];
            strcpy(current->next->username,testtwo);
        }
        else
        {
            current->next->character=character[i];
            strcpy(current->next->username,testthree);
        }
        current = current->next;
        current->character = character[i];
        fillCFUCards(current, cfuCards);
    }

    current->next=NULL;

}
*/

bool turn(CFU_Cards **cfuCards,DMG_cards *dmgCards,Player *head_player,int turn_number,int numplayers,CFU_Cards **scarti,char *sav)
{
    //inizializzo la board i player vengono aggiornati per eliminazione

    scrittura_salvataggio(&head_player,cfuCards,&dmgCards,scarti,sav);
    Board board={0};
    initializeBoard(&board,numplayers);
    Player *temp_player=head_player;

    for (int i = 0; i < numplayers; ++i) {
        board.temporay_scores[i]=0;
    }



    //stampa del numero turno
    printf("Inizia il turno numero %d\n",turn_number);
    printf("---------------------------\n");
    printf("---------------------------\n");

    printf("Premi un tasto per continuare\n");
    clear();


    //estrazione carta danno
    DMG_cards draftedDMG=*draw_DMG(dmgCards);

    //aggiungo la carta danno alla board
    board.draftedDMG=&draftedDMG;
    board.draftedDMG->next=NULL;



    //azioni giocatore fase di gioco CFU
    for (int i = 0; i < numplayers; ++i) {
        //mostra le informazioni sul giocatore attuale
        printf("Turno del Giocatore: %s \n",temp_player->username);
        printf("Il tuo personaggio: %s \n",temp_player->character.name);


        printf("[1]Gioca una carta CFU\n");
        printf("[2]Mostra gli altri giocatori\n");
        printf("[3]Esci dal gioco\n");
//        selettore dell'azione contestuale
        int action=ask_for_action();

//        controllo lazione ed eseguo le prime 2
        check_action(action,temp_player,head_player);
        if(action==1)
        {
//        gioco la carta CFU
        playCFU(temp_player,&scarti,&board,i,turn_number);

        }

        temp_player=temp_player->next;
    }




    //calcolo punteggio in questa fase il punteggio e calcolato con il punteggio

//
//    //carte di prova
//    CFU_Cards cartaDebugNESSUNO={"cartaDebugNESSUNO",10,NESSUNO,NULL};
//
//    CFU_Cards cartaDebug={"cartaDebug",10,SCAMBIAC,NULL};
//
//    board.ingame_cards[0]=&cartaDebug;
//    board.ingame_cards[1]=&cartaDebugNESSUNO;
//
//    //fine carte di prova

    // in questa fase i giocatori con carte con effetti hanno la possibilità
    // di giocare l'effetto


    //effetti giocatore
    temp_player=head_player;
    effects(temp_player,*cfuCards,scarti,&board,numplayers);


    //fase di attivazione delle carte istantanee
    player_has_instant(head_player,&board,dmgCards,scarti);


    //controllo se c'è un pareggio in caso positivo si ripete il turno con i player che avevano pareggiato


    //stabilisco il vincitore del turno e il perdente
    bool tie_points=false;

    tie_points = conteggi(&board,&head_player,scarti);


    //preparo la prossima carta danno


    //spareggio
    //tiepoints vale true'
    //nessun controllo sul numero della carta giocata 5=crash
    temp_player=head_player;
    int count_tie=0;
    while (tie_points==true)
    {
        memset(board.temporay_scores,0,numplayers*sizeof(int));
        printf("Spareggio\n");
        for (int i = 0; i < numplayers; i++) {

            if(board.temporay_scores[i]==board.lowest_score)
            {
                playCFU(temp_player,&scarti,&board,i,turn_number);

            } else{
                board.temporay_scores[i]=NONTIE;
            }
            temp_player=temp_player->next;
        }
        conteggi(&board, &head_player, (CFU_Cards **) scarti);
    }


//    printf("Stampa dopo il conteggio\n");
//    print_board(head_player,&board);




    //controllo se un player deve essere eliminato oppure ha vinto per punti
    Player * player_to_delete;
    player_to_delete=win_check(head_player, numplayers, dmgCards,&board);

    if(board.win==true)return board.win;

    //eliminazione player
    delete_player(&head_player,player_to_delete,scarti,&dmgCards);


    //controllo se rimane un solo player
    if(count_players(head_player)==1)
    {
        printf("Il giocatore %s ha vinto la partita",head_player->username);
        write_log(head_player->username,turn_number,NULL,3);
        board.win=true;
        return board.win;
    }

    //pesca carte in difetto dal turno precendente per tutti i giocatori

    temp_player=head_player;
    while (temp_player!=NULL)
    {
        draw(temp_player,cfuCards);
        temp_player=temp_player->next;
    }



    free(board.ingame_cards);
    free(board.temporay_scores);
    free(board.flags);
    free(board.base_scores);
    return board.win;
}


void setup_game(CFU_Cards **cfuCards,DMG_cards **dmgCards,Player **head_player,Character* character,int num_players)
{
    //operazioni di lettura
    *cfuCards=card_reading();
    *dmgCards=dmg_reading();
    printf("lettura finita \n");
    //mix
    shuffleCFU(cfuCards);
    shuffleDmg(dmgCards);
    printf("shuffle finito \n");

    //lettura personaggi
    character_reading(character);

    shuffle_characters(character,num_players);

    //creazione personaggio
    //sto chiedendo anche l'username

    //creo il primo player
    *head_player = create_player();
    head_player[0]->character=character[0];
    Player *current = *head_player;
    char *username=malloc(sizeof(char)*MAX_CHAR);
    player_username(username);
    strcpy(current->username,username);

    fillCFUCards(current,cfuCards);

    for (int i = 0; i < num_players-1; ++i) {
        current->next = create_player();
        current=current->next;
        current->character=character[i+1];
        player_username(current->username);
        fillCFUCards(current,cfuCards);
    }
    current->next=NULL;

}


void fillCFUCards(Player *player, CFU_Cards **deck_head_ref) {
    for (int i = 0; i < HAND; i++) {
        if (*deck_head_ref == NULL) {
            printf("Not enough cards in the deck\n");
            return;
        }
        // Remove the card from the top of the deck
        CFU_Cards *card = *deck_head_ref;
        *deck_head_ref = (CFU_Cards *) card->next;

        // Add the card to the player's CFU cards
        card->next = (struct CFU_Cards *) player->hand;
        player->hand = card;
    }
}


int game_over(){
    printf("\nGame over\n");
    exit(0) ;
}

Player * win_check(Player*head_player,int numplayers,DMG_cards *dmgMazzo,Board *board)
{
    /*
    Vince la partita il primo studente che arriva a 60 CFU o l’ultimo che non ha fatto rinuncia agli studi.
    Quando si ha almeno un vincitore della partita il gioco (e il programma) finisce.
    Se più giocatori arrivano a 60 CFU nello stesso turno ci sono più vincitori.
    Per morire un giocatore deve soddisfare una delle seguenti condizioni:
    - 3 carte ostacolo dello stesso tipo
    - una carta ostacolo di ogni tipo
    Quando un giocatore muore le sue carte vanno scartate e il giocatore viene deallocato. Le carte ostacolo in suo
    possesso vengono rimesse in fondo al mazzo.*/

    //controllo se un player ha vinto
    Player *current=head_player;
    while(current!=NULL)
    {
        if(current->cfu_score>=60)
        {
            printf("Il giocatore %s ha vinto la partita",current->username);
            board->win=true;
            return NULL;
        }
        current=current->next;
    }

    printf("\n");
    printf("fine controllo vincitore\n");
    printf("\n");


    //controllo se un player deve essere eliminato
    current=head_player;
    while (current!=NULL) {
        int count[4] = {0, 0, 0, 0};
        DMG_cards *temp_dmg = current->dmg;
        //scorro le carte ostacolo per vedere la combinazione
        while (temp_dmg != NULL) {
            count[temp_dmg->type]++;
            temp_dmg = temp_dmg->next;
        }

        int check=dmg_count(count);
        //controllo se il giocatore è morto
        if (check==1) {
            printf("Il giocatore %s e' stato eliminato", current->username);
            write_log(current->username,0,NULL,2);
            //elimino il giocatore
            return current;

        }
        current = current->next;
    }

}


int dmg_count( int  *count){

    //il giocatore è morto se ha una carta di ogni tipo oppure 3 carte dello stesso tipo
    //ci sono 4 tipi di carte ostacolo, il 4 tipo vale come jolly

    int counter=0;

    //tripletta base
    if(count[0]>0&&count[1]>0&&count[2]>0)
        return 1;

    for (int i = 0; i < 4; ++i) {

        if(count[i]>0)  counter++;

        //tripletta di carte singole
        if(count[i]>=3) return 1;

        //doppio e jolly
        if(count[i]+count[3]>=3)    return 1;

    }

    //tripletta con jolly il giocatore ha almeno 2 tipi di carte e una carta jolly
    if(counter>=3)  return 1;


    // Se nessuna delle condizioni è soddisfatta, il giocatore non è eliminato
    return 0;
}
