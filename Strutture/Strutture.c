#include "Strutture.h"

/**
 * \brief shuffle mescola il mazzo di carte.
 *
 * Utilizza l'algoritmo Fisher-Yates
 *
 * @param head_ref riferimento al primo elemento della lista carte
 *
 */
void shuffleCFU(CFU_Cards **head_ref)
{
    srand(time(NULL));

    if (*head_ref == NULL || (*head_ref)->next == NULL) {
        return;
    }

    CFU_Cards *current = *head_ref;
    CFU_Cards *prev = NULL;
    int count = 0;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    current = *head_ref;

    for (int i = 0; i < count; i++) {
        int rand_index = rand() % count;

        CFU_Cards *swap_node = *head_ref;
        CFU_Cards *swap_prev = NULL;

        for (int j = 0; j < rand_index; j++) {
            swap_prev = swap_node;
            swap_node = swap_node->next;
        }

        if (prev != NULL) {
            prev->next = swap_node;
        } else {
            *head_ref = swap_node;
        }

        if (swap_prev != NULL) {
            swap_prev->next = current;
        } else {
            *head_ref = current;
        }

        CFU_Cards *temp = current->next;
        current->next = swap_node->next;
        swap_node->next = temp;

        prev = swap_node;
        current = swap_node->next;
    }
}

void shuffleDmg(DMG_cards **head_ref){
    srand(time(NULL));

    if (*head_ref == NULL || (*head_ref)->next == NULL) {
        return;
    }

    DMG_cards *current = *head_ref;
    DMG_cards *prev = NULL;
    int count = 0;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    current = *head_ref;

    for (int i = 0; i < count; i++) {
        int rand_index = rand() % count;

        DMG_cards *swap_node = *head_ref;
        DMG_cards *swap_prev = NULL;

        for (int j = 0; j < rand_index; j++) {
            swap_prev = swap_node;
            swap_node = swap_node->next;
        }

        if (prev != NULL) {
            prev->next = swap_node;
        } else {
            *head_ref = swap_node;
        }

        if (swap_prev != NULL) {
            swap_prev->next = current;
        } else {
            *head_ref = current;
        }

        DMG_cards *temp = current->next;
        current->next = swap_node->next;
        swap_node->next = temp;

        prev = swap_node;
        current = swap_node->next;
    }
}


void shuffle_characters(Character *array,size_t n) {
    srand(time(NULL));
    if (n > 1) {
        size_t i;
        for (i = 0; i < n - 1; i++) {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            Character t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

Player *create_player()
{
    Player *newPlayer = malloc(sizeof(Player));
    if(newPlayer==NULL)
    {
        printf("Errore di memoria per player");
        return NULL;
    }

    newPlayer->hand=NULL;
    newPlayer->dmg=NULL;
    newPlayer->cfu_score = 0;

    newPlayer->next=NULL;
    return newPlayer;
}


void swap(CFU_Cards *a, CFU_Cards *b) {
    CFU_Cards temp = *a;
    *a = *b;
    *b = temp;
}

void print_cards(CFU_Cards* head) {
    CFU_Cards* temp = head;
    int count=1;
    while (temp != NULL) {
        printf("Carta num:%d Name: %s, Points: %d, Effect: %d\n",
               count,temp->name, temp->cfu_points, temp->effect);
        temp = (CFU_Cards *) temp->next;
        count++;
    }
}

void print_dmg_cards(DMG_cards* head) {
    DMG_cards* temp = head;
    while (temp != NULL) {
        printf("Name: %s\n", temp->name);
        printf("Description: %s\n", temp->desc);
        printf("Type: %d\n", temp->type);
        printf("\n");
        temp = (DMG_cards *)temp->next;
    }
}

void free_cards(CFU_Cards* head) {
    CFU_Cards* temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void free_dmg_cards(DMG_cards * head){
    DMG_cards * temp;

    while (head != NULL) {
        temp = head;

        free(temp);
        temp = head->next;
    }
}




void free_players(Player *head) {
    Player *current = head;
    while (current != NULL) {
        Player *nextPlayer = current->next;

        // Free the player's CFU cards
        free_cards(current->hand);

        // Free the player's obstacle cards
        free_dmg_cards(current->dmg);

        // Free the player
        free(current);

        current = nextPlayer;
    }
}


void initializeBoard(Board* board,int numplayers) {
    board->temporay_scores = (int*) malloc(numplayers * sizeof(int));
    board->base_scores = (int*) malloc(numplayers * sizeof(int));
    board->ingame_cards = (CFU_Cards**) malloc(numplayers * sizeof(CFU_Cards*)); // Allocate the ingame_cards array
    board->flags = (int*) malloc(numplayers * sizeof(int));
    board->numplayers= numplayers;
    board->molt=false;
    board->annulla=false;
    board->salva=false;

    for (int i = 0; i < numplayers; ++i) {
        board->temporay_scores[i] = 0;
        board->base_scores[i] = 0;
        board->ingame_cards[i] = NULL; // Initialize each pointer to NULL
        board->flags[i] = 0;
    }
}

int copy_array(int a[], int b[], int n, int i)
{
    // copying elements from one array to another
    if (i < n) {
        b[i] = a[i];
        copy_array(a, b, n, ++i);
    }
}

void add_card_to_hand(Player *player, CFU_Cards *new_card) {
    // Create a new node for the card
    CFU_Cards *new_node = malloc(sizeof(CFU_Cards));
    if (new_node == NULL) {
        printf("Error: could not allocate memory for new card\n");
        return;
    }

    // Copy the card data   
    new_node = new_card;

    // Add the new node to the beginning of the linked list
    new_node->next = (struct CFU_Cards *) player->hand;
    player->hand = new_node;
}

void add_card_to_scarti(CFU_Cards **scarti,CFU_Cards *card) {
    if (scarti == NULL || card == NULL) {
        printf("Error: Null pointer passed to add_card_to_scarti\n");
        return;
    }

    // Create a new CFU_Cards object to hold the discarded card
    CFU_Cards *discarded_card = malloc(sizeof(CFU_Cards));
    if (discarded_card == NULL) {
        printf("Error: could not allocate memory for new card\n");
        return;
    }

    // Copy the data from the original card to the new card
    *discarded_card = *card;

    // Add the new card to the discard pile
    discarded_card->next = (struct CFU_Cards *) *scarti;
    *scarti = discarded_card;

}

//rimuove la carta dalla lista mano del giocatore
void remove_card_from_hand(Player *player, CFU_Cards *card_to_remove) {
    if (player == NULL || card_to_remove == NULL) {
        printf("Error: Null pointer passed to remove_card_from_hand\n");
        return;
    }

    CFU_Cards *current_card = player->hand;
    CFU_Cards *prev_card = NULL;

    while (current_card != NULL) {
        if (current_card == card_to_remove) {
            if (prev_card == NULL) {
                player->hand = current_card->next;
            } else {
                prev_card->next = current_card->next;
            }

            free(card_to_remove);
            return;
        }

        prev_card = current_card;
        current_card = current_card->next;
    }
}
void print_card_info(CFU_Cards *card) {
    if (card == NULL) {
        printf("Error: Null pointer passed to print_card_info\n");
        return;
    }

    printf("Name: %s\n", card->name);
    printf("Points: %d\n", card->cfu_points);

    //print dell'effetto utilizzando il nome dell'effetto
    switch (card->effect) {
        case NESSUNO:
            printf("Effect: Nessuno\n");
            break;
        case SCARTAP:
            printf("Effect: Scarta una carta\n");
            break;
        case RUBA:
            printf("Effect: Ruba una carta\n");
            break;
        case SCAMBIADS:
            printf("Effect: Scambia una carta con lo scarto\n");
            break;
        case SCARTAE:
            printf("Effect: Scarta una carta e pesca dal mazzo\n");
            break;
        case SCARTAC:
            printf("Effect: Scarta una carta e pesca dal mazzo\n");
            break;
        case SCAMBIAP:
            printf("Effect: Scambia una carta con un altro giocatore\n");
            break;
        case DOPPIOE:
            printf("Effect: Doppio effetto\n");
            break;
        case SBIRCIA:
            printf("Effect: Guarda la mano di un altro giocatore\n");
            break;
        case SCAMBIAC:
            printf("Effect: Scambia una carta con un altro giocatore\n");
            break;
        case ANNULLA:
            printf("Effect: Annulla l'effetto di una carta\n");
            break;
        case AUMENTA:
            printf("Effect: Aumenta il punteggio di una carta\n");
            break;
        case DIMINUISCI:
            printf("Effect: Diminuisci il punteggio di una carta\n");
            break;
        case INVERTI:
            printf("Effect: Inverti il punteggio di una carta\n");
            break;
        case SALVA:
            printf("Effect: Salva una carta per il prossimo turno\n");
            break;
        case DIROTTA:
            printf("Effect: Dirotta una carta\n");
            break;
        default:
            printf("Effect: Unknown\n");
            break;
    }
}

void add_dmg(Player*player,DMG_cards*new_card)
{



    if (player == NULL || new_card == NULL) {
        printf("Error: Null pointer passed to add_dmg\n");
        return;
    } else{

        //creo una nuova copia della carta danno
        DMG_cards *copy_card = malloc(sizeof(DMG_cards));
        if (copy_card == NULL) {
            printf("Error: could not allocate memory for new card\n");
            return;
        }

        //copio i dati della carta
        memccpy(copy_card, new_card, sizeof(DMG_cards), sizeof(DMG_cards));

        //se il giocatore non ha carte danni
        if(player->dmg == NULL){
            player->dmg = copy_card;
            player->dmg->next = NULL;
            return;

        } else{
            // Aggiungo la carta alla fine della lista
            DMG_cards *current = player->dmg;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = copy_card;
            copy_card->next = NULL;
        }

    }


}

void delete_player(Player *head, Player *player) {
    if (head == NULL || player == NULL) {
        printf("Error: Null pointer passed to delete_player\n");
        return;
    }

    Player *current = head;
    Player *prev = NULL;

    while (current != NULL) {
        if (current == player) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }

            free_cards(current->hand);
            free_dmg_cards(current->dmg);
            free(current);
            return;
        }

        prev = current;
        current = current->next;
    }
}

void add_player(Player **head, Player *new_player) {
    if (head == NULL || new_player == NULL) {
        printf("Error: Null pointer passed to add_player\n");
        return;
    }

    new_player->next = *head;
    *head = new_player;
}

int count_players(Player *head) {
    int count = 0;
    Player *current = head;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}
