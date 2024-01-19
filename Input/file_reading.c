#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_reading.h"




/*


#define MAX_CHAR 50

enum effects { Monitor, Mouse, Tastiera, Cavo_Ethernet, Cavo_USB, Esse3, MS_Teams };

typedef struct CFU_Cards {
    char name[MAX_CHAR];
    int cfu_points;
    enum effects effect;
    struct CFU_Cards *next;
} CFU_Cards;

int main() {
    FILE *file = fopen("file.txt", "r");
    if (file == NULL) {
        printf("Non è stato possibile aprire il file.\n");
        return 1;
    }

    CFU_Cards *head = NULL;
    CFU_Cards *temp = NULL;

    while (!feof(file)) {
        CFU_Cards *new_card = malloc(sizeof(CFU_Cards));
        if (new_card == NULL) {
            printf("Memoria esaurita.\n");
            return 1;
        }

        fscanf(file, "%d %d %d %[^\n]", &(new_card->cfu_points), &(new_card->effect), &(new_card->name));
        new_card->next = NULL;

        if (head == NULL) {
            head = new_card;
        } else {
            temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_card;
        }
    }

    fclose(file);

    // Stampa i dati
    temp = head;
    while (temp != NULL) {`
        printf("Nome: %s, Punti CFU: %d, Effetto: %d\n", temp->name, temp->cfu_points, temp->effect);
        temp = temp->next;
    }

    // Libera la memoria
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
 // Estrai 4 carte casuali
    for (int i = 0; i < 4; i++) {
        int random_card_index = rand() % total_cards;
        temp = head;
        for (int j = 0; j < random_card_index; j++) {
            temp = temp->next;
        }
        printf("Carta estratta %d: %s\n", i+1, temp->name);
    }

    // ... Il tuo codice precedente ...
}
 */