#include "game.h"

void fill_characters(int num_players)
{
    for (int i = 0; i < num_players; ++i) {


    }

}

Player *create_player(char *username,CFU_Cards *hand,Character character)
{
    Player *newPlayer = (Player*)malloc(sizeof(Player));
    //username preso da input
    strcpy(newPlayer->username,NULL);
    newPlayer->cfu_score = 0;
    

    newPlayer->next=NULL;
    return newPlayer;
}
