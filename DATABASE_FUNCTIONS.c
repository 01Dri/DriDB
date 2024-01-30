
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "DATABASE_FUNCTIONS.h"

void showTables(const char *stringConnection) {

    DIR *dir;
    struct dirent *ent;
    dir = opendir(stringConnection);
    if (dir != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            printf("%s\n", ent->d_name);
        }
        closedir(dir);
    } else {
        printf("Nenhuma tabela foi encontrada");
    }
}

void showValues(const char *stringConnection) {
    FILE *arquivo = fopen(stringConnection, "r");
    char linha[100]; 
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }
    fclose(arquivo);
}

void openTable(const char *stringConnection) {
    FILE *arquivo = fopen(stringConnection, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    int inputChoose;
    printf("DRIDB --- \n");
    printf("DRIDB INSERT VALUE (1)\n");
    printf("DRIDB SHOW VALUES  (2)\n");
    printf("DRIDB --- \n");
    scanf("%d", &inputChoose);
     if (inputChoose == 1) {
        return;
    }
    showValues(stringConnection);

}


void showDatabaseOption(char stringConnection[]) {

    int inputChoose;
    char tableFile[20];
    printf("DriDB -- OPTIONS \n");
    printf("DriDB -- SHOW TABLES (1) \n");
    printf("DriDB -- CONNECT TABLE (2) \n");
    scanf("%d", &inputChoose);

    if (inputChoose == 1) {
        showTables(stringConnection);
        return;
    }
    printf("ENTER WITH TABLE NAME: \n");
    scanf("%19s", tableFile);
    
    sprintf(stringConnection, "%s/%s", stringConnection, tableFile);
    printf("%s\n", stringConnection);
    openTable(stringConnection);
}

char *parseStringConnection(char stringConnection[]) {

    char *point = strrchr(stringConnection, '.'); // FOLDER PATH HERE 
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
        showDatabaseOption(stringConnection);
    } else {
        printf("DATABASE NOT FOUND \n");
    }
}

void startDb() {
    
    int inputChoose;
    printf("DriDB - OPTIONS \n");
    printf("--------------------- \n");
    printf("DriDB - CONNECT DB (1) \n");
    printf("DriDB - DELETE DB (2) \n");
    printf("Exit (3) \n");
    scanf("%d", &inputChoose);

    if (inputChoose == 1) {
        char stringConnection[255];
        printf("ENTER WITH STRING CONNECTION \n");
        scanf("%254s", stringConnection);
        connectDb(stringConnection);
    }

}
