//
// Created by hungt on 2023-04-14.
//
#include "bitmap.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>

FILE * getFile(char * prompt, char * mode)
{
    FILE * file = NULL;
    char fn[256];
    fn[0] = '\0';
    printf("%s", prompt);
    fgets(fn, 255, stdin);
    file = fopen(fn, mode);
    return file;
}

void fileIoErrorHandler(FILE * f)
{
    int err = ferror(f);
    if(err)
    {
        printf("Error %d: %s\n", err, strerror(err));
    }
    else
    {
        printf("Unknown reason caused failed to read/write file\n");
    }
}

void readHeader(IMAGE * image, FILE * f)
{
    BOOL bSuccess = FALSE;
    image->bmHDR = (BITMAPHDR *) malloc(sizeof (BITMAPHDR));
    if(image->bmHDR)
    {
        if(fread(image->bmHDR, sizeof(BITMAPHDR), 1, f) == 1)
        {
            bSuccess = TRUE;
        }
        else
        {
            fileIoErrorHandler(f);
        }
    }
    if(!bSuccess && image->bmHDR)
    {
        free(image->bmHDR);
        image->bmHDR = NULL;
        printf("Read header from file failed.\n");
    }
}

void readData(IMAGE * image, FILE * f)
{
    BOOL bSuccess = FALSE;
    unsigned int size = 0;
    //3 pixels in a row
    //=> 3 pixels x 3 = 9 bytes
    //Padding 3 bytes so total is 12 bytes per row
    unsigned int padding = image->bmHDR->dwWidth % 4;
    size = (image->bmHDR->dwWidth * sizeof(PIXEL) + padding) * image->bmHDR->dwHeight;
    image->bmData = (PIXEL *) malloc(size);
    if(image->bmHDR)
    {
        if(fread(image->bmData, size, 1, f) == 1)
        {
            bSuccess = TRUE;
        }
    }
    if(!bSuccess && image->bmData)
    {
        free(image->bmData);
        image->bmData = NULL;
        printf("Failed to read image data.\n");
    }
}

void readImage(IMAGE * image, FILE * f)
{
    readHeader(image, f);
    if(image->bmHDR)
    {
        readData(image, f);
    }
}

void printHeader(IMAGE * image)
{
    BITMAPHDR * headerPtr = image->bmHDR;
    printf("First two characters: %x\n",headerPtr->wType);
    printf("File size: %d\n",headerPtr->dwFileSize);
    printf("Data offset: %d\n",headerPtr->dwDataOffset);
    printf("Dimensions: %d by %d\n",headerPtr->dwWidth, headerPtr->dwHeight);
    printf("Planes: %d\n",headerPtr->wPlanes);
    printf("Color depth: %d\n",headerPtr->wBitCount);
    printf("Compression: %d\n",headerPtr->dwCompression);
    printf("Image size: %d\n",headerPtr->dwImageSize);
    printf("Colors used: %d\n",headerPtr->dwClrUsed);
}

void freeImage(IMAGE * image)
{
    free(image->bmHDR);
    image->bmHDR = NULL;
    free(image->bmData);
    image->bmData = NULL;
}

void writeHeader(IMAGE * image, FILE * file)
{
    if(fwrite(image->bmHDR, sizeof(BITMAPHDR), 1, file) != 1)
    {
        printf("Failed to write image header\n");
    }
}

void writeData(IMAGE * image, FILE * file)
{
    unsigned int size, padding;
    padding = image->bmHDR->dwWidth % 4;
    size = (image->bmHDR->dwWidth * sizeof(PIXEL) + padding) * image->bmHDR->dwHeight;
    if(fwrite(image->bmData, size, 1, file) != 1)
    {
        printf("Failed to write image data\n");
    }
}

void writeImage(IMAGE * image, FILE * file)
{
    writeHeader(image, file);
    writeData(image, file);
}

PIXEL * getPixel(unsigned int row, unsigned int col, IMAGE * image)
{
    unsigned int padding = image->bmHDR->dwWidth % 4;
    unsigned int offset = (image->bmHDR->dwWidth * sizeof(PIXEL) + padding) * row + col * sizeof(PIXEL);
    return (PIXEL *) (((BYTE *) image->bmData) + offset);
}

#define MIN(a, b) a < b

void processTwoImages(IMAGE * image1, IMAGE * image2, BMP_FUN_PTR_TWO func)
{
    unsigned int height = MIN(image1->bmHDR->dwHeight, image2->bmHDR->dwHeight);
    unsigned int width = MIN(image1->bmHDR->dwWidth, image2->bmHDR->dwWidth);
    for(unsigned int i = 0; i < height; i++)
    {
        for(unsigned int j = 0; j < width; j++)
        {
            func(getPixel(i, j, image1), getPixel(i, j, image2));
        }
    }
}

void processImage(IMAGE * image, BMP_FUN_PTR_ONE func)
{
    for(unsigned int i = 0; i < image->bmHDR->dwHeight; i++)
    {
        for(unsigned int j = 0; j < image->bmHDR->dwWidth; j++)
        {
            func(getPixel(i, j, image));
        }
    }
}

IMAGE resizeImage(IMAGE * image, unsigned int newWidth, unsigned int newHeight)
{
    IMAGE imageNew = {NULL, NULL};
    int newImageSize = 0;
    int padding = 0;
    unsigned int width, height;
    PIXEL startPixel = {255,255,255};
    imageNew.bmHDR = (BITMAPHDR *) malloc(sizeof(BITMAPHDR));
    if(imageNew.bmHDR)
    {
        memcpy(imageNew.bmHDR,image->bmHDR, sizeof(BITMAPHDR));
        imageNew.bmHDR->dwWidth = newWidth;
        imageNew.bmHDR->dwHeight = newHeight;
        padding = newWidth % 4;
        newImageSize = (newWidth * sizeof(PIXEL) + padding) * newHeight;
        imageNew.bmHDR->dwImageSize = newImageSize;
        imageNew.bmHDR->dwFileSize = newImageSize + sizeof(BITMAPHDR);

        imageNew.bmData = (PIXEL *) malloc(newImageSize);
        memset(imageNew.bmData, 0x00, newImageSize);
        if(imageNew.bmData)
        {
            height = newHeight < image->bmHDR->dwHeight ? newHeight : image->bmHDR->dwHeight;
            width = newWidth < image->bmHDR->dwWidth ? newWidth : image->bmHDR->dwWidth;
            for(unsigned int i = 0; i < height; i++)
            {
                for(unsigned int j = 0; j < width; j++)
                {
                    *getPixel(i, j, &imageNew) = *getPixel(i, j ,image);
                }
            }
        }
    }
    return imageNew;
}

IMAGE crop(IMAGE * image, unsigned int left, unsigned int top,
           unsigned int newWidth, unsigned int newHeight)
{
    IMAGE imageNew = {NULL, NULL};
    if(image->bmHDR->dwWidth < left + newWidth || image->bmHDR->dwHeight < top + newHeight)
    {
        return imageNew;
    }
    int newImageSize = 0;
    int padding = 0;
    unsigned int width, height;
    PIXEL startPixel = {255,255,255};
    imageNew.bmHDR = (BITMAPHDR *) malloc(sizeof(BITMAPHDR));
    if(imageNew.bmHDR)
    {
        memcpy(imageNew.bmHDR, image->bmHDR, sizeof(BITMAPHDR));
        imageNew.bmHDR->dwWidth = newWidth;
        imageNew.bmHDR->dwHeight = newHeight;
        padding = newWidth % 4;
        newImageSize = (newWidth * sizeof (PIXEL) + padding) * newHeight;
        imageNew.bmHDR->dwImageSize = newImageSize;
        imageNew.bmHDR->dwFileSize = newImageSize + sizeof (BITMAPHDR);
        imageNew.bmData = (PIXEL *) malloc(newImageSize);
        memset(imageNew.bmData, 0x00, newImageSize);
        if(imageNew.bmData)
        {
            for(unsigned int i = 0; i < newHeight; i++)
            {
                for(unsigned int j = 0; j < newWidth; j++)
                {
                    *getPixel(i, j, &imageNew) = *getPixel(i+top, j+left, image);
                }
            }
        }
    }
    return imageNew;
}

void initPixels(IMAGE * image, PIXEL p)
{
    for(unsigned int i = 0; i < image->bmHDR->dwHeight; i++)
    {
        for(unsigned int j = 0; j < image->bmHDR->dwWidth; j++)
        {
            *(getPixel(i, j, image)) = p; // Memcpy(getPixel(i,j,image), &p, sizeof(PIXEL))
        }
    }
}

IMAGE rotate(IMAGE * image, double theta)
{
    unsigned int imageSize = 0, padding = 0;
    IMAGE newImage = {NULL, NULL};
    newImage.bmHDR = (BITMAPHDR *) malloc(sizeof (BITMAPHDR));
    memcpy(newImage.bmHDR, image->bmHDR, sizeof(BITMAPHDR));
    padding = newImage.bmHDR->dwWidth % 4;
    imageSize = (newImage.bmHDR->dwWidth * sizeof(PIXEL) + padding) * newImage.bmHDR->dwHeight;
    newImage.bmData = (PIXEL *) malloc(imageSize);
    PIXEL startPixel = {0, 255, 128};
    initPixels(&newImage, startPixel);
    int ox = newImage.bmHDR->dwWidth/2;
    int oy = newImage.bmHDR->dwHeight/2;
    int x, y;
    for(int pY = 0; pY < newImage.bmHDR->dwHeight; pY++)
    {
        for(int pX = 0; pX < newImage.bmHDR->dwWidth; pX++)
        {
            x = (unsigned int) (cos(theta) * (pX - ox) - sin(theta) * (pY - oy) + ox);
            y = (unsigned int) (sin(theta) * (pX - ox) + cos(theta) * (pY - oy) + oy);
            if(x >= 0 && x < newImage.bmHDR->dwWidth && y >= 0 && y < newImage.bmHDR->dwHeight)
            {
                *getPixel(y, x, &newImage) = *getPixel(pY, pX, image);
            }
        }
    }
    return newImage;
}
void antiAlias(IMAGE * image);