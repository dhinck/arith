/*
 * Compress.s
 * COMP 40 HW 4
 * Rebecca Redelmeier & Darcy Hinck
 * October 26, 2017
 * 
 * Purpose: Implementation for image compression
 */

#include <seq.h>
#include "uarray2.h"
#include <pnm.h>
#include "RGB_CV_Transforms.h"
#include <stdlib.h>
#include "ManipulateWordElements.h"

#define SEQ_HINT 4

/* FUNCTION PROTOTYPES */
void createCVSeqs(int col, int row, UArray2_T original, void *elem, 
        void *toCompress);
void initSeqs(int col, int row, UArray2_T toCompress, void *elem, 
        void *cl);
void freeSeqs(int col, int row, UArray2_T toCompress, void *elem, 
        void *cl);
void buildWordUArray2(int col, int row, UArray2_T cvSeqUArray2, void *elem, 
        void *words);

/*
 * Purpose: Call required functions to compress an image and return the 
 *          UArray2 of the new compressed image
 */
UArray2_T compress(Pnm_ppm original)
{
        UArray2_T toCompress = UArray2_new((original->width / 2), 
                (original->height / 2), sizeof(Seq_T));

        //Init Sequences and then fill with CV structs
        UArray2_map_row_major(toCompress, initSeqs, NULL);
        UArray2_map_row_major(original->pixels, createCVSeqs, &toCompress);

        UArray2_T words = UArray2_new((original->width / 2), 
                (original->height / 2), sizeof(uint64_t));

        UArray2_map_row_major(toCompress, buildWordUArray2, &words);

        UArray2_free(&toCompress);

        return(words);

}

/*
 * Purpose: Apply function that puts each element in the Pnm_ppm
 *          pixels UArray2 in a sequence in a UArray2 of the width and
 *          height of the decompressed image
 */
void createCVSeqs(int col, int row, UArray2_T original, void *elem, 
        void *toCompress)
{
        Seq_T *currSeq = UArray2_at(*((UArray2_T*)toCompress), col/2, row/2);

        (void)original;
        CV cv = RGBtoCV((Pnm_rgb)elem);
        
        Seq_addlo(*currSeq, cv);
}

/*
 * Purpose: Apply function that creates a word from all elements in the
 *          Sequence that is at each element of the UArray2 being mapped on.
 */
void buildWordUArray2(int col, int row, UArray2_T cvSeqUArray2, void *elem, 
        void *words)
{
        (void)cvSeqUArray2;
        
        uint64_t currWord = convertToWord(*(Seq_T*)elem);
        
        void *currSpot = UArray2_at(*(UArray2_T*)words, col, row);

        *(uint64_t*)currSpot = currWord;

}

/*
 * Purpose: Apply function that initiates all sequences in the UArray2 
 */
void initSeqs(int col, int row, UArray2_T toCompress, void *elem, 
        void *cl)
{
        (void)col;
        (void)row;
        (void)toCompress;
        (void)cl;
        *(Seq_T*)elem = Seq_new(SEQ_HINT);

}