
#ifndef _PR1_PROGETTO_FILE_READING_H
#define _PR1_PROGETTO_FILE_READING_H

#define NUMCHARACTERS 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Strutture/Strutture.h"


// file name aggiornare la working directory:

#define CARTEABS "C:\\Users\\lemai\\Desktop\\Pr1_progetto\\HappyLittleStudents\\Files\\carte.txt"
#define CARTE "Files/carte.txt"
#define OSTACOLIABS "C:\\Users\\lemai\\Desktop\\Pr1_progetto\\HappyLittleStudents\\Files\\ostacoli.txt"
#define OSTACOLI "Files/ostacoli.txt"

#define PERSONAGGIABS "C:\\Users\\lemai\\Desktop\\Pr1_progetto\\HappyLittleStudents\\Files\\personaggi.txt"
#define PERSONAGGI "Files/personaggi.txt"


DMG_cards *dmg_reading();

CFU_Cards *card_reading();

void character_reading(Character *characters);

void write_log(const char* player_name, int turn, const char* card_played,int flag);

void init_log();

char *list_saves();

void newSave(char*nome);


#endif //_PR1_PROGETTO_FILE_READING_H
