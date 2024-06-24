#include "user_input.h"


void
clear (void)
{
    while ( getchar() != '\n' );
}


int players_number()
{
    int ngiocatori=0;
    int is_valid=0;

    while(is_valid==0) {
        //stampa qui
        printf("------------------------------\n"
               "Inserisci il numero dei giocatori:\n"
               "il numero deve essere al massimo 4\n"
               "------------------------------\n");
        printf("->");

        scanf("%d", &ngiocatori);
        if (ngiocatori<=4&&ngiocatori>1) {
            printf("Il numero va bene\n");
            is_valid=1;
        } else{
            printf("il numero non va bene\n");
        }

    }
    return ngiocatori;
}

void player_username(char username[MAX_CHAR])
{
    printf("Enter your username (up to %d characters): ", MAX_CHAR - 1);

    do {
        // Input dall'utente 32 caratteri
        scanf("%32s", username);
        //pulisco il buffer

        // Valida la lunghezza dell'input
        size_t lunghezzaInput = strlen(username);
        if (lunghezzaInput > 32) {
            printf("Errore: L'input supera la lunghezza massima di 32 caratteri. Riprova.\n");
        } else {
            // Stampa la stringa inserita
            printf("Hai inserito: %s\n", username);
        }
    } while (strlen(username) > 32); // Continua finché l'input è troppo lungo

}

//scelgo un numero da 1 a 2
int choose2()
{
    int scelta=0;
    do {
        printf("Inserisci la tua scelta: ");
        scanf("%d", &scelta);
        switch (scelta) {
            case 1:
                printf("Hai scelto l'opzione 1.\n");
                return 1;
                break;
            case 2:
                printf("Hai scelto l'opzione 2.\n");
                return 2;
                break;
            default:
                printf("Scelta non valida.\n");
                break;
        }
    } while (scelta != 1 && scelta != 2);
}

//scelgo un numero da 1 a 3
int ask_for_action(){
    int num=0;
    do {
        //stampa toga
        printf("scegli un opzione con un numero da 1 a 3");
        printf("->");
        scanf("%d",&num);
        if (!(num >= 1 && num <= 3))
            printf("Scegli un opzione con un numero da 1 a 3");
    } while (!(num >= 1 && num <= 3));
    return num;
}

//scelgo un numero da 1 a 5
int ask_for_card(){
    int num=0;
    printf("Gioca una carta con un numero da 1 a 5: \n");
    while(scanf("%d", &num) != 1 || num < 1 || num > 5) {
        while(getchar() != '\n'); // clear input buffer
        printf("Invalid input. Please enter a number between 1 and 5: \n");
    }
    return num;
}