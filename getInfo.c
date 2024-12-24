#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void giveFileName(char projectName[], char type[], char copy[]) {
    strcpy(copy, projectName);
    strcat(copy, type);
}

int projectStatus(char projectName[]) {
    char copy[20];
    giveFileName(projectName, "Stats", copy);
    char status;
    FILE *fptr = fopen(copy, "r");

    status = fgetc(fptr);

    fclose(fptr);
    return status - '0';
}

void changeProjectStatus(char projectName[]) {
    char copy[20];
    giveFileName(projectName, "Stats", copy);

    char stats = projectStatus(projectName);
    FILE *fptr = fopen(copy, "w");

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
    char copy[20];
    giveFileName(projectName, "Count", copy);

    FILE *fptr = fopen(copy, "r+");

    fseek (fptr, 0, SEEK_END);
    int length = ftell (fptr);
    fseek (fptr, 0, SEEK_SET);
    char *count = malloc (length);
    fread (count, 1, length, fptr);

    return atoi(count);
}
