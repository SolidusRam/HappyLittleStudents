
#ifndef HAPPYLITTLESTUDENTS_SALVATAGGI_H
#define HAPPYLITTLESTUDENTS_SALVATAGGI_H

#import "Strutture/Strutture.h"
#import "Game/game.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//da cambiare//
#define FILENAMEABS "C:\\Users\\lemai\\Desktop\\Pr1_progetto\\HappyLittleStudents\\Files\\savegame.sav"
#define FILENAME "Files/savegame.sav"
#define FILENAMESAV "Files/salvataggioProva.sav"

void lettura_salvataggio(Player **head_player,CFU_Cards**,DMG_cards**,CFU_Cards ** scarti,int *numplayers,char *filename);
void scrittura_salvataggio(Player **head_player,CFU_Cards**mazzo,DMG_cards**danno,CFU_Cards **scarti,char *filename);


#endif //HAPPYLITTLESTUDENTS_SALVATAGGI_H
