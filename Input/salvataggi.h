
#ifndef HAPPYLITTLESTUDENTS_SALVATAGGI_H
#define HAPPYLITTLESTUDENTS_SALVATAGGI_H

#import "Strutture/Strutture.h"
#import "Game/game.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//da cambiare//
#define FILENAMEABS "C:\\Users\\lemai\\Desktop\\Pr1_progetto\\HappyLittleStudents\\Specifiche_testi\\savegame.sav"
#define FILENAME "Specifiche_testi/savegame.sav"

void lettura_salvataggio(int *numPlayers,Player **head_player,CFU_Cards**,DMG_cards**,CFU_Cards ** scarti);
void scrittura_salvataggio(Player **head_player,CFU_Cards**mazzo,DMG_cards**danno,CFU_Cards **scarti);


#endif //HAPPYLITTLESTUDENTS_SALVATAGGI_H
