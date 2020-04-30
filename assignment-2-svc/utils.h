#ifndef util_h
#define util_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

const char *svcDir= ".svc";

void ensure_write_file(char *path, char *content);
void ensure_mkdir(const char *path);
void init_svc_dir();

void ensure_write_file(char *path, char *content){
    FILE *fp;
    fp = fopen(path, "w+");
    fputs(content, fp);
    fclose(fp);
}

void ensure_mkdir(const char *path) {
    struct stat st = {0};

    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}


void init_svc_dir(){
    ensure_mkdir(svcDir);

    char obj_dir[strlen(svcDir) + 100];
    strcpy(obj_dir, svcDir);
    strcat(obj_dir, "/objects");
    ensure_mkdir(obj_dir);

    char head_dir[strlen(svcDir) + 100];
    strcpy(head_dir, svcDir);
    strcat(head_dir, "/HEAD");
    ensure_write_file(head_dir, "refs/heads/master");
}

#endif

