//
// Created by hungt on 2023-04-23.
//
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "struct.h"

int main(int argc, char **argv)
{
    Classroom *c = PopulateClassroom();
    displayClassroom(c);
    freeClassroom(c);
}