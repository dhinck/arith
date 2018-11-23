/*
 * deompress.c
 * COMP 40 HW 4
 * Rebecca Redelmeier & Darcy Hinck
 * October 26, 2017
 * 
 * Purpose: Implementation for image decompression
 */

#include <stdlib.h>
#include "decompress.h"
#include <stdint.h>
#include <seq.h>
#include <pnm.h>
#include <assert.h>
#include "ManipulateWordElements.h"
#include "RGB_CV_Transforms.h"

/* FUNCTION PROTOTYPES*/
uint64_t * makeCurrWord(FILE *input);
void placeCurrSeq(Seq_T currSeq, int col, int row, UArray2_T);

/*
 * Purpose: Call required functions to decompress a file, place new
 *          decompressed file in the passed in UArray2
 */
void decompressImage(FILE *input, UArray2_T imageArray)
{
        int placeCol = 0;
        int placeRow = 0;


        int max = (UArray2_width(imageArray) / 2) * 
                (UArray2_height(imageArray) / 2);

        //what if the file is longer than specified by the header?!
        for (int n = 0; n < max; n++) {
                uint64_t *currWord = makeCurrWord(input);
                
                if (placeCol >= UArray2_width(imageArray)) {
                        placeCol = 0;
                        placeRow += 2;
                }

                Seq_T currSeq = convertToSequence(*currWord);

                free(currWord);

                placeCurrSeq(currSeq, placeCol, placeRow, imageArray);
                placeCol += 2;
        }
}

/*
 * Purpose: Return a uint64_t made from a word in the FILE
 * Error: CRE if file is smaller than indicated by header
 */
uint64_t * makeCurrWord(FILE *input) 
{
        char *word = malloc(4 * sizeof(char));
        assert(word);

        for (int i = 0; i < 4; i++) {
                int curr = getc(input);
                assert(curr != EOF);
                word[i] = (char)curr;
        } 

        uint64_t *currWord = (uint64_t*)word;

        return(currWord);
}

/*
 * Purpose: Place a sequence of pixels in the appropriate places in the UArray2
 */
void placeCurrSeq(Seq_T currSeq, int placeCol, int placeRow, 
        UArray2_T imageArray)
{
        int count = 0;
        for (int i = 0; i < 2; i++) {
                for (int n = 0; n < 2; n++) {
                        CV currCV = Seq_get(currSeq, count);
                        count++;

                        Pnm_rgb backtoRGB = CVtoRGB(currCV);
                        free(currCV);
                        struct Pnm_rgb *curr = (struct Pnm_rgb *)
                                UArray2_at(imageArray, placeCol + n, 
                                        placeRow + i);
                        curr->red = backtoRGB->red;
                        curr->green = backtoRGB->green;
                        curr->blue = backtoRGB->blue;
                        free(backtoRGB);
                }
        }
        Seq_free(&currSeq);        
}








