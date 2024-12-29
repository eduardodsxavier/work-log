#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "getInfo.c"

struct stat st = {0};

int startProject(char projectName[]) {
    char fileName[20];
    if (stat(projectName, &st) == -1) {
        mkdir(projectName, 0700);
    }

    giveFileName(projectName, "logs", fileName);
    FILE *fptrLogs = fopen(fileName, "r+");
    if (fptrLogs == NULL) { 
        fptrLogs = fopen(fileName, "w");
    }

    giveFileName(projectName, "stats", fileName);
    FILE *fptrStats = fopen(fileName, "r+");
    if (fptrStats == NULL) { 
        fptrStats = fopen(fileName, "w");
        fprintf(fptrStats, "0");
    }
    fclose(fptrStats);

    giveFileName(projectName, "count", fileName);
    FILE *fptrCount = fopen(fileName, "r+");
    if (fptrCount == NULL) { 
        fptrCount = fopen(fileName, "w");
        fprintf(fptrCount, "0");
    }
    fclose(fptrCount);

    if (projectStatus(projectName)) {
        printf("must stop timer of %s before start it again.", projectName);
        return 500;
    }

    changeProjectStatus(projectName);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fseek(fptrLogs, 0, SEEK_END);
    fprintf(fptrLogs, " %d-%02d-%02d:%lu", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, time(NULL));
    fclose(fptrLogs);
    return 200;
}

int stopProject(char projectName[]) {
    char fileName[20];
    if (stat(projectName, &st) == -1) {
        printf("cannot find project: '%s'.", projectName);
        return 404;
    }

    giveFileName(projectName, "logs", fileName);
    FILE *fptrLogs = fopen(fileName, "r+");


    if (!projectStatus(projectName)) {
        printf("must start time of %s before stop it.", projectName);
        return 500;
    }

    changeProjectStatus(projectName);

    int count = getProjectCount(projectName);

    giveFileName(projectName, "count", fileName);

    FILE *fptrCount = fopen(fileName, "w");

    fprintf(fptrCount, "%d", count + 1);

    fseek(fptrLogs, 0, SEEK_END);
    fprintf(fptrLogs, "-%lu\n", time(NULL));

    fclose(fptrLogs);
    fclose(fptrCount);
    return 200;
}

int projectLog(char projectName[]) {
    char fileName[20];
    if (stat(projectName, &st) == -1) {
        printf("cannot find project: '%s'.", projectName);
        return 404;
    }

    giveFileName(projectName, "logs", fileName);
    FILE *fptrLogs = fopen(fileName, "r+");

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
        fgets(date, 12, fptrLogs);
        fgetc(fptrLogs);
        fgets(startTime, 11, fptrLogs);
        fgetc(fptrLogs);
        fgets(endTime, 11, fptrLogs);
        fgetc(fptrLogs);
        int time = (atoi(endTime) - atoi(startTime));
        printf("log%s: %d min.\n", date, time / 60);
        totalTime += time;
    }

    printf("total time on project: %dmin.", totalTime / 60);

    fclose(fptrLogs);
    return 200;
}
