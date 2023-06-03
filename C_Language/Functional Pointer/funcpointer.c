//
// Created by hungt on 2023-04-24.
#include "funcpointer.h"

void sortInts(int arr[], int size, COMPARATOR comp)
{
    int i, key, j;
    for(i = 1; i < size; i++)
    {
        key = arr[i];
        j = i - 1;
        while(j >= 0 && comp(arr[j], key) > 0)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void processDoubles(double arr[], int size, MYROUNDUP round, PROCESSIT pro)
{
    for(int i = 0; i < size; i++)
    {
        arr[i] = round(arr[i]);
        pro(arr[i]);
    }
}