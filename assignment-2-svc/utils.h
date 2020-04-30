#ifndef util_h
#define util_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void ensureWriteFile(char *path, char *content){
    FILE *fp;
    fp = fopen(path, "w+");
    fputs(content, fp);
    fclose(fp);
}
void ensureMkdir(const char *path) {
    struct stat st = {0};

    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

const char *svcDir= ".svc";

void initSVCDir(){
    char dst[strlen(svcDir) + 100];
    strcpy(dst, svcDir);
    ensureMkdir(svcDir);

    strcat(dst, "/HEAD");
    ensureWriteFile(dst, "refs/heads/master");
}

#endif

