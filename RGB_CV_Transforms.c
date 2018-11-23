/*
 *  RGB_CV_Transforms.c
 *  COMP 40 HW4 
 *  Darcy Hinck & Rebecca Redelmeier
 *  October 15, 2017
 *
 *  Purpose: Define functions that converts RGB to Component Video
 *               and vice-versa, defines
 *
 */

#include "RGB_CV_Transforms.h"
#include <stdlib.h>
#include <assert.h>
 
/* Scale factor for RGB to CV transforms */
const float COLOR_SCALE = 255.0;

float scale(int color);
int reverseScale(float color);
float getPr(float r, float g, float b);
float getY(float r, float g, float b);
float getPb(float r, float g, float b);
float getR(float y, float pb, float pr);
float getG(float y, float pb, float pr);
float getB(float y, float pb, float pr);


struct ComponentVideo {
        float y;
        float pb;
        float pr;

};

/* Interchangable with the Pnm_rgb struct defined by the 
 pnm.h interface */
struct RGB {
        unsigned red;
        unsigned green;
        unsigned blue;
};

/* Purpose: Convert an RGB struct to a CV struct */
CV RGBtoCV(Pnm_rgb toConvert)
{
        float red = scale(toConvert->red);

        float green = scale(toConvert->green);

        float blue = scale(toConvert->blue);



        CV currCV = malloc(sizeof(struct ComponentVideo));
        assert(currCV);
        currCV->y = getY(red, green, blue);
        currCV->pb = getPb(red, green, blue);
        currCV->pr = getPr(red, green, blue);

        return currCV;
}

/* Purpose: convert a CV struct to an RGB struct */
Pnm_rgb CVtoRGB(CV toConvert)
{
        float y = toConvert->y;
        float pb = toConvert->pb;
        float pr = toConvert->pr;

        Pnm_rgb currRGB = malloc(sizeof(struct RGB));
        assert(currRGB);
        currRGB->red = reverseScale(getR(y, pb, pr));
        currRGB->green = reverseScale(getG(y, pb, pr));
        currRGB->blue = reverseScale(getB(y, pb, pr));

        return currRGB;

}

/* Purpose: scale rgb numbers by the COLOR_SCALE before converting to
            CV */
float scale(int color)
{
        float colorFloat = (float)color;
        return (colorFloat / COLOR_SCALE);
}

/* Purpose: reverse scale the numbers converted back from CV to become
            an rgb */
int reverseScale(float color)
{
        float scaledColor = color * COLOR_SCALE;
        if (scaledColor > 255) {
                scaledColor = 255;
        }
        if (scaledColor < 0) {
                scaledColor = 0;
        }
        return (int)scaledColor;
}


/* PURPOSE OF ALL FUNCTIONS BELOW: Helper functions to perform
 * conversions from RGB to CV and CV to RGB 
 */

float getY(float r, float g, float b)
{
        return ((0.299 * r) + (0.587 * g) + (0.114 * b));
}

float getPb(float r, float g, float b)
{
        return ((-0.168736 * r) - (0.331264 * g) + (0.5 * b));
}

float getPr(float r, float g, float b)
{
        return ((0.5 * r) - (0.418688 * g) - (0.081312 * b));
}

float getR(float y, float pb, float pr)
{
        return ((1.0 * y) + (0.0 * pb) + (1.402 * pr));
}

float getG(float y, float pb, float pr)
{
        return ((1.0 * y) - (0.344136 * pb) - (0.714136 * pr));
}

float getB(float y, float pb, float pr)
{
        return ((1.0 * y) + (1.772 * pb) + (0.0 * pr));
}