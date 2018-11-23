/*
 *  ManipulateWordElements.h
 *  COMP 40 HW4 
 *  Darcy Hinck & Rebecca Redelmeier
 *
 *  Purpose: Turn 4 pixels (held in a sequence) into a word and vice versa
 */

#include <stdint.h>
#include <seq.h>

#ifndef _MANIP_WORD_ELEMS
#define _MANIP_WORD_ELEMS

typedef struct wordParts *wordP;

/* 
Purpose: Convert a sequence of CV structs in a uint64_t word
*/
uint64_t convertToWord(Seq_T cvPixels);

/* 
Purpose: Convert a uint64_t word into a sequence of 4 CV structs
*/
Seq_T convertToSequence(uint64_t);

#endif
