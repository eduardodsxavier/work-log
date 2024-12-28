#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "getInfo.c"

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
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fseek(fptr, 0, SEEK_END);
    fprintf(fptr, " %d-%02d-%02d:%lu", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, time(NULL));
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
    char date[12];
    int count = getProjectCount(projectName);
    int totalTime = 0;

    for (int i = 0; i < count; i++) {
        fgets(date, 12, fptr);
        fgetc(fptr);
        fgets(startTime, 11, fptr);
        fgetc(fptr);
        fgets(endTime, 11, fptr);
        fgetc(fptr);
        int time = (atoi(endTime) - atoi(startTime));
        printf("log%s: %d min.\n", date, time / 60);
        totalTime += time;
    }

    printf("total time of project: %dmin.", totalTime / 60);

    fclose(fptr);
    return 200;
}
