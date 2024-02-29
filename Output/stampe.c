#include "stampe.h"

void print_player( Player *player) {
    Player *temp = player;
    printf("Nikname: %s\n", temp->username);
    printf("CFU accumulated: %d\n", temp->cfu_score);
    printf("Personaggio: %s\n", temp->character.name);
    printf("CFU Cards:\n");
    print_cards(temp->hand);
}

void game_start()
{
    printf("+----------------------------------------------------------------------------+\n");
    printf("| _   _                                     _       _   _     _     _        |\n");
    printf("| | | |   __ _   _ __    _ __    _   _    | |     (_) | |_  | |_  | |   ___ |\n");
    printf("| |_| |  / _` | | '_ \\  | '_ \\  | | | |   | |     | | | __| | __| | |  / _ \\|\n");
    printf("|  _  | | (_| | | |_) | | |_) | | |_| |   | |___  | | | |_  | |_  | | |  __/|\n");
    printf("| |_| |_|  \\__,_| | .__/  | .__/   \\__, |   |_____| |_|  \\__|  \\__| |_|  \\___||\n");
    printf("| ____    _      |_|     |_|_     |___/        _                             |\n");
    printf("|/ ___|  | |_   _   _    __| |   ___   _ __   | |_   ___                     |\n");
    printf("|\\___ \\  | __| | | | |  / _` |  / _ \\ | '_ \\  | __| / __|                    |\n");
    printf("| ___) | | |_  | |_| | | (_| | |  __/ | | | | | |_  \\__ \\                    |\n");
    printf("|____/   \\__|  \\__,_|  \\__,_|  \\___| |_| |_|  \\__| |___/                    |\n");
    printf("+----------------------------------------------------------------------------+\n");
    printf("\n");
    printf("========================================================================================================================\n");
    printf("1. Carica la partita\n");
    printf("2. Inizia un nuovo salvataggio\n");


}