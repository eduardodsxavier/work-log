#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "getInfo.c"

int startProject() {
    char fileName[20];
    if (dirExist()) {
        mkdir(".workLog", 0700);
    }

    giveFileName("logs", fileName);
    FILE *fptrLogs = fopen(fileName, "r+");
    if (fptrLogs == NULL) { 
        fptrLogs = fopen(fileName, "w");
    }

    giveFileName("stats", fileName);
    FILE *fptrStats = fopen(fileName, "r+");
    if (fptrStats == NULL) { 
        fptrStats = fopen(fileName, "w");
        fprintf(fptrStats, "0");
    }
    fclose(fptrStats);

    giveFileName("count", fileName);
    FILE *fptrCount = fopen(fileName, "r+");
    if (fptrCount == NULL) { 
        fptrCount = fopen(fileName, "w");
        fprintf(fptrCount, "0");
    }
    fclose(fptrCount);

    if (projectStatus()) {
        printf("must stop timer of project before start it again.");
        return 500;
    }

    changeProjectStatus();
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fseek(fptrLogs, 0, SEEK_END);
    fprintf(fptrLogs, " %02d-%02d-%02d:%lu", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, time(NULL));
    fclose(fptrLogs);
    return 200;
}

int stopProject() {
    char fileName[20];
    if (dirExist()) {
        printf("cannot find directory '.workLog'.");
        return 404;
    }

    giveFileName("logs", fileName);
    FILE *fptrLogs = fopen(fileName, "r+");


    if (!projectStatus()) {
        printf("must start time of the project before stop it.");
        return 500;
    }

    changeProjectStatus();

    int count = getProjectCount();

    giveFileName("count", fileName);

    FILE *fptrCount = fopen(fileName, "w");

    fprintf(fptrCount, "%d", count + 1);

    fseek(fptrLogs, 0, SEEK_END);
    fprintf(fptrLogs, "-%lu\n", time(NULL));

    fclose(fptrLogs);
    fclose(fptrCount);
    return 200;
}

int projectLog() {
    char fileName[20];
    if (dirExist()) {
        printf("cannot find directory '.workLog'");
        return 404;
    }

    giveFileName("logs", fileName);
    FILE *fptrLogs = fopen(fileName, "r+");

    if (projectStatus()) {
        printf("must stop timer of the project before see the project log.");
        return 500;
    }

    char startTime[11];
    char endTime[11];
    char date[12];
    int count = getProjectCount();
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
