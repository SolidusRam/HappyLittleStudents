
#ifndef _PR1_PROGETTO_FILE_READING_H
#define _PR1_PROGETTO_FILE_READING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Strutture/Strutture.h"
// file name:

#define CARTE "C:\\Users\\realr\\CLionProjects\\HappyLittleStudents\\Specifiche_testi\\carte.txt"
#define OSTACOLI "C:\\Users\\realr\\CLionProjects\\HappyLittleStudents\\Specifiche_testi\\ostacoli.txt"
#define PERSONAGGI "C:\\Users\\realr\\CLionProjects\\HappyLittleStudents\\Specifiche_testi\\personaggi.txt"


DMG_cards *dmg_reading();

CFU_Cards *card_reading();

void character_reading(Character *characters, int numCharacters);


#endif //_PR1_PROGETTO_FILE_READING_H
