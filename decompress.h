/*
 * decompress.h
 * COMP 40 HW 4
 * Rebecca Redelmeier & Darcy Hinck
 * October 21, 2017
 * 
 * Purpose: Interface for decompressing an image
 */

#include <stdio.h>
#include "uarray2.h"

#ifndef _DECOMPRESS_IMAGE
#define _DECOMPRESS_IMAGE

void decompressImage(FILE *input, UArray2_T imageArray);

#endif