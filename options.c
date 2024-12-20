#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

int projectStatus(char projectName[]) {
    char status[2];
    FILE *fptr = fopen(projectName, "r");

    fgets(status, 2, fptr);

    fclose(fptr);
    return atoi(status);
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

    char ch;
    fseek(fptr, 2, SEEK_SET);

    while ((ch = fgetc(fptr)) != EOF) {
        printf("%c", ch);
    }

    fclose(fptr);
    return 200;
}
