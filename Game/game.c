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
    int load=choose2();

    if (load==1)
    {
        lettura_salvataggio(num_players,&players,&cfuCards,&dmgCards,&scarti);

    }
    if(load==2)
    {
        //chiedo il numero di giocatori della partita
        num_players=players_number();

        //se il gioco non è stato caricato dal salvataggio preparo il setup
        setup_game(&cfuCards,&dmgCards,&players,characters,num_players);

        //pesco le carte dal mazzo direttamente nel setup
    }


    print_player(players);
    //print_cards(cfuCards);
    printf("inizio della partita");
    int turn_number=0;

    turn(&cfuCards,dmgCards,players,turn_number,num_players ,scarti);
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


int turn(CFU_Cards **cfuCards,DMG_cards *dmgCards,Player *head_player,int turn_number,int numplayers,CFU_Cards *scarti)
{
    //inizializzo la board i player vengono aggiornati per eliminazione
    Board board;
    initializeBoard(&board,numplayers);


    //allocazione board
    if(board.ingame_cards==NULL||board.temporay_scores==NULL)
    {
        printf("Errore allocazione Board");
        exit(2);
    }

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
        playCFU(temp_player,&board,i);
        //}
        temp_player=temp_player->next;
    }



    //calcolo punteggio in questa fase il punteggio e calcolato con il punteggio
    //carte




    printf("\n");


    // in questa fase i giocatori con carte con effetti hanno la possibilità
    // di giocare l'effetto

    //effetti giocatore
    effects(head_player,&cfuCards,&scarti,&board,numplayers);

    // altro ciclo per la carta CFU instantaneo
    //di nuovo richiedo le altre due opzioni

    /*
    if(temp_player==NULL)
    {
        printf("Nessuno gioca Errore");
        return 1;
    }
    */



    //pesca carte in difetto dal turno precendente per tutti i giocatori
    // (occhio alle stampe di debung)
    //draw(head_player,cfuCards);



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

