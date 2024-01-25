#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_reading.h"



CFU_Cards* card_reading()
{
    FILE *file = fopen("C:\\Users\\lemai\\Desktop\\Pr1_progetto\\HappyLittleStudents\\Specifiche_testi\\carte.txt", "r");
    if (file == NULL) {
        printf("Could not open file\n");
        exit(1);
    }

    CFU_Cards *head = NULL;
    CFU_Cards *temp = NULL;

    while (!feof(file)) {
        CFU_Cards *new_card = malloc(sizeof(CFU_Cards));
        if (new_card == NULL) {
            printf("Memory allocation failed\n");
            exit(2);
        }

        fscanf(file, "%d %d %d %[^\n]",&(new_card->num), &(new_card->cfu_points),
               &(new_card->effect), &(new_card->name));
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
    return head;
}

void print_cards(CFU_Cards* head) {
    CFU_Cards* temp = head;
    while (temp != NULL) {
        printf("Name: %s, Points: %d, Effect: %d\n", temp->name, temp->cfu_points, temp->effect);
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
