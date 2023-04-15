//
// Created by hungt on 2023-04-14.
//
#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"


int main(int argc, char ** argv)
{
    FILE * in = fopen("bike.bmp", "rb");
    FILE * out = fopen("newBike.bmp", "wb");
    IMAGE * image = (IMAGE *) malloc(sizeof(IMAGE));
    readImage(image,in);
    printHeader(image);
    IMAGE resizeOne = resizeImage(image, 100, 100);
    writeImage(&resizeOne, out);
    free(&resizeOne);
    freeImage(image);
    free(image);
    fclose(in);
    fclose(out);
}