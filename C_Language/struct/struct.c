//
// Created by hungt on 2023-04-23.
//
#include "struct.h"
#include "memory.h"
#include "mem.h"
#include "stdio.h"
#include "stdlib.h"

Student *createStudent(char *name, int num, int *marks, int markCount)
{
    Student *student = (Student *) malloc(sizeof (Student));
    if(student)
    {
        student->namePtr = strdup(name);
        student->studentNo = num;
        student->markPtr = (int *) malloc(sizeof (int) * markCount);
        memcpy(student->markPtr, marks, sizeof(int) * markCount);
        student->markCount = markCount;
    }
    return student;
}

void freeStudent(Student *student)
{
    free(student->namePtr);
    free(student->markPtr);
    free(student);
}

void displayStudent(Student *student)
{
    printf("\nName: %s\n", student->namePtr);
    printf("Student num: %d", student->studentNo);
    printf("Marks:\n");
    for(int i = 0; i < student->markCount; i++)
    {
        printf("%d ", student->markPtr[i]);
    }
    printf("\n\n");
}

Student *getStudent()
{
    char name[256];
    name[0] = '\0';
    int studentNum = 0;
    int marks[2];
    printf("Enter the name: ");
    getc(stdin);
    fgets(name, 256, stdin);
    printf("Enter the student number: ");
    scanf("%d", &studentNum);
    printf("Enter two marks:");
    scanf("%d %d", &marks[0], &marks[1]);
    return createStudent(name, studentNum, marks, 2);
}

Classroom  *PopulateClassroom()
{
    Classroom *c = malloc(sizeof (Classroom));
    printf("Enter number of students: ");
    scanf("%hu", &c->numStudent);
    c->sPtrPtr = (Student **) malloc(c->numStudent * sizeof (Student*));
    for(int i = 0; i < c->numStudent; i++)
    {
        c->sPtrPtr[i] = getStudent();
    }
}

void displayClassroom(Classroom *c)
{
    for(int i = 0; i < c->numStudent; i++)
    {
        displayStudent(c->sPtrPtr[i]);
    }
}

void freeClassroom(Classroom *c)
{
    for(int i = 0; i < c->numStudent; i++)
    {
        freeStudent(c->sPtrPtr[i]);
    }
    free(c->sPtrPtr);
    free(c);
}