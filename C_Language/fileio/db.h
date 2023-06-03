//
// Created by hungt on 2023-04-22.
//

#ifndef C_LANGUAGE_DB_H
#define C_LANGUAGE_DB_H

#define DB_HANDLE void *
DB_HANDLE open_db(const char * fn);
void close_db(DB_HANDLE db);
int add(void * data, unsigned int size, DB_HANDLE db);
int read(void * buff, unsigned int buffSize, DB_HANDLE db, int recId);
#endif //C_LANGUAGE_DB_H
