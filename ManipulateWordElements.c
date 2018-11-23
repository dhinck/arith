/*
 *  DCTransforms.c
 *  COMP 40 HW4 
 *  Darcy Hinck & Rebecca Redelmeier
 *
 *  Purpose: Implement functions that create a, b, c, d, Pb, Pr elements from
 *           the Y, Pb, Pr elements, and vice versa
 */

#include "ManipulateWordElements.h"
#include "Quantizing.h"
#include <arith40.h>
#include <stdlib.h>
#include <stdio.h>
#include "ModifyWordPack.h"
#include <assert.h>

/* number of pixels per block compressed */
const float PIXBLOCK = 4.0;

struct wordParts {
        unsigned a;
        signed b;
        signed c;
        signed d;
        unsigned Pb;
        unsigned Pr;

};

struct ComponentVideo {
        float y;
        float pb;
        float pr;

};

/* FUNCTION PROTOTYPES */
unsigned makeLuma(float a, float b, float c, float d);

/* Purpose: Converts the 4 CV pixels pased in that are held in the Seq_t
            to a uint64_t word */
uint64_t convertToWord(Seq_T cvPixels)
{
        
        struct ComponentVideo *cv1 = Seq_remlo(cvPixels);
        struct ComponentVideo *cv2 = Seq_remlo(cvPixels);
        struct ComponentVideo *cv3 = Seq_remlo(cvPixels);
        struct ComponentVideo *cv4 = Seq_remlo(cvPixels);

        float y4 = cv4->y;
        float y3 = cv3->y;
        float y2 = cv2->y;
        float y1 = cv1->y;

        struct wordParts currWord;

        currWord.a = quantizeA((y4 + y3 + y2 + y1) / PIXBLOCK);
        currWord.b = quantizeBCD((y4 + y3 - y2 - y1) / PIXBLOCK);
        currWord.c = quantizeBCD((y4 - y3 + y2 - y1) / PIXBLOCK);
        currWord.d = quantizeBCD((y4 - y3 - y2 + y1) / PIXBLOCK);

        currWord.Pb = makeLuma(cv1->pb, cv2->pb, 
                cv3->pb, cv4->pb); 
        currWord.Pr = makeLuma(cv1->pr, cv2->pr, 
                cv3->pr, cv4->pr);

        uint64_t packedWord = packWord(&currWord);

        free(cv1);
        free(cv2);
        free(cv3);
        free(cv4);
        Seq_free(&cvPixels);

        return(packedWord);

}

/* Purpose: Make the luma elelment from the cosine coefficients passed in */
unsigned makeLuma(float a, float b, float c, float d)
{
        float average = ((a + b + c + d) / PIXBLOCK);
        return (Arith40_index_of_chroma(average));
}

/* Purpose: Reverse quantaizes the a, b, c, and d value of the Cosine
            Coefficient struct. Then, creates a new ComponentVideo struct
            for each pixel (4). Assigne the corresponding y, Pb, and Pr to this 
            pixel. Places each pixel in a Seq_t of length 4 and return it. */
Seq_T convertToSequence(uint64_t packedWord)
{
        wordP currWord = unpackWord(packedWord);

        Seq_T currSeq = Seq_new(4);

        float a = unquantizeA(currWord->a);
        float b = unquantizeBCD(currWord->b);
        float c = unquantizeBCD(currWord->c);   
        float d = unquantizeBCD(currWord->d);
        
        float y1 = (a - b - c + d);
        float y2 = (a - b + c - d);
        float y3 = (a + b - c - d);
        float y4 = (a + b + c + d);

        float pr = Arith40_chroma_of_index(currWord->Pr);
        float pb = Arith40_chroma_of_index(currWord->Pb);


        struct ComponentVideo *cv1 = malloc(sizeof(struct ComponentVideo));
        assert(cv1);
        cv1->y = y1;
        cv1->pr = pr;
        cv1->pb = pb;
        Seq_addhi(currSeq, cv1);

        struct ComponentVideo *cv2 = malloc(sizeof(struct ComponentVideo));
        assert(cv2);
        cv2->y = y2;
        cv2->pr = pr;
        cv2->pb = pb;
        Seq_addhi(currSeq, cv2);

        struct ComponentVideo *cv3 = malloc(sizeof(struct ComponentVideo));
        assert(cv3);
        cv3->y = y3;
        cv3->pr = pr;
        cv3->pb = pb;
        Seq_addhi(currSeq, cv3);

        struct ComponentVideo *cv4 = malloc(sizeof(struct ComponentVideo));
        assert(cv4);
        cv4->y = y4;
        cv4->pr = pr;
        cv4->pb = pb;
        Seq_addhi(currSeq, cv4);

        free(currWord);

        return(currSeq);

}



