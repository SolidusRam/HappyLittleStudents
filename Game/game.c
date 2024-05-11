#include "game.h"

void game()
{
    Character characters[4];
    int num_players=0;

    //inzializzo le varibili
    //definire meglio il numero delle carte per allocare bene la memoria

    CFU_Cards *cfuCards;//= malloc(sizeof(CFU_Cards)*TOTALCFU);
    CFU_Cards *scarti;//= malloc(sizeof(CFU_Cards)*TOTALCFU);

    DMG_cards *dmgCards;//= malloc(sizeof(DMG_cards)*TOTALDMG);

    Player *players;

    Board board;

    //chiedo se si vuole leggere e caricare il file di salvataggio
    game_start();
    //1 carica il file di salvataggio. 2 inizia la partita con un nuovo gioco
    //todel
    //int load=choose2();
    int load=1;

    if (load==1)
    {
        lettura_salvataggio(&num_players,&players,&cfuCards,&dmgCards,&scarti);

    }
    if(load==2)
    {
        //chiedo il numero di giocatori della partita
        num_players=players_number();

        //se il gioco non è stato caricato dal salvataggio preparo il setup
        setup_game(&cfuCards,&dmgCards,&players,characters,num_players);

        //pesco le carte dal mazzo direttamente nel setup
    }

    Player *temp=players;
    for (int i = 0; i < num_players; ++i) {
        print_player(temp);
        temp=temp->next;
    }


    printf("inizio della partita\n");
    int turn_number=0;

    while (1){
        turn(&cfuCards,dmgCards,players,turn_number,num_players ,&scarti);
        turn_number++;
    }
    /*
    int check=0;
    //turno da reiterare per variabile di ritorno
    for(int turn_number=0;check==0;turn_number++)
    {
        check=turn(&cfuCards,dmgCards,players,turn_number,numplyers );
    }
    */


    //memory free
    free_cards(scarti);
    free_cards(cfuCards);
    free_players(players);
    //questo non funziona
    //free_dmg_cards(dmgCards);
    game_over();
}


int turn(CFU_Cards **cfuCards,DMG_cards *dmgCards,Player *head_player,int turn_number,int numplayers,CFU_Cards **scarti)
{
    //inizializzo la board i player vengono aggiornati per eliminazione
    Board board;
    initializeBoard(&board,numplayers);


    for (int i = 0; i < numplayers; ++i) {
        board.temporay_scores[i]=0;
    }

    //salvataggio stato in file.save
    //stampa del numero turno
    printf("Inizia il turno numero %d\n",turn_number);



    //estrazione carta danno
    if(dmgCards!=NULL){
        draw_DMG(dmgCards);
        //to debug
        board.draftedDMG=dmgCards;
    } else{
        printf("Errore la carta DMG non esiste bisogna rimescolare");
        //funzione di rimescolamento
    }

    //azioni giocatore fase di gioco CFU
    Player *temp_player=head_player;

    for (int i = 0; i < numplayers; ++i) {
        //mostra le informazioni sul giocatore attuale
        printf("Turno del Giocatore: %s \n",temp_player->username);
        printf("Il tuo personaggio: %s \n",temp_player->character.name);
        //selettore dell'azione contestuale
        //int action=ask_for_action();
        //controllo lazione ed eseguo le prime 2
        //check_action(action,temp_player,head_player);
        //if(action==1)
        //{
        //gioco la carta CFU
        playCFU(temp_player,&scarti,&board,i);
        //}
        temp_player=temp_player->next;
    }

    printf("Stampa delle carte scartate\n");
    print_cards(&scarti);

    //calcolo punteggio in questa fase il punteggio e calcolato con il punteggio
    //carte

    printf("\n");


    // in questa fase i giocatori con carte con effetti hanno la possibilità
    // di giocare l'effetto

    //effetti giocatore
    temp_player=head_player;
    effects(temp_player,&cfuCards,&scarti,&board,numplayers);


    //stampa del punteggio temporaneo
    print_board(head_player,&board);

    //fase di attivazione delle carte istantanee
    player_has_instant(head_player,&scarti,&board);


    //controllo se c'è un pareggio in caso positivo si ripete il turno con i player che avevano pareggiato


    //stabilisco il vincitore del turno e il perdente
    int tie=conteggi(&board,&head_player,dmgCards);

    //controllo se c'è un pareggio fra i perdenti
    if(tie>=1)
    {
        //si avvia il turno di spareggio
        Player *tie_players=head_player;
        temp_player=head_player;
        while (temp_player!=NULL)
        {
            if(temp_player->cfu_score==tie)
            {
                printf("Turno di spareggio per il giocatore %s\n",temp_player->username);
                //salvo il giocatore in una lista di giocatori in pareggio
                tie_players=temp_player;
                tie_players->next=NULL;
            }
            temp_player=temp_player->next;
        }

        tie_turn(cfuCards, dmgCards, tie_players, scarti);
    }

    //controllo se un player deve essere eliminato oppure ha vinto
    win_check(head_player,numplayers);

    /*
    if(temp_player==NULL)
    {
        printf("Nessuno gioca Errore");
        return 1;
    }
    */



    //pesca carte in difetto dal turno precendente per tutti i giocatori
    // (occhio alle stampe di debung)
    draw(head_player,cfuCards);



    //codice di uscita !=0
    free(board.ingame_cards);
    free(board.temporay_scores);
    free(board.flags);
    return 1;
}


void setup_game(CFU_Cards **cfuCards,DMG_cards **dmgCards,Player **head_player,Character character[],int num_players)
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
    Player *current = *head_player;
    player_username(current->username);
    fillCFUCards(current,cfuCards);

    for (int i = 0; i < num_players-1; ++i) {
        current->next = create_player();
        current=current->next;
        current->character=character[i];
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
    return 0;
}

int conteggi(Board*board,Player**head,DMG_cards *dmgCards)
{
    //trovo il giocatore con il punteggio più alto e piu basso
    int max=board->temporay_scores[0];
    int min=board->temporay_scores[0];
    int index_max=0;
    int index_min=0;
    //trasformo la lista in array
    Player *current=head;
    Player *players[board->numplayers];

    for (int i = 0; i < board->numplayers; ++i) {
        players[i]=current;
        current=current->next;
    }


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
        current=current->next;
    }

    //in caso di pareggio per il punteggio più alto assengo il punteggio a tutti i giocatori pareggianti
    for (int i = 0; i < board->numplayers; ++i) {
        if(board->temporay_scores[i]==max)
        {
            players[i]->cfu_score=board->temporay_scores[i];
        }
    }

    //controllo un pareggio per il punteggio più basso
    if (check_tie(head, min)) {
        // Se c'è un pareggio per il punteggio più basso, nessun giocatore prende la carta danno
        //si ripete il turno
        return min;
    }

    if(board->salva!=true)
    {
        //al giocatore con il punteggio più basso assegno la carta danno
        add_dmg(players[index_min],dmgCards);
    } else{
        //se il giocatore ha giocato la carta salva non prende la carta danno
        //aggiungo la carta danno alla fine della lista DMGcards
        DMG_cards *temp=dmgCards;
        while (temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=board->draftedDMG;
    }

    return 0;
}

void win_check(Player*head_player,int numplayers){
    /*
    Vince la partita il primo studente che arriva a 60 CFU o l’ultimo che non ha fatto rinuncia agli studi.
    Quando si ha almeno un vincitore della partita il gioco (ed il programma) finisce.
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
            game_over();
        }
        current=current->next;
    }

    //controllo se un player deve essere eliminato
    current=head_player;
    while (current!=NULL)
    {
        DMG_cards *temp=current->dmg;
        int count[4]={0,0,0,0};

        while (temp!=NULL)
        {
            count[temp->type]++;
            temp=temp->next;
        }
        if(dmg_count(count))
        {
            printf("Il giocatore %s è stato eliminato",current->username);
            //elimino il giocatore
            delete_player(head_player,current);
            //decremento il numero di giocatori
            numplayers--;
        }

        current=current->next;
    }

    //controllo se un player è rimasto solo
    current=head_player;
    if(current->next==NULL)
    {
        printf("Il giocatore %s ha vinto la partita rimanendo l'unico in gioco",current->username);
        game_over();
    }
}

int dmg_count( int *count)
{
    // Controlla se il giocatore ha 3 carte ostacolo dello stesso tipo
    for (int i = 0; i < 4; i++) {
        if (count[i] >= 3) {
            return 1;
        }
    }

    // Controlla se il giocatore ha una carta ostacolo di ogni tipo
    // Le carte ESAME sono jolly e contano come tutti i tipi di ostacolo
    if ((count[STUDIO] > 0 || count[ESAME] > 0) &&
        (count[SOPRAVVIVENZA] > 0 || count[ESAME] > 0) &&
        (count[SOCIALE] > 0 || count[ESAME] > 0)) {
        return 1;
    }

    // Se nessuna delle condizioni è soddisfatta, il giocatore non è "morto"
    return 0;
}

int check_tie(Player *head, int val) {
    Player *current = head;
    int tie_count = 0;

    // Compare each player's score with the known value
    while (current != NULL) {
        if (current->cfu_score == val) {
            tie_count++;
        }
        current = current->next;
    }

    // If more than one player has the known score, there is a tie
    if (tie_count > 1) {
        return 1; // Return 1 if a tie is found
    }

    return 0; // Return 0 if no tie is found
}


/*
- si possono utilizzare solo carte CFU punto
- qualsiasi effetto e/o modificatore, compresa personalità, vengono ignorati
- si continua ad oltranza finché non c’è un vincitore
- se un giocatore non ha carte CFU punto perde il turno
- se entrambi i giocatori non hanno carte CFU punto non ci sono perdenti */
void tie_turn(CFU_Cards **cfuCards, DMG_cards *dmgCards, Player *head_player, CFU_Cards *scarti) {

    Player *temp_player = head_player;
    int numplayers = count_players(temp_player);

    //inizializzo la board i player vengono aggiornati per eliminazione
    Board board;
    initializeBoard(&board,numplayers);

    temp_player=head_player;
    for (int i = 0; i < numplayers; ++i) {
        //mostra le informazioni sul giocatore attuale
        printf("Turno del Giocatore: %s \n",temp_player->username);
        //selettore dell'azione contestuale
        //int action=ask_for_action();
        //controllo lazione ed eseguo le prime 2
        //check_action(action,temp_player,head_player);
        //if(action==1)
        //{
        //gioco la carta CFU
        playCFU(temp_player,scarti,&board,i);
        //}
        temp_player=temp_player->next;
    }

    conteggi(&board,&head_player,dmgCards);

}