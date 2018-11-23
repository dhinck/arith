 /*
 * Bitpack.c
 * COMP 40 HW 4
 * Rebecca Redelmeier & Darcy Hinck
 * October 21, 2017
 *
 *  Purpose: Implementation of bitpack interface
 */


#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <pnm.h>
#include <bitpack.h>


const uint64_t BASE_TWO = 2;
const uint64_t PACK_SIZE = 64;
const uint64_t PROCESSOR_SIZE = 32;
const uint64_t U_ONE = 1;
const int64_t I_ONE = -1;

Except_T Bitpack_Overflow = { "Overflow packing bits" };

uint64_t createMask(int lsb, int width);
uint64_t shiftRight(uint64_t word, uint64_t shiftVal);
uint64_t shiftLeft(uint64_t word, uint64_t shiftVal);

/* Purpose: Check if an unsigned fits into a specified width bits. Return true
            if so, else return false 
   Error: CRE if the width is <= 0
*/
bool Bitpack_fitsu(uint64_t n, unsigned width) 
{
        assert(width > 0);

        uint64_t max = shiftLeft(U_ONE, width);

        return (n <= max);
}

/* Purpose: Check if an signed int fits into a specified with bits. Return true
            if so, else return false 
   Error: CRE if the width is <= 0
*/
bool Bitpack_fitss(int64_t n, unsigned width)
{

        assert(width > 0);

        int64_t min = I_ONE * (shiftLeft(U_ONE, (width - U_ONE)));
        int64_t max = (shiftLeft(U_ONE, (width - U_ONE)) - U_ONE);

        if (n >= 0) {
                return (n <= max);
        }

        return (n >= min);
}

/* 
  Purpose: Extract a specified bitfield from a signed word
  Error: CRE if width is > pack size (64), if width + lsb > packsize, and
         if width is NULL.
*/
int64_t Bitpack_gets(uint64_t word, unsigned width, unsigned lsb)
{  
        assert(width && width <= PACK_SIZE);
        assert(width + lsb <= PACK_SIZE);

        uint64_t mask = createMask(lsb, width);

        int64_t getVal = shiftRight((word & mask), lsb);

        if (getVal >= (signed)shiftLeft(U_ONE, (width - U_ONE))) {
                uint64_t negMask = ~0;
                getVal = getVal | shiftLeft(negMask, (width));
        }

        return getVal;

 }
 
/* 
  Purpose: Place a specified bitfield in an signed word
  Error: CRE if width is > pack size (64), if width + lsb > packsize, and if
         width is NULL. Raised Bitpack_Overflow exception if value will not 
         fit in width bits.
*/
uint64_t Bitpack_news(uint64_t word, unsigned width, unsigned lsb,  
        int64_t value)
{
        assert(width && width <= PACK_SIZE);
        assert(width + lsb <= PACK_SIZE);

        
        if (Bitpack_fitss(value, width) == false) {
                RAISE(Bitpack_Overflow);
        }
    

        uint64_t mask = createMask(0, width);

        value = value & mask;

        mask = ~(createMask(lsb, width));

        uint64_t newWord = ((word & mask) | (shiftLeft(value, lsb)));

        return(newWord);
}

/* 
  Purpose: Extract a specified bitfield from an unsigned word
  Error: CRE if width is > pack size (64), if width + lsb > packsize, and if
         width is NULL
*/
uint64_t Bitpack_getu(uint64_t word, unsigned width, unsigned lsb)
{
        assert(width && width <= PACK_SIZE);
        assert(width + lsb <= PACK_SIZE);

        uint64_t mask = createMask(lsb, width);

        uint64_t maskValue = shiftRight((word & mask), lsb);

        return (maskValue);
}
 
/* 
  Purpose: Place a specified bitfield in an unsigned word
  Error: CRE width is > pack size (64), if width + lsb > packsize, and if
         width is NULL. Raised Bitpack_Overflow exception if value will not 
         fit in width bits.
*/
uint64_t Bitpack_newu(uint64_t word, unsigned width, unsigned lsb, 
        uint64_t value)
{
        assert(width && width <= PACK_SIZE);
        assert(width + lsb <= PACK_SIZE);

        if (Bitpack_fitsu(value, width) == false) {
                RAISE(Bitpack_Overflow);
        }

        uint64_t mask = ~(createMask(lsb, width));

        uint64_t newWord = ((word & mask) | (shiftLeft(value, lsb)));

        return (newWord);
}

/* 
  Purpose: Create a mask of all 1s between lsb and width
*/
uint64_t createMask(int lsb, int width)
{
        uint64_t mask = ~0;

        mask = shiftRight(mask, (PACK_SIZE - width));
        mask = shiftLeft(mask, lsb);

        return mask;
}
 
/* 
  Purpose: Shift a uint64_t left by the shift val
*/
uint64_t shiftLeft(uint64_t word, uint64_t shiftVal) 
{
        uint64_t shifted;

        if ((shiftVal) == PACK_SIZE) {
                return (((word << 31) << 31) << 2);
        }

        if (shiftVal >= 32) {
                shifted = word << 31; 
                shifted = shifted << (shiftVal - 31); 
        }
        else {
                shifted = word << shiftVal;
        }

        return shifted;
}

/* 
  Purpose: Shift a uint64_t right by the shift val
*/
uint64_t shiftRight(uint64_t word, uint64_t shiftVal)
{
        uint64_t shifted;

        if ((shiftVal) == PACK_SIZE) {
                return (((word >> 31) >> 31) >> 2);
        }

        if (shiftVal >= 32) {
                shifted = word >> 31; 
                shifted = shifted >> (shiftVal - 31); 
        }

        else {
                shifted = word >> shiftVal;
        }

        return shifted;
}



