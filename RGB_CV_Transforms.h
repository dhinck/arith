/*
 *  RGB_CV_Transforms.h
 *  COMP 40 HW4 
 *  Darcy Hinck & Rebecca Redelmeier
 *
 *  Purpose: Declare functions that converts RGB to Component Video
 *               and vice-versa, defines
 *
 */

#ifndef RGB_CV_TRANSFORM
#define RGB_CV_TRANSFORM

#include <pnm.h>

typedef struct ComponentVideo *CV;

/* Purpose: Converts a Pnm_rgb struct into a ComponentVideo struct. Will
            call calculations outlined in spec. First will convert
            r, g, and b to a floating point number. */
CV RGBtoCV(Pnm_rgb toConvert);

/* Purpose: Converts a ComponentVideo struct into a Pnm_rgb struct. Will
            call calculations outlined in spec */
Pnm_rgb CVtoRGB(CV toConvert);

#endif