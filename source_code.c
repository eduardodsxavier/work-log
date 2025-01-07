#include <stdio.h>
#include <string.h>

#include "options.c"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("program must have 2 parameters");
        return 400;
    }
    if (strcmp(argv[1], "start") == 0) {
        return startProject(); 
    }
    if (strcmp(argv[1], "stop") == 0) {
        return stopProject();
    }
    if (strcmp(argv[1], "log") == 0) {
        return projectLog(); 
    }

    printf("'%s' ins't a option", argv[1]);
    return 404;
}
