#ifndef util_h
#define util_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

const char *svc_dir= ".svc";

void ensure_write_file(char *path, char *content);
void ensure_mkdir(const char* to, const char* path);
void init_svc_dir();

void ensure_write_file(char *path, char *content){
    FILE *fp;
    fp = fopen(path, "w+");
    fputs(content, fp);
    fclose(fp);
}

void ensure_mkdir(const char* to, const char* path) {
    char target_dir[strlen(to) + 100];
    strcpy(target_dir, to);
    strcat(target_dir, path);

    struct stat st = {0};

    if (stat(target_dir, &st) == -1) {
        printf("mkdir on %s\n", target_dir);
        mkdir(target_dir, 0700);
    }
}


void init_svc_dir(){
    ensure_mkdir(svc_dir, "");

    ensure_mkdir(svc_dir, "/objects");
    ensure_mkdir(svc_dir, "/refs");
    ensure_mkdir(svc_dir, "/refs/heads");
    ensure_mkdir(svc_dir, "/refs/tags");

    char target_dir[strlen(svc_dir) + 100];
    strcpy(target_dir, svc_dir);
    strcat(target_dir, "/HEAD");
    ensure_write_file(target_dir, "refs/heads/master");
}

#endif

