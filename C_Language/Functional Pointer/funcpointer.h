//
// Created by hungt on 2023-04-24.
//

#ifndef C_LANGUAGE_FUNCPOINTER_H
#define C_LANGUAGE_FUNCPOINTER_H

typedef int (*COMPARATOR)(int, int);
typedef double (*MYROUNDUP)(double );
typedef void (*PROCESSIT) (double );

void sortInts(int arr[], int size, COMPARATOR comp);
void processDoubles(double arr[], int size, MYROUNDUP round, PROCESSIT pro);
double round(double d);
void printit(double d);
#endif //C_LANGUAGE_FUNCPOINTER_H
