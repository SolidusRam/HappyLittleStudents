#include "game.h"

void game()
{
    int load=0;

    Character characters[4];
    int num_players;

    //inzializzo le varibili
    //definire meglio il numero delle carte per allocare bene la memoria

    CFU_Cards *cfuCards;//= malloc(sizeof(CFU_Cards)*TOTALCFU);
    CFU_Cards *scarti;//= malloc(sizeof(CFU_Cards)*TOTALCFU);

    DMG_cards *dmgCards;//1= malloc(sizeof(DMG_cards)*TOTALDMG);

    Player *players;

    //chiedo se si vuole leggere e caricare il file di salvataggio
    game_start();
    //1 carica il file di salvataggio. 2 inizia la partita con un nuovo gioco
    load=load_game();
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


    /*
    int check=0;
    //turno da reiterare per variabile di ritorno
    for(int turn_number=0;check==0;turn_number++)
    {
        check=turn(&cfuCards,dmgCards,players,turn_number);
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

int turn(CFU_Cards **cfuCards,DMG_cards *dmgCards,Player *head_player,int turn_number)
{

    //salvataggio stato in file.save

    //stampa del numero turno
    printf("%d",turn_number);
    //pesca carte in difetto dal turno precendente
    draw(head_player,cfuCards);

    //estrazione carta danno
    if(dmgCards!=NULL){
        draw_DMG(dmgCards);
    } else{
        printf("Errore la carta DMG non esiste");
    }


    //azioni giocatori
    Player *temp_player=head_player;
    while (temp_player!=NULL)
    {
        //mostra le informazioni sul giocatore attuale
        printf("Giocatore: %s \n",temp_player->username);
        //selettore dell'azione contestuale
            //
            //gioca una carta CFU
            //
                //selettore carta Cfu

            //
            //Controlla lo stato dei giocatori
            //
            //Esci dal gioco
            //

        temp_player=temp_player->next;
    }
    if(temp_player==NULL)
    {
        printf("Nessuno gioca Errore");
        return 1;
    }


    //altro ciclo per la carta CFU instantaneo
    //di nuovo richiedo le altre due opzioni

    //codice di uscita !=0
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
    character_reading(character,num_players);

    shuffle_characters(character,num_players);

    //creazione personaggio
    //sto chiedendo anche l'username

    *head_player = create_player();
    Player *current = *head_player;

    for (int i = 0; i < num_players; ++i) {
        current->next = create_player();
        current->character=character[i];
        player_username(current->username);
        fillCFUCards(current,cfuCards);
        current=current->next;
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