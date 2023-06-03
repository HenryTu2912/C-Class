//
// Created by hungt on 2023-04-23.
//
#include "stdio.h"
#include "stdlib.h"

//255 -> 11111111
void showBits(int value, int bytes)
{
    unsigned int filter = 1; //00000001
    int bit;
    char *bitString = (char *) malloc(33);
    for(bit = 0; bit < bytes * 8; bit++)
    {
        if(value & filter)
        {
            bitString[31-bit] = '1';
        }
        else
        {
            bitString[31-bit] = '0';
        }
        filter *= 2;
    }
    bitString[32] = 0;
    printf("The value %16u is \t%s\n", value, bitString[32-bytes*8]);
    free(bitString);
}

unsigned int reverseBits(unsigned int d)
{
    unsigned char totalBits = 32;
    unsigned int rs = 0;
    unsigned int curBit = 0;
    for(int i = 0; i < totalBits; i ++)
    {
        curBit = d & (1<<i);
        if(curBit)
        {
            rs |= 1 << (totalBits - i - 1);
        }
    }
    return rs;
}

void bitAND()
{
    unsigned char a = 0x48;
    unsigned char b = 0x88;
    unsigned rs = a & b;
    int x = 0x030B1A0F;
    int maskFindBit = 0x00000010;
    unsigned int maskSetBitToZero = 0xFFFFFFFF;
}

void bitSHIFT()
{
    short x = 37;
    int z = 1;
    signed char y = -128;
    char value = 0xD3;
    char mask = 0x0F;
    unsigned char uc = 0b11010011;
    showBits(uc, 1);
}

unsigned char swapNibbles(unsigned char c)
{
    return (c<<4) | (c>>4);
}

unsigned char blendNibbles(unsigned char a, unsigned char b)
{
    return (a & 0xf0) | (b & 0x0f);
}