/*
 *  Quantizing.c
 *  COMP 40 HW4 
 *  Darcy Hinck & Rebecca Redelmeier
 *
 *  Purpose: Define necessary quantize functions
 *
 */

#include <stdio.h>

const float FLOAT_CODE = 50.0;

/* Purpose: Quantize fuction for A coefficient */
unsigned quantizeA(float a)
{
        if (a > 1.0) {
                a = 1.0;
        }
        if (a < 0.0) {
                a = 0.0;
        }

        return(a * 511);
}

/* Purpose: Quantize fuction for B, C, D coefficient */
signed quantizeBCD(float n)
{
        if (n > 0.3) {
                n = 0.3;
        }

        if (n < -0.3) {
                n = -0.3;
        }

        return(n * FLOAT_CODE);
}

/* Purpose: Unquantize fuction for A coefficient */
float unquantizeA(unsigned a)
{
        float af = (a / 511.0);

        if (af > 1.0) {
                af = 1.0;
        }
        if (af < 0.0) {
                af = 0.0;
        }

        return(af);
}

/* Purpose: Unuantize fuction for B, C, D coefficient */
float unquantizeBCD(signed n)
{

        float nf = (n / FLOAT_CODE);
        if (nf > 0.3) {
                nf = 0.3;
        }
        if (nf < -0.3) {
                nf = -0.3;
        }

        return(nf);
}
