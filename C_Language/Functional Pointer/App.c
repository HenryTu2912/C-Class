//
// Created by hungt on 2023-04-24.
//
#include "funcpointer.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "stdlib.h"

int comareA(int a, int b) {return a-b;}
void getExactStringFromUserInput()
{
    char buf[250];
    buf[0] = 0;
    printf("Enter string: ");
    fgets(buf, 250, stdin);
    char *userinput = strdup(buf);
    char *userdata = (char *) malloc(strlen(buf) + 1 + 1);
    strcpy(userdata, buf);
    printf("%s", userdata);
}

int main(int argc, char **argv)
{
    //sortInts({1,2,3,4}, 4, comareA);
    getExactStringFromUserInput();
}