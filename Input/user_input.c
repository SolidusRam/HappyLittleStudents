#include "user_input.h"


int players_number()
{
    int ngiocatori;
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

    if (fgets(username, MAX_CHAR, stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(username);
        if (len > 0 && username[len-1] == '\n') {
            username[--len] = '\0';
        }
    } else {
        printf("Error reading username. Please try again.\n");
    }
}

int load_game()
{
    int scelta=0;
    do {
        printf("Inserisci la tua scelta: ");
        scanf("%d", &scelta);
        switch (scelta) {
            case 1:
                printf("Hai scelto di caricare la partita.\n");
                return 1;
                break;
            case 2:
                printf("Hai scelto di iniziare un nuovo salvataggio.\n");
                return 2;
                break;
            default:
                printf("Scelta non valida.\n");
                break;
        }
    } while (scelta != 1 && scelta != 2);
}



