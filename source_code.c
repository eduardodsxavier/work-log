#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void startProject(char projectName[]);
void stopProject(char projectName[]);
void projectLog(char projectName[]);

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

void startProject(char projectName[]) {
    time_t seconds = time(NULL);
    char str[11];
    FILE *fptr = fopen("project.txt", "w");

    fprintf(fptr, "%lu", seconds);

    printf("start timer for %s\n", projectName);
    fclose(fptr);
    return;
}

void stopProject(char projectName[]) {
    time_t seconds = time(NULL);
    char startTime[11];
    FILE *fptr = fopen("project.txt", "r");

    fgets(startTime, 11, fptr);
    long numericStartTime = atoi(startTime);

    printf("stop timer for %s\n", projectName);
    printf("project time: %lu min\n", (seconds - numericStartTime) / 60);
    fclose(fptr);
    return;
}

void projectLog(char projectName[]) {
    printf("show log for %s", projectName);
    return;
}
