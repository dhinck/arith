/*
 * Compress40.c
 * COMP 40 HW 4
 * Rebecca Redelmeier & Darcy Hinck
 * October 21, 2017
 * 
 * Purpose: Call appropraite compress or decompress interface
 */

#include "uarray2.h"
#include <compress40.h>
#include <pnm.h>
#include <a2plain.h>
#include "compress.h"
#include <stdio.h>
#include <stdlib.h>
#include "decompress.h"
#include <assert.h>
#include <stdint.h>

const unsigned DENOMINATOR = 255;

/* FUNCTION PROTOTYPES */
Pnm_ppm checkEven(Pnm_ppm original);
void printCompressed(int, int, UArray2_T, void *, void *);
void makeEvenUArray2(int col, int row, UArray2_T even, void *elem, void *odd);


/*
 * Purpose: Call required interface to compress an image and call to print
 *          out the returned compressed image
 */
extern void compress40(FILE *input)
{
        A2Methods_T methods = uarray2_methods_plain;
        Pnm_ppm original = Pnm_ppmread(input, methods);
        
        original = checkEven(original);

        UArray2_T tempP = original->pixels;
        original->pixels = compress(original);

        printf("COMP40 Compressed image format 2\n%u %u\n", (original->width),
                (original->height));
        UArray2_map_row_major(original->pixels, printCompressed, NULL);

        UArray2_free(&tempP);
        Pnm_ppmfree(&original);
} 

/*
 * Purpose: Print the compressed image to standard output
 */
void printCompressed(int col, int row, UArray2_T wordsArray2, void *elem, 
        void *cl)
{
        (void)col;
        (void)row;
        (void)wordsArray2;
        (void)cl;

        char *currElem = (char *)elem;

        for (int i = 0; i < 4; i++) {
                putchar(currElem[i]);
        }
}

/*
 * Purpose: Call required interface to decompress an image and print
 *          out the returned compressed image
 */
extern void decompress40(FILE *input)
{

        unsigned height, width;

        int read = fscanf(input, "COMP40 Compressed image format 2\n%u %u", 
                           &width, &height);
        assert(read == 2);
        int c = getc(input);
        assert(c == '\n');

        UArray2_T pixels = UArray2_new(width, height, sizeof(struct Pnm_rgb));

        decompressImage(input, pixels);

        Pnm_ppm pixmap = malloc(sizeof(struct Pnm_ppm)); 

        pixmap->width = width;
        pixmap->height = height;
        pixmap->denominator = DENOMINATOR;
        pixmap->pixels = pixels;
        pixmap->methods = uarray2_methods_plain;
        
        Pnm_ppmwrite(stdout, pixmap);
        Pnm_ppmfree(&pixmap);

}


/*
 * Purpose: Check if Pnm_ppm passed in has even rows and cols. If not, shave
 *          last row and/or col to make it even. Return the new even Pnm_ppm
 */
Pnm_ppm checkEven(Pnm_ppm original)
{
        unsigned width = original->width;
        if (width == 1) {
                exit(EXIT_FAILURE);
        }
        if ((width % 2) != 0) {
                width = width - 1;
        }

        unsigned height = original->height;
        if (height == 1) {
                exit(EXIT_FAILURE);
        }
        if ((height % 2) != 0) {
                height = height - 1;
        }

        if (width != original->width || height != original->height) {
                original->width = width;
                original->height = height;
                UArray2_T newEven = UArray2_new(width, height, 
                        sizeof(struct Pnm_rgb));

                UArray2_map_row_major(newEven, makeEvenUArray2, &(original->pixels));
                UArray2_T tempP = original->pixels;
                original->pixels = newEven;
                UArray2_free(&tempP);
        }
        return original;
}

/*
 * Purpose: Map function to turn UArray2 with odd width and/or height into one
 *          with even width and or height
 */
void makeEvenUArray2(int col, int row, UArray2_T even, void *elem, void *odd)
{
        (void)even;
        
        struct Pnm_rgb *toAdd = UArray2_at((*(UArray2_T*)odd), col, row);
        
        *(struct Pnm_rgb*)elem = *toAdd; 
}
