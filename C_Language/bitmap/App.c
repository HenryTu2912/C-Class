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
    //Resize
//    IMAGE resizeOne = resizeImage(image, 100, 100);
//    writeImage(&resizeOne, out);
//    freeImage(&resizeOne);

    //Crop
//    IMAGE cropOne = crop(image, 100, 100, 90, 90);
//    writeImage(&cropOne, out);
//    freeImage(&cropOne);

    //Rotate
    IMAGE rotateImg = rotate(image, 0.1);
    writeImage(&rotateImg, out);
    freeImage(&rotateImg);

    freeImage(image);
    free(image);
    fclose(in);
    fclose(out);
}