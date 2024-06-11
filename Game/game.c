#include "game.h"
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

    //creo il primo player
    *head_player = create_player();
    Player *current = *head_player;
    current->character=character[0];
    //player_username(current->username);
    fillCFUCards(current,cfuCards);

    //forzatura sull'effetto
    current->hand->effect=SBIRCIA;

    for (int i = 1; i < num_players; i++) {
        current->next = create_player();
        current=current->next;
        current->character=character[i];
        fillCFUCards(current,cfuCards);
    }
    current->next=NULL;
    /*
     *
       for (int i = 0; i < num_players-1; ++i) {
       current->next = create_player();
       current=current->next;
       current->character=character[i];
       player_username(current->username);
       fillCFUCards(current,cfuCards);
       }
       current->next=NULL;
     *
     * */

}


int turn(CFU_Cards **cfuCards,DMG_cards *dmgCards,Player *head_player,int turn_number,int numplayers,CFU_Cards **scarti)
{
    //inizializzo la board i player vengono aggiornati per eliminazione
    Board board={0};
    initializeBoard(&board,numplayers);
    Player *temp_player=head_player;


    for (int i = 0; i < numplayers; ++i) {
        board.temporay_scores[i]=0;
    }

//    printf("Stampa delle carte scartate\n");
//    print_cards(*scarti);


    //salvataggio stato in file.save
    //stampa del numero turno
    printf("Inizia il turno numero %d\n",turn_number);
    printf("---------------------------\n");
    printf("---------------------------\n");




    //estrazione carta danno
    DMG_cards *draftedDMG=draw_DMG(dmgCards);

    //aggiungo la carta danno alla board
    board.draftedDMG=draftedDMG;

    //azioni giocatore fase di gioco CFU

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

    //stampa dei player e carte
    temp_player=head_player;
    while (temp_player!=NULL)
    {
        print_player(temp_player);
        temp_player=temp_player->next;
    }


    //Warning
    //le carte scarti perdono il nome
    printf("Stampa delle carte scartate\n");
    print_cards(*scarti);

    //calcolo punteggio in questa fase il punteggio e calcolato con il punteggio
    //carte

    printf("\n");


    // in questa fase i giocatori con carte con effetti hanno la possibilità
    // di giocare l'effetto

    //effetti giocatore
    temp_player=head_player;
    //effects(temp_player,&cfuCards,&scarti,&board,numplayers);


    //stampa del punteggio temporaneo
    print_board(head_player,&board);

    //fase di attivazione delle carte istantanee
    //player_has_instant(head_player,&scarti,&board);


    //controllo se c'è un pareggio in caso positivo si ripete il turno con i player che avevano pareggiato


    //stabilisco il vincitore del turno e il perdente
    bool tie_points=false;

    tie_points = conteggi(&board,&head_player,dmgCards);


    //controllo se c'è un pareggio fra i perdenti
//    if(tie_points==true)
//    {
//        //si avvia il turno di spareggio
//        Player *tie_players=head_player;
//        temp_player=head_player;
//        while (temp_player!=NULL)
//        {
//            if(temp_player->cfu_score==tie_points)
//            {
//                printf("Turno di spareggio per il giocatore %s\n",temp_player->username);
//                //salvo il giocatore in una lista di giocatori in pareggio
//                tie_players=temp_player;
//                tie_players->next=NULL;
//                tie_players=tie_players->next;
//            }
//            temp_player=temp_player->next;
//        }
//
//        tie_turn(cfuCards, dmgCards, tie_players, *scarti);
//    }


    printf("Stampa dopo il conteggio\n");
    print_board(head_player,&board);




    //controllo se un player deve essere eliminato oppure ha vinto
    win_check(head_player, numplayers, dmgCards);

    /*
    if(temp_player==NULL)
    {
        printf("Nessuno gioca Errore");
        return 1;
    }
    */


    //pesca carte in difetto dal turno precendente per tutti i giocatori
    // (occhio alle stampe di debung)

    temp_player=head_player;
    while (temp_player!=NULL)
    {
        draw(temp_player,cfuCards);
        temp_player=temp_player->next;
    }



    temp_player=head_player;
    while (temp_player!=NULL)
    {
        print_player(temp_player);
        temp_player=temp_player->next;
    }

    //codice di uscita !=0
//    free(board.ingame_cards);
//    free(board.temporay_scores);
//    free(board.flags);
    return 1;
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
    clear();
    strcpy(current->username,username);

    fillCFUCards(current,cfuCards);

    for (int i = 0; i < num_players-1; ++i) {
        current->next = create_player();
        current=current->next;
        current->character=character[i+1];
        player_username(current->username);
        clear();
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

/**
 * La funzione trova il giocatore con il punteggio più alto e più basso e assegna la carta danno al giocatore con il punteggio più basso.
 * In caso di pareggio per il punteggio più basso nessun giocatore prende la carta danno e si ripete il turno fra i giocatori in pareggio.
 * In caso di pareggio per il punteggio più alto entrambi vincono il turno.
 *
 */

bool conteggi(Board*board,Player**head,DMG_cards *dmgCards)
{

    /* controllo se la carta salva è stata giocata
    if (board->salva) {
        printf("La carta SALVA è stata giocata, nessun giocatore prende la carta danno\n");
        return 0;
    }
    */

    int max=board->temporay_scores[0];
    int min=board->temporay_scores[0];
    int mincount=1;
    int index_max=0;
    int index_min=0;
    int tiemin=0;
    int check=0;
    Player *current=*head;

    //ciclo per trovare il punteggio massimo e minimo controllo anche in caso di pareggio
    for (int i = 0; i < board->numplayers; ++i) {
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
    for (int i = 0; i < board->numplayers-1; ++i) {
        if(board->temporay_scores[i]==max)
        {
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
        printf("Il giocatore %s ha preso la carta danno\n",current->username);
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

void win_check(Player*head_player,int numplayers,DMG_cards *dmgMazzo)
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
            game_over();
        }
        current=current->next;
    }

    printf("fine controllo vincitore\n");

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
            printf("Il giocatore %s è stato eliminato", current->username);
            //elimino il giocatore
            Player *temp = current;
            current = current->next;
            free(temp);
            //rimetto le carte ostacolo in fondo al mazzo
            DMG_cards *tmpMazzo = dmgMazzo;
            while (tmpMazzo->next != NULL) {
                tmpMazzo = tmpMazzo->next;
            }
            tmpMazzo->next = current->dmg;
        }
        current = current->next;
    }

    //controllo se un player è rimasto solo
    current=head_player;
    if(current->next==NULL)
    {
        printf("Il giocatore %s ha vinto la partita rimanendo l'unico in gioco",current->username);
        game_over();
    }
}


/** La funzione controlla se il giocatore ha la combinazione
 * di carte ostacolo che lo fa eliminare dal gioco
 * */

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
        playCFU(temp_player, (CFU_Cards ***) scarti, &board, i);
        //}
        temp_player=temp_player->next;
    }

    conteggi(&board,&head_player,dmgCards);

}