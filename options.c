#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

int projectStatus(char projectName[]) {
    char status;
    FILE *fptr = fopen(projectName, "r");

    status = fgetc(fptr);

    fclose(fptr);
    return status - '0';
}

int startProject(char projectName[]) {
    FILE *fptr = fopen(projectName, "r+");

    if (fptr == NULL) { 
        fptr = fopen(projectName, "w");
    }

    if (projectStatus(projectName)) {
        printf("must stop timer of %s before start it again.", projectName);
        return 500;
    }

    fprintf(fptr, "1");
    fseek(fptr, 0, SEEK_END);
    fprintf(fptr, "\n%lu", time(NULL));

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

    fprintf(fptr, "0");
    fseek(fptr, 0, SEEK_END);
    fprintf(fptr, "-%lu", time(NULL));

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
    printf("%d", (atoi(endTime) - atoi(startTime)));

    fclose(fptr);
    return 200;
}
