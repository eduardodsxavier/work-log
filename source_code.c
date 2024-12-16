#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int startProject(char projectName[]);
int stopProject(char projectName[]);
int projectLog(char projectName[]);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("program must have at least 2 parameter");
        return 1;
    }
    if (strcmp(argv[1], "start") == 0) {
        startProject(argv[2]);
        return 0;
    }
    if (strcmp(argv[1], "stop") == 0) {
        stopProject(argv[2]);
        return 0;
    }
    if (strcmp(argv[1], "log") == 0) {
        projectLog(argv[2]);
        return 0;
    }

    printf("argv '%s' ins't a option", argv[1]);
    return 2;
}

int startProject(char projectName[]) {
    time_t seconds = time(NULL);
    char str[11];
    char file[15];

    sprintf(file, "%s.txt", projectName);
    FILE *fptr = fopen(file, "a");

    fprintf(fptr, "%lu", seconds);

    printf("start timer for %s\n", projectName);
    fclose(fptr);
    return 0;
}

int stopProject(char projectName[]) {
    time_t seconds = time(NULL);
    char startTime[11];
    char file[15];
    sprintf(file, "%s.txt", projectName);

    FILE *fptr = fopen(file, "a+");

    if (fptr == NULL) { 
        printf("cannot open file: '%s'", file);
        return 3;
    }

    fgets(startTime, 11, fptr);
    long numericStartTime = atoi(startTime);

    printf("stop timer for %s\n", projectName);
    printf("project time: %lu min\n", (seconds - numericStartTime) / 60);

    fprintf(fptr, " - %lu\n", seconds);

    fclose(fptr);
    return 0;
}

int projectLog(char projectName[]) {
    printf("show log for %s", projectName);
    return 0;
}
