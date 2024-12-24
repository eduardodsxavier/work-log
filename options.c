#include <stdlib.h>
#include <time.h>
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

int startProject(char projectName[]) {
    FILE *fptr = fopen(projectName, "r+");

    char copy[20];
    giveFileName(projectName, "Stats", copy);

    FILE *fptrStats = fopen(copy, "r+");

    if (fptrStats == NULL) { 
        fptrStats = fopen(copy, "w");
        fprintf(fptrStats, "0");
    }
    fclose(fptrStats);

    giveFileName(projectName, "Count", copy);

    FILE *fptrCount = fopen(copy, "r+");

    if (fptrCount == NULL) { 
        fptrCount = fopen(copy, "w");
        fprintf(fptrCount, "0");
    }
    fclose(fptrCount);

    if (fptr == NULL) { 
        fptr = fopen(projectName, "w");
    }

    if (projectStatus(projectName)) {
        printf("must stop timer of %s before start it again.", projectName);
        return 500;
    }

    changeProjectStatus(projectName);
    fseek(fptr, 0, SEEK_END);
    fprintf(fptr, "%lu", time(NULL));

    fclose(fptr);
    return 200;
}

int stopProject(char projectName[]) {
    FILE *fptr = fopen(projectName, "r+");

    if (fptr == NULL) { 
        printf("cannot find file: '%s'.", projectName);
        return 404;
    }

    if (!projectStatus(projectName)) {
        printf("must start time of %s before stop it.", projectName);
        return 500;
    }

    changeProjectStatus(projectName);

    int count = getProjectCount(projectName);

    char copy[20];
    giveFileName(projectName, "Count", copy);

    FILE *fptrCount = fopen(copy, "w");

    fprintf(fptrCount, "%d", count + 1);

    fseek(fptr, 0, SEEK_END);
    fprintf(fptr, "-%lu\n", time(NULL));

    fclose(fptr);
    return 200;
}

int projectLog(char projectName[]) {
    FILE *fptr = fopen(projectName, "r");

    if (NULL == fptr) {
        printf("cannot find file: '%s'.", projectName);
        return 404;
    }

    if (projectStatus(projectName)) {
        printf("must stop timer of %s before see the project log.", projectName);
        return 500;
    }

    char startTime[11];
    char endTime[11];
    int count = getProjectCount(projectName);

    for (int i = 0; i < count; i++) {
        fgets(startTime, 11, fptr);
        fgetc(fptr);
        fgets(endTime, 11, fptr);
        fgetc(fptr);
        printf("log%d: %d min\n", i,  (atoi(endTime) - atoi(startTime)) / 60);
    }

    fclose(fptr);
    return 200;
}
