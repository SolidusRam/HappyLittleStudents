#include "file_reading.h"



CFU_Cards* card_reading()
{
    //modificare il path del file
    FILE *file = fopen(CARTE, "r");
    if (file == NULL) {
        printf("Could not open file CFU\n");
        exit(1);
    }

    CFU_Cards *head = NULL;
    CFU_Cards **last_ptr = &head;

    while (1) {
        int num_cards;
        if (fscanf(file, "%d", &num_cards) != 1) {
            break;
        }

        CFU_Cards template_card;
        fscanf(file, "%d %d ", &template_card.effect, &template_card.cfu_points);
        fgets(template_card.name, MAX_CHAR, file);
        template_card.name[strcspn(template_card.name, "\n")] = 0;  // remove newline character

        for (int i = 0; i < num_cards; i++) {
            CFU_Cards *new_card = malloc(sizeof(CFU_Cards));
            *new_card = template_card;
            new_card->next = NULL;

            *last_ptr = new_card;
            last_ptr = &new_card->next;
        }
    }

    fclose(file);
    return head;
}

/** \brief Legge il file di testo carte ostacolo.
 * Contiene un controllo sulla corretta lettura del file, restituisce null in caso
 * il file sia vuoto oppure il file non e' contenuto nel path indicato.
 * @return riferimento al primo valore dellla lista
 */
//La funzione non riesce a leggere i caratteri speciali
DMG_cards* dmg_reading() {
    FILE *file = fopen(OSTACOLI, "r");
    if (file == NULL) {
        printf("Could not open file\n");
        return NULL;
    }

    DMG_cards *head = NULL;
    DMG_cards *temp = NULL;

    char name[MAX_CHAR];
    char desc[DESC_MAX_CHAR];
    int num_rows;

    enum dmg_type type = STUDIO; // Start with the first type

    while (fscanf(file, "%d\n", &num_rows) != EOF) {
        for (int i = 0; i < num_rows; i++) {
            fgets(name,MAX_CHAR,file);
            fgets(desc,DESC_MAX_CHAR,file);

            DMG_cards *new_card = malloc(sizeof(DMG_cards));
            strcpy(new_card->name, name);
            strcpy(new_card->desc, desc);
            new_card->type = type;
            new_card->next = NULL;

            if (head == NULL) {
                head = new_card;
                temp = new_card;
            } else {
                temp->next = new_card;
                temp = new_card;
            }
        }
        type++; // Move to the next type
    }

    fclose(file);

    return head;

    //nome, descrizione, tipo
}

void character_reading(Character *characters, int numCharacters)
{
    FILE *file = fopen(PERSONAGGI, "r");
    if (file == NULL) {
        printf("Cannot open file. File personaggi\n");
        return;
    }

    for (int i = 0; i < numCharacters; i++) {
        fscanf(file, "%d %d %d %d %s",
               &characters[i].bonus[0], &characters[i].bonus[1], &characters[i].bonus[2], &characters[i].bonus[3], characters[i].name);
    }

    fclose(file);
}
