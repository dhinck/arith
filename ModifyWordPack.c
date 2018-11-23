/*
 * ModifyWordPack.c
 * COMP 40 HW 4
 * Rebecca Redelmeier & Darcy Hinck
 * October 21, 2017
 *
 *  Purpose: Gets and sets necessary variables in a word through calls to
 *           the bitpack interface
 */

#include "ModifyWordPack.h"
#include "bitpack.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


const uint64_t A_WIDTH = 9;
const uint64_t BCD_WIDTH = 5;
const uint64_t PBPR_WIDTH = 4;

const uint64_t A_LSB = 23;
const uint64_t B_LSB = 18;
const uint64_t C_LSB = 13;
const uint64_t D_LSB = 8;
const uint64_t PB_LSB = 4;
const uint64_t PR_LSB = 0;


struct wordParts {
        unsigned a;
        signed b;
        signed c;
        signed d;
        unsigned Pb;
        unsigned Pr;

};

/* Purpose: Packs all elements from the struct into the word and returns it */
uint64_t packWord(wordP wordPointer)
{

        uint64_t word = 0;

        struct wordParts currParts = *((struct wordParts *) wordPointer);

        word = Bitpack_newu(word, A_WIDTH, A_LSB, currParts.a);
        word = Bitpack_news(word, BCD_WIDTH, B_LSB, currParts.b);
        word = Bitpack_news(word, BCD_WIDTH, C_LSB, currParts.c);
        word = Bitpack_news(word, BCD_WIDTH, D_LSB, currParts.d);

        word = Bitpack_newu(word, PBPR_WIDTH, PB_LSB, currParts.Pb);
        word = Bitpack_newu(word, PBPR_WIDTH, PR_LSB, currParts.Pr);

        return(word);
}

/* Purpose: Unpacks all parts of the word into a struct and returns it */
wordP unpackWord(uint64_t word)
{

        struct wordParts *currWord = malloc(sizeof(struct wordParts));
        assert(currWord); 

        currWord->a = Bitpack_getu(word, A_WIDTH, A_LSB);
        currWord->b = Bitpack_gets(word, BCD_WIDTH, B_LSB);
        currWord->c = Bitpack_gets(word, BCD_WIDTH, C_LSB);
        currWord->d = Bitpack_gets(word, BCD_WIDTH, D_LSB);

        currWord->Pb = Bitpack_getu(word, PBPR_WIDTH, PB_LSB);
        currWord->Pr = Bitpack_getu(word, PBPR_WIDTH, PR_LSB);

        wordP finalWord = currWord;
        return(finalWord);
}






