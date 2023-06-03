//
// Created by hungt on 2023-04-22.
//
#include <string.h>
#include "db.h"
#include "stdio.h"

int gen_rec(const char * name, int age, float loan, void * buff, int buffSize)
{
    char *cBuff = (char *) buff;
    char *cur_buff = cBuff;
    if(buffSize < strlen(name) + sizeof(int) + sizeof(float) + sizeof(int)) return -1;
    int str_len = strlen(name);
    memcpy(cur_buff, &str_len, sizeof(int));
    cur_buff += sizeof(int);
    memcpy(cur_buff, name, str_len);
    cur_buff += str_len;
    memcpy(cur_buff, &age, sizeof(int));
    cur_buff += sizeof(int);
    memcpy(cur_buff, &loan, sizeof (float));
    cur_buff += sizeof(float);
    printf("Gen_rec: cur_buff - cBuff: %d\n", cur_buff - cBuff);
    return cur_buff - cBuff;
}

int degen_rec(char *name, int *age, float *loan, void *buff, int buffSize)
{
    char *cbuff = (char *)buff;
    char *cur_buff =  cbuff;
    if(buffSize < strlen(name) + sizeof (int) + sizeof (float) + sizeof (int)) return -1;
    int str_len = 0;
    memcpy(&str_len, cur_buff, sizeof (int));
    cur_buff += sizeof(int);
    memcpy(name, cur_buff, str_len);
    cur_buff += str_len;
    memcpy(age, cur_buff, sizeof (int));
    cur_buff += sizeof (int);
    memcpy(loan, cur_buff, sizeof (float));
    cur_buff += sizeof(float);
    printf("Degen_rec: cur_buff - cBuff: %d\n", cur_buff - cbuff);
    return cur_buff - cbuff;
}

int main(int argc, const char * argv[])
{
    DB_HANDLE db = open_db("db.bin");
    char buff[256];
    int rec_size = gen_rec("Alex", 19, 1000.0, buff, 256);
    int rec_id = add(buff, rec_size, db);
    memset(buff, 0, 256);
    rec_size = read(buff, 256, db, rec_id);
    char name[] = "      ";
    int age = 0;
    float loan = 0.0;
    degen_rec(name, &age, &loan, buff, 256);
    printf("%s %d %f\n", name, age,loan);
    close_db(db);
}