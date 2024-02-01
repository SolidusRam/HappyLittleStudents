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

void print_cards(CFU_Cards* head) {
    CFU_Cards* temp = head;
    while (temp != NULL) {
        printf("Name: %s, Points: %d, Effect: %d\n",
               temp->name, temp->cfu_points, temp->effect);

        temp = temp->next;
    }
}

void print_dmg_cards(DMG_cards* head) {
    DMG_cards* temp = head;
    while (temp != NULL) {
        printf("Name: %s\n", temp->name);
        printf("Description: %s\n", temp->desc);
        printf("Type: %d\n", temp->type);
        printf("\n");
        temp = temp->next;
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
        head = head->next;
        free(temp);
    }
}



void print_player( Player *player) {
    printf("CFU accumulated: %d\n", player->cfu_score);
    printf("CFU Cards:\n");
    print_cards(player->hand);
}

void free_players(Player *head) {
    Player *current = head;
    while (current != NULL) {
        Player *nextPlayer = current->next;

        // Free the player's CFU cards
        free_cards(nextPlayer->hand);

        // Free the player's obstacle cards
        free_dmg_cards(nextPlayer->dmg);

        // Free the player
        free(current);

        current = nextPlayer;
    }
}