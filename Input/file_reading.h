
#ifndef _PR1_PROGETTO_FILE_READING_H
#define _PR1_PROGETTO_FILE_READING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Strutture/Strutture.h"


// file name aggiornare la working directory:

#define CARTEABS "C:\\Users\\lemai\\Desktop\\Pr1_progetto\\HappyLittleStudents\\Specifiche_testi\\carte.txt"
#define CARTE "Specifiche_testi/carte.txt"
#define OSTACOLIABS "C:\\Users\\lemai\\Desktop\\Pr1_progetto\\HappyLittleStudents\\Specifiche_testi\\ostacoli.txt"
#define OSTACOLI "Specifiche_testi/ostacoli.txt"

#define PERSONAGGIABS "C:\\Users\\lemai\\Desktop\\Pr1_progetto\\HappyLittleStudents\\Specifiche_testi\\personaggi.txt"
#define PERSONAGGI "Specifiche_testi/personaggi.txt"


DMG_cards *dmg_reading();

CFU_Cards *card_reading();

void character_reading(Character *characters, int numCharacters);


#endif //_PR1_PROGETTO_FILE_READING_H
