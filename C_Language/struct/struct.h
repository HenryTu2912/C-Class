//
// Created by hungt on 2023-04-23.
//

#ifndef C_LANGUAGE_STRUCT_H
#define C_LANGUAGE_STRUCT_H
#pragma pack(push)
#pragma pack(1)
typedef struct _BirthDate{
    char *name;
    char gender;
    int day;
    int month;
    int year;
} BirthDate;
#pragma pack(pop)

typedef struct _student{
    char *namePtr;
    int studentNo;
    int * markPtr;
    int markCount;
}Student;

typedef struct _classroom{
    unsigned short numStudent;
    Student **sPtrPtr;
} Classroom;

Classroom  *PopulateClassroom();
void displayClassroom(Classroom *c);
void freeClassroom(Classroom *c);

typedef struct _pixel{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
}Pixel;

typedef union{
    unsigned int val;
    Pixel components;
}Color;

typedef union{
    char a;
    int i;
}FOO;

typedef union{
    unsigned int dword_val;
    struct words{
        unsigned short high;
        unsigned short low;
    };
    struct nibbles{
        unsigned char four;
        unsigned char three;
        unsigned char two;
        unsigned char one;
    };
    unsigned char nibble_arr[4];
    unsigned short words_arr[2];
}DWORD;

#endif //C_LANGUAGE_STRUCT_H
