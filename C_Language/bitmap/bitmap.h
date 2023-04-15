//
// Created by hungt on 2023-04-14.
//

#ifndef C_LANGUAGE_BITMAP_H
#define C_LANGUAGE_BITMAP_H

#include "stdio.h"
#define BOOL unsigned char
#define TRUE 1
#define FALSE 0

#define BYTE unsigned char
#define WORD unsigned char
#define DWORD unsigned int

#pragma pack(push) // Use to store the default byte alignment
#pragma pack(1) // Set the byte alignment to 1

typedef struct _bitmap_header
{
    WORD wType;
    DWORD dwFileSize;
    WORD wReserved1;
    WORD wReserved2;
    DWORD dwDataOffset;
    DWORD dwHeaderSize;
    DWORD dwWidth;
    DWORD dwHeight;
    WORD wPlanes;
    WORD wBitCount;
    DWORD dwCompression;
    DWORD dwImageSize;
    DWORD dwXPelsPerMeter;
    DWORD dwYPelsPerMeter;
    DWORD dwClrUsed;
    DWORD dwClrImportant;
}BITMAPHDR;

typedef struct _pixel
{
    //Strangely, blue comes first in the pixel
    BYTE bBlue, bGreen, bRed
} PIXEL;

typedef struct _image
{
    BITMAPHDR * bmHDR;
    PIXEL * bmData;
} IMAGE;

#pragma pack(pop) //Use to reset the default byte alignment

FILE * getFile(char * prompt, char * mode);
void readImage(IMAGE * image, FILE * f);
void readHeader(IMAGE * image, FILE * f);
void readData(IMAGE * image, FILE * f);
void printHeader(IMAGE * image);
void freeImage(IMAGE * image);
void writeImage(IMAGE * image, FILE * file);
void writeHeader(IMAGE * image, FILE * file);
void writeData(IMAGE * image, FILE * file);

typedef void (* BMP_FUN_PTR_ONE) (PIXEL *);
typedef void (* BMP_FUN_PTR_TWO) (PIXEL *, PIXEL *);
void processTwoImages(IMAGE * image1, IMAGE * image2, BMP_FUN_PTR_TWO func);
void processImage(IMAGE * image, BMP_FUN_PTR_ONE func);
PIXEL * getPixel(unsigned int row, unsigned int col, IMAGE * image);

IMAGE resizeImage(IMAGE * image, unsigned int newWidth, unsigned int newHeight);
IMAGE crop(IMAGE * image, unsigned int left, unsigned int top,
           unsigned int newWidth, unsigned int newHeight);
IMAGE rotate(IMAGE * image, double theta);
void antiAlias(IMAGE * image);

#endif //C_LANGUAGE_BITMAP_H
