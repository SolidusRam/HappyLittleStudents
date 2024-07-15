
#ifndef HAPPYLITTLESTUDENTS_SALVATAGGI_H
#define HAPPYLITTLESTUDENTS_SALVATAGGI_H

#import "Strutture/Strutture.h"
#import "Game/game.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Funzione che legge il file binario di salvataggio
 * @param head_player lista dei giocatori
 * @param scarti lista delle carte scartate
 * @param numplayers numero dei giocatori
 * @param filename path del file di salvataggio
 */
void lettura_salvataggio(Player **head_player,CFU_Cards**,DMG_cards**,CFU_Cards ** scarti,int *numplayers,char *filename);

/**
 * Funzione che scrive il file binario di salvataggio
 */
void scrittura_salvataggio(Player **head_player,CFU_Cards**mazzo,DMG_cards**danno,CFU_Cards **scarti,char *filename);


#endif //HAPPYLITTLESTUDENTS_SALVATAGGI_H
