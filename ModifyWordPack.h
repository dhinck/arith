/*
 * ModifyWordPack.h
 * COMP 40 HW 4
 * Rebecca Redelmeier & Darcy Hinck
 * October 21, 2017
 *
 *  Purpose: Interface to turn a pointer to a word struct into a 
 *                       uint64_t word
 */

#ifndef _MODIFY_WORD
#define _MODIFY_WORD


#include "ManipulateWordElements.h"
#include <stdint.h>

/* Purpose: Packs all elements from the struct into the word and returns it */
uint64_t packWord(wordP);

/* Purpose: Unpacks all parts of the word into a struct and returns it */
wordP unpackWord(uint64_t);

#endif