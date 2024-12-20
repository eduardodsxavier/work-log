#include <stdio.h>
#include <string.h>

#include "options.c"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("program must have 2 parameters");
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

    printf("'%s' ins't a option", argv[1]);
    return 404;
}
