#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int startProject(char projectName[]);
int stopProject(char projectName[]);
int projectLog(char projectName[]);
int projectStatus(char projectName[]);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("program must have at least 2 parameter");
        return 400;
    }
    if (strcmp(argv[1], "start") == 0) {
        return startProject(argv[2]); 
    }
    if (strcmp(argv[1], "stop") == 0) {
        return stopProject(argv[2]);
    }
    if (strcmp(argv[1], "log") == 0) {
        return projectLog(argv[2]); 
    }

    printf("argv '%s' ins't a option", argv[1]);
    return 404;
}

int startProject(char projectName[]) {
    FILE *fptr = fopen(projectName, "r+");

    if (fptr == NULL) { 
        fptr = fopen(projectName, "w");
    }

    if (projectStatus(projectName)) {
        printf("timer of %s is alread in use", projectName);
        return 500;
    }

    fprintf(fptr, "1");

    fclose(fptr);
    return 200;
}

int stopProject(char projectName[]) {
    FILE *fptr = fopen(projectName, "r+");

    if (fptr == NULL) { 
        printf("cannot open file: '%s'", projectName);
        return 404;
    }

    if (!projectStatus(projectName)) {
        printf("timer of %s is not in use", projectName);
        return 500;
    }

    fprintf(fptr, "0");
    fclose(fptr);
    return 200;
}

int projectLog(char projectName[]) {
    printf("show log for %s", projectName);
    return 200;
}

int projectStatus(char projectName[]) {
    char status[2];

    FILE *fptr = fopen(projectName, "r");
    fgets(status, 2, fptr);
    fclose(fptr);

    return atoi(status);
}
