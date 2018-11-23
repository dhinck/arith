/*
 *  Quantizing.h
 *  COMP 40 HW4 
 *  Darcy Hinck & Rebecca Redelmeier
 *  October 21, 2017
 *
 *  Purpose: Declare necessary quantize functions
 *
 */

#ifndef QUANTIZE_INCLUDED
#define QUANTIZE_INCLUDED

unsigned quantizeA(float);

signed quantizeBCD(float);

float unquantizeA(unsigned);

float unquantizeBCD(signed);

#endif