#ifndef svc_h
#define svc_h

#include "object.h"
#include "cache.h"

#include <stdlib.h>
#include <stdio.h>
#ifdef __APPLE__
        #include <sys/uio.h>
#else
        #include <sys/io.h>
#endif
enum ErrorNumber {
    FILE_PATH_ERROR = -1,       // file_path is NULL
    FILE_EXIST_ERROR = -2,      // no file exists
    FILE_OPEN_ERROR = -3,       // file can't open
    ALREADY_TRACKED_ERROR = -4, // file is already being tracked
};

typedef struct resolution {
    // NOTE: DO NOT MODIFY THIS STRUCT
    char *file_name;
    char *resolved_file;
} resolution;

struct helper {
    int cache_num;
    struct cache cache_array[100];
    struct object *object;
};

void *svc_init(void);

void cleanup(void *helper);

int hash_file(void *helper, char *file_path);

char *svc_commit(void *helper, char *message);

void *get_commit(void *helper, char *commit_id);

char **get_prev_commits(void *helper, void *commit, int *n_prev);

void print_commit(void *helper, char *commit_id);

int svc_branch(void *helper, char *branch_name);

int svc_checkout(void *helper, char *branch_name);

char **list_branches(void *helper, int *n_branches);

int svc_add(void *helper, char *file_name);

int svc_rm(void *helper, char *file_name);

int svc_reset(void *helper, char *commit_id);

char *svc_merge(void *helper, char *branch_name, resolution *resolutions, int n_resolutions);

#endif

