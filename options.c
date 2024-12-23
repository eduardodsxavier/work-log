#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

int projectStatus(char projectName[]) {
    char copy[20];
    strcpy(copy, projectName);
    strcat(copy, "Stats");
    char status;
    FILE *fptr = fopen(copy, "r");

    status = fgetc(fptr);

    fclose(fptr);
    return status - '0';
}

void changeProjectStatus(char projectName[]) {
    char copy[20];
    char stats = projectStatus(projectName);

    strcpy(copy, projectName);
    strcat(copy, "Stats");
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

int startProject(char projectName[]) {
    FILE *fptr = fopen(projectName, "r+");

    char copy[20];
    strcpy(copy, projectName);
    strcat(copy, "Stats");
    FILE *fptrStats = fopen(copy, "r+");

    if (fptrStats == NULL) { 
        fptrStats = fopen(copy, "w");
        fprintf(fptrStats, "0");
    }
    fclose(fptrStats);

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

    fseek(fptr, 2, SEEK_SET);

    char startTime[11];
    char endTime[11];
        
    fgets(startTime, 11, fptr);
    fgetc(fptr);
    fgets(endTime, 11, fptr);
    printf("%d min", (atoi(endTime) - atoi(startTime)) / 60);

    fclose(fptr);
    return 200;
}
