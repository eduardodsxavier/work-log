#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void giveFileName(char projectName[], char type[], char fileName[]) {
    strcpy(fileName, projectName);
    strcat(fileName, "/");
    strcat(fileName, type);
}

int projectStatus(char projectName[]) {
    char fileName[20];
    giveFileName(projectName, "stats", fileName);
    char status;
    FILE *fptr = fopen(fileName, "r");

    status = fgetc(fptr);

    fclose(fptr);
    return status - '0';
}

void changeProjectStatus(char projectName[]) {
    char fileName[20];
    giveFileName(projectName, "stats", fileName);

    char stats = projectStatus(projectName);
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

int getProjectCount(char projectName[]) {
    char fileName[20];
    giveFileName(projectName, "count", fileName);

    FILE *fptr = fopen(fileName, "r+");

    fseek (fptr, 0, SEEK_END);
    int length = ftell (fptr);
    fseek (fptr, 0, SEEK_SET);
    char *count = malloc (length);
    fread (count, 1, length, fptr);

    return atoi(count);
}
