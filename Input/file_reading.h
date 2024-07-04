
#ifndef _PR1_PROGETTO_FILE_READING_H
#define _PR1_PROGETTO_FILE_READING_H

#define NUMCHARACTERS 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Strutture/Strutture.h"

#define CARTE "Files/carte.txt"
#define OSTACOLI "Files/ostacoli.txt"

#define PERSONAGGI "Files/personaggi.txt"

/**
 * Funzione che legge le carte ostacolo dal file
 * @return lista delle carte
 */
DMG_cards *dmg_reading();


/**
 * Funzione che legge le carte  dal file
 * @return lista delle carte
 */
CFU_Cards *card_reading();

/**
 * Funzione che legge i personaggi dal file
 * @param characters array dei personaggi
 */
void character_reading(Character *characters);

/**
 * Funzione che scrive il log della partita
 */
void write_log(const char* player_name, int turn, const char* card_played,int flag);

/**
 * Funzione che inizializza il log
 */
void init_log();

/**
 * Funzione che legge la lista dei salvataggi e permette di scegliere quale caricare
 * @return path del salvataggio scelto
 */
char *list_saves();

/**
 * Funzione che crea un nuovo salvataggio
 * @param nome path del salvataggio
 */
void newSave(char*nome);


#endif //_PR1_PROGETTO_FILE_READING_H
