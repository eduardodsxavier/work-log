#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

struct stat st = {0};

void giveFileName(char type[], char fileName[]) {
    strcpy(fileName, ".workLog");
    strcat(fileName, "/");
    strcat(fileName, type);
}

int dirExist() {
    return stat(".workLog", &st) == -1;
}

int projectStatus() {
    char fileName[20];
    giveFileName("stats", fileName);
    char status;
    FILE *fptr = fopen(fileName, "r");

    status = fgetc(fptr);

    fclose(fptr);
    return status - '0';
}

void changeProjectStatus() {
    char fileName[20];
    giveFileName("stats", fileName);

    char stats = projectStatus();
    FILE *fptr = fopen(fileName, "w");

    if (stats) {
        fprintf(fptr, "0");       
    }
    else {
        fprintf(fptr, "1");       
    }
    fclose(fptr);
    return;
}

int getProjectCount() {
    char fileName[20];
    giveFileName("count", fileName);

    FILE *fptr = fopen(fileName, "r+");

    fseek (fptr, 0, SEEK_END);
    int length = ftell (fptr);
    fseek (fptr, 0, SEEK_SET);
    char *count = malloc (length);
    fread (count, 1, length, fptr);

    return atoi(count);
}
