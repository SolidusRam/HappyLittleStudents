#include "stampe.h"

void print_player( Player *player) {
    Player *temp = player;
    printf("Nikname: %s\n", temp->username);
    printf("CFU accumulated: %d\n", temp->cfu_score);
    printf("Personaggio: %s\n", temp->character.name);
    printf("CFU Cards:\n");
    print_cards(temp->hand);
    printf("Obstacle Cards:\n");
    print_dmg_cards(temp->dmg);
}

void game_start()
{
    printf("+----------------------------------------------------------------------------+\n");
    printf("| _   _                                    _       _   _     _     _         |\n");
    printf("| | | |   __ _   _ __    _ __    _   _    | |     (_) | |_  | |_  | |   ___  |\n");
    printf("| |_| |  / _` | | '_ \\  | '_ \\  | | | |   | |     | | | __| | __| | |  / _  \\|\n");
    printf("|  _  | | (_| | | |_) | | |_) | | |_| |   | |___  | | | |_  | |_  | | |  __/ |\n");
    printf("| |_| |_|  \\__,_| | .__/  | .__/ \\__,     | |_____| |_|  \\__|  \\__| |_|  \\__ |\n");
    printf("| ____    _     |_|     |_| _     |___/        _                             |\n");
    printf("|/ ___|  | |_   _   _    __| |   ___   _ __   | |_   ___                     |\n");
    printf("|\\___ \\  | __| | | | |  / _` |  / _ \\ | '_ \\  | __| / __|                    |\n");
    printf("| ___) | | |_  | |_| | | (_| | |  __/ | | | | | |_  \\__ \\                    |\n");
    printf("| ____/   \\__|  \\__,_|  \\__,_|  \\___| |_| |_|  \\__| |___/                    |\n");
    printf("+----------------------------------------------------------------------------+\n");
    printf("\n");
    printf("========================================================================================================================\n");
    printf("1. Carica la partita\n");
    printf("2. Inizia un nuovo salvataggio\n");


}
void papiro()
{
    /*


        ______________________________
      / \                             \.
     |   |                            |.
      \_ |                            |.
         |                            |.
         |                            |.
         |                            |.
         |                            |.
         |                            |.
         |                            |.
         |                            |.
         |                            |.
         |                            |.
         |                            |.
         |                            |.
         |    ________________________|____
         |   /                            /.
          \_/____________________________/.




    printf(""
           "        ______________________________      \n"
           "      / \\                             \\.  \n"
           "     |   |                            |.    \n"
           "      \\_ |                            |.   \n"
           "         |                            |.    \n"
           "         |                            |.    \n"
           "         |         Hello Word         |.    \n"
           "         |                            |.    \n"
           "         |    ________________________|____ \n"
           "         |   /                            /.\n"
           "          \\_/dc__________________________/.\n");
    */

    // Definisco la larghezza del bordo
    int border_width = 27;

    // Stringa di prova
    char *message = "Hello World ";

    //Calcolo gli spazi prima e dopo il messaggio
    int spaces_before = (border_width - strlen(message)) / 2;
    int spaces_after = border_width - strlen(message) - spaces_before;

    // Print the top border
    printf(""
           "        ______________________________      \n"
           "      / \\                             \\.  \n"
           "     |   |                            |.    \n"
           "      \\_ |                            |.   \n"
           "         |                            |.    \n"
           "         |                            |.    \n");

    // Stampa il messaggio
    printf("         | ");
    for (int i = 0; i < spaces_before; i++) {
        printf(" ");
    }
    printf("%s", message);
    for (int i = 0; i < spaces_after; i++) {
        printf(" ");
    }
    printf("|.\n");

    // Stampa il fondo
    printf("         \\_/____________________________/\n");


}