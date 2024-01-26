
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include "DATABASE_FUNCTIONS.h"



void showTables() {
    
}


void showDatabaseOption() {

    int inputChoose;
    printf("DriDB -- OPTIONS \n");
    printf("DriDB -- SHOW TABLES (1) \n");
    printf("DriDB -- CONNECT TABLE (2) \n");
    scanf("%d", &inputChoose);

    if (inputChoose == 1) {
        showTables();
    }

}


char *parseStringConnection(char stringConnection[]) {

    char *point = strrchr(stringConnection, '.');
    if (point != NULL) {
        *point = '\0';
        return stringConnection;
    }
    return NULL;

}


bool existDatabase(char stringConnection[]) {
    struct stat info;
    if (stat(parseStringConnection(stringConnection), &info) != 0) {
        return false;
    }
    return S_ISDIR(info.st_mode);

}

void connectDb(char stringConnection[]) {
    if (existDatabase(stringConnection)) {
        showDatabaseOption();
    } else {
        printf("DATABASE NOT FOUND \n");
    }
}

void showMenuDatabase() {
    
    int inputChoose;
    printf("DriDB - OPTIONS \n");
    printf("--------------------- \n");
    printf("DriDB - CONNECT DB (1) \n");
    printf("DriDB - DELETE DB (2) \n");
    printf("Exit (3) \n");
    scanf("%d", &inputChoose);

    if (inputChoose == 1) {
        char stringConnection[20];
        printf("ENTER WITH STRING CONNECTION \n");
        scanf("%s", stringConnection);
        connectDb(stringConnection);
    }

}
