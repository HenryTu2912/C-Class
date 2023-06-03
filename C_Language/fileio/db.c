//
// Created by hungt on 2023-04-22.
//
#include "db.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

DB_HANDLE open_db(const char * fn)
{
    FILE *f = NULL;
    int err = EXIT_SUCCESS;
    f = fopen(fn, "ab+");
    if(f == NULL)
    {
        err = errno;
        printf("Got error: errno=%d, error message: %s\n", err, strerror(err));
    }
    else
    {
        printf("Successed\n");
    }
    return (DB_HANDLE) f;
}

void close_db(DB_HANDLE db)
{
    fclose((FILE *)db);
}

void handle_rw_error(FILE *f)
{
    int err = ferror(f);
    if(err)
    {
        printf("Error %d: %s\n", err, strerror(err));
    }
    else
    {
        printf("Unknown reason caused fauled to read file\n");
    }
}

int add(void * data, unsigned int size, DB_HANDLE db)
{
    FILE *f = (FILE *) db;
    fseek(f, 0, SEEK_END);
    int location = ftell(f);
    int bts = fwrite(&size, sizeof(unsigned int), 1, f);
    if(bts == 1)
    {
        //Write the size of the record first
    }
    else handle_rw_error(f);
    bts = fwrite(data, size, 1, f);
    if(bts == 1)
    {
        fflush(f);
        return location;
    }
    else handle_rw_error(f);
    return -1;
}

int read(void * buff, unsigned int buffSize, DB_HANDLE db, int recId)
{
    FILE *f = (FILE *) db;
    fseek(f, recId, SEEK_SET);
    unsigned int recSize = 0;
    int bts = fread(&recSize, sizeof (unsigned int ), 1, f);
    if(bts == 1)
    {
        return fread(buff, recSize < buffSize ? recSize:buffSize, 1, f);
    }
    else handle_rw_error(f);
}