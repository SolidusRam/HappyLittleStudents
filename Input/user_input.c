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
    //stampa qui
    int is_valid = 0;

    while (is_valid==0) {
        printf("Inserisci una nikname: ");
        scanf("%32s", username);

        if (strlen(username) <= 32) {
            printf("Username inserito\n");
            is_valid = 1;
        } else {
            printf("La stringa è troppo lunga. Per favore, reinserisci.\n");
        }
    }

}
