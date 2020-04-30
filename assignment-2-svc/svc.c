#include "svc.h"

void *svc_init(void) {
    void *helper = malloc(sizeof(struct helper));
    return helper;
}

void cleanup(void *helper) {
    // TODO: Implement
}

int hash_file(void *helper, char *file_path) {
    if (file_path == NULL) {
        printf("ERROR: file_path is NULL");
        return FILE_PATH_ERROR;
    }
    if (access(file_path, 0) == -1) {
        // check for file existence
        printf("ERROR: %s does not exist", file_path);
        return FILE_EXIST_ERROR;
    }
    if (access(file_path, 4) == -1) {
        // check for file read permission
        printf("ERROR: can't read %s", file_path);
        return FILE_OPEN_ERROR;
    }

    char *file_contents = NULL;
    FILE *fp = NULL;
    fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("ERROR: fopen can't open %s", file_path);
        return FILE_PATH_ERROR;
    }

    fseek(fp, 0, SEEK_END);
    int file_length = ftell(fp);
    file_contents = (char *) malloc((file_length + 1) * sizeof(char));
    rewind(fp);
    file_length = fread(file_contents, 1, file_length, fp);
    file_contents[file_length] = '\0';
    fclose(fp);

    int hash = 0;
    for (int i = 0; i < strlen(file_path); i++) {
        hash = (hash + file_path[i]) % 1000;
    }
    for (int i = 0; i < file_length; i++) {
        hash = (hash + file_contents[i]) % 2000000000;
    }

    return hash;
}

char *svc_commit(void *helper, char *message) {
    // TODO: Implement
    return NULL;
}

void *get_commit(void *helper, char *commit_id) {
    // TODO: Implement
    return NULL;
}

char **get_prev_commits(void *helper, void *commit, int *n_prev) {
    // TODO: Implement
    return NULL;
}

void print_commit(void *helper, char *commit_id) {
    // TODO: Implement
}

int svc_branch(void *helper, char *branch_name) {
    // TODO: Implement
    return 0;
}

int svc_checkout(void *helper, char *branch_name) {
    // TODO: Implement
    return 0;
}

char **list_branches(void *helper, int *n_branches) {
    // TODO: Implement
    return NULL;
}

int svc_add(void *helper, char *file_name) {
    // TODO: Implement
    return 0;
}

int svc_rm(void *helper, char *file_name) {
    // TODO: Implement
    return 0;
}

int svc_reset(void *helper, char *commit_id) {
    // TODO: Implement
    return 0;
}

char *svc_merge(void *helper, char *branch_name, struct resolution *resolutions, int n_resolutions) {
    // TODO: Implement
    return NULL;
}

