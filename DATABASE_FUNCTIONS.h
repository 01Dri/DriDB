#include <stdbool.h>
#ifndef DATABASE_FUNCTIONS_H
#define DATABASE_FUNCTIONS_H

void showTables();
void showDatabaseOption();
bool existDatabase(char stringConnection[]);
void connectDb(char stringConnection[]);
void startDb();
char* parseStringConnection(char stringConnection[]);

#endif  // DATABASE_FUNCTIONS_H
