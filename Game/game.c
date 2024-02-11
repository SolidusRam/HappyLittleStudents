#include "game.h"

void game()
{
    //chiedo il numero di giocatori della partita
    //int num_players= players_number();
    int num_players=2;

    //inzializzo le varibili
    CFU_Cards *cfuCards= malloc(sizeof (CFU_Cards));
    CFU_Cards *scarti= malloc(sizeof (CFU_Cards));
    DMG_cards *dmgCards= malloc(sizeof (DMG_cards));
    Player *players= malloc(sizeof(Player));
    Character characters[num_players];

    setup_game(cfuCards,dmgCards,players,characters,num_players);

    //turno da reiterare per variabile di ritorno
    turn(cfuCards,dmgCards,players);


    game_over();
}

int turn(CFU_Cards *cfuCards,DMG_cards *dmgCards,Player *head_player)
{

    //salvataggio stato in file.save

    //pesca carte in difetto dal turno precendente
    draw(&head_player,&cfuCards);

    //estrazione carta danno
    if(dmgCards!=NULL){
        draw_DMG(dmgCards);
        dmgCards=dmgCards->next;
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
        printf("Nessuno gioca");

    //altro ciclo per la carta CFU instantaneo
    //di nuovo richiedo le altre due opzioni

    return 0;
}


void setup_game(CFU_Cards *cfuCards,DMG_cards *dmgCards,Player *head_player,Character character[],int num_players)
{
    //operazioni di lettura
    cfuCards=card_reading();
    dmgCards=dmg_reading();
    printf("lettura finita \n");
    //mix
    shuffleCFU(&cfuCards);
    shuffleDmg(&dmgCards);
    shuffle_characters(character,num_players);
    printf("shuffle finito \n");



    //lettura personaggi
    character_reading(character,num_players);

    //creazione personaggio
    head_player = create_player(&cfuCards);
    Player *current = head_player;

    for (int i = 0; i < num_players-1; ++i) {
        current->next = create_player(&cfuCards);
        current->character=character[i];
        current=current->next;
    }
    current->next=NULL;


    /*print di controllo
    print_player(head_player);
    print_cards(cfuCards);
     */

    /*memory free
    free_players(head_player);
    free_cards(cfuCards);
    free_dmg_cards(dmgCards);*/

}



Player *create_player(CFU_Cards **cards)
{
    Player *newPlayer = (Player*)malloc(sizeof(Player));
    if(newPlayer==NULL)
    {
        printf("Errore di memoria per player");
        return NULL;
    }
    //nome da ottenuto tramite input
    //player_username(newPlayer->username);

    newPlayer->hand=NULL;
    fillCFUCards(newPlayer,cards);
    newPlayer->dmg=NULL;
    newPlayer->cfu_score = 0;

    newPlayer->next=NULL;
    return newPlayer;
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

void draw(Player *head, CFU_Cards **deck_head_ref)
{
    Player *current_player =head;

    while(current_player!=NULL)
    {
        // Count the number of cards in the player's hand
        int hand_size = 0;
        CFU_Cards *current = current_player->hand;


        while (current != NULL) {
            hand_size++;
            current =  current->next;
        }

        // Draw cards from the deck until the player has 5 cards
        while (hand_size < HAND) {
            if (*deck_head_ref == NULL) {
                //aggiungere la funzione di mescolamento quando le carte sono finite
                printf("finite le carte inizio un nuovo mescolamento\n");
                return;
            }

            // Remove the card from the top of the deck
            CFU_Cards *card = *deck_head_ref;
            *deck_head_ref = card->next;

            // Add the card to the player's hand
            card->next =  current_player->hand;
            current_player->hand = card;

            hand_size++;
        }
        current_player=current_player->next;
    }
}

void draw_DMG(DMG_cards *head){
    //per ora solo stampa
    if(head!=NULL) {
        printf("Name: %s\n", head->name);
        printf("Description: %s\n", head->desc);
        printf("Type: %d\n", head->type);
        printf("\n");
    }

}

int game_over(){
    printf("\nGame over\n");
    return 0;
}