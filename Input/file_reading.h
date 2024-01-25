
#ifndef _PR1_PROGETTO_FILE_READING_H
#define _PR1_PROGETTO_FILE_READING_H

// file name:

#define CARTE "Specifiche_testi/carte.txt"
#define OSTACOLI "Specifiche_testi/ostacoli.txt"
#define PERSONAGGI "Specifiche_testi/personaggi.txt"

#include "Srutture/Strutture.h"


void characters();

void ostacoli(char[]);

CFU_Cards *card_reading();

void print_cards(CFU_Cards*);

void free_cards(CFU_Cards* head);

#endif //_PR1_PROGETTO_FILE_READING_H
