#include "file_reading.h"



CFU_Cards* card_reading()
{
    //modificare il path del file
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

        fscanf(file, "%d %d %d %[^\n]",&(new_card->num),
               &(new_card->effect),&(new_card->cfu_points), &(new_card->name));
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

/** \brief Legge il file di testo carte ostacolo.
 * Contiene un controllo sulla corretta lettura del file, restituisce null in caso
 * il file sia vuoto oppure il file non e' contenuto nel path indicato.
 * @return riferimento al primo valore dellla lista
 */
//La funzione non riesce a leggere i caratteri speciali
DMG_cards* dmg_reading() {
    FILE *file = fopen("C:\\Users\\lemai\\Desktop\\Pr1_progetto\\HappyLittleStudents\\Specifiche_testi\\ostacoli.txt", "r");
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
}

void character_reading(Character *characters, int numCharacters)
{
    FILE *file = fopen("C:\\Users\\lemai\\Desktop\\Pr1_progetto\\HappyLittleStudents\\Specifiche_testi\\personaggi.txt", "r");
    if (file == NULL) {
        printf("Cannot open file.\n");
        return;
    }

    for (int i = 0; i < numCharacters; i++) {
        fscanf(file, "%d %d %d %d %s", &characters[i].bonus[0], &characters[i].bonus[1], &characters[i].bonus[2], &characters[i].bonus[3], characters[i].name);
    }

    fclose(file);
}