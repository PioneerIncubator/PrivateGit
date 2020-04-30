#include "svc.h"
#include "utils.h"


void *svc_init(void) {
    init_svc_dir();
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
    int hash_value = hash_file(helper, file_name);
    if (hash_value < 0) {
        printf("ERROR: hash_file error in svc_add");
        return hash_value;
    }
    struct helper *tmp_helper = (struct helper *) helper;

    struct cache *new_cache = (struct cache *) malloc(sizeof(struct cache));
    char *buffer = (char*)malloc(strlen(file_name) * sizeof(char));
    strcpy(buffer, file_name);
    new_cache->name = buffer;

    if (tmp_helper->cache_num == 0) {
        tmp_helper->cache_num++;
        tmp_helper->cache_array = malloc(tmp_helper->cache_num * sizeof(struct cache));
        tmp_helper->cache_array[0] = new_cache;
    } else if (tmp_helper->cache_num == 1){
        int cmp = strcmp(tmp_helper->cache_array[0]->name, new_cache->name);
        if (cmp == 0) {
            tmp_helper->cache_array = realloc(tmp_helper->cache_array, tmp_helper->cache_num * (sizeof(struct cache) + 1));
            tmp_helper->cache_array[1] = new_cache;
        }
    } else {
        int i = 1;
        for (; i < tmp_helper->cache_num; i++) {
            int prev_cmp = strcmp(tmp_helper->cache_array[i - 1]->name, new_cache->name);
            int cur_cmp = strcmp(tmp_helper->cache_array[i]->name, new_cache->name);
            if (prev_cmp == 0) {
                break;
            }
            if (prev_cmp < 0 && cur_cmp > 0) {
                break;
            }
        }
        tmp_helper->cache_array = realloc(tmp_helper->cache_array, tmp_helper->cache_num * (sizeof(struct cache) + 1));
        memmove(tmp_helper->cache_array[i + 1], tmp_helper->cache_array[i], (tmp_helper->cache_num - i + 1) * sizeof(struct cache));
        tmp_helper->cache_array[i] = new_cache;
    }

    return hash_value;
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

struct blob create_blob(void *helper, char *file_path) {
    struct blob b;
    int hash_value = hash_file(helper, file_path);
    if (hash_value < 0) {
        printf("ERROR: get hash_value error, ErrorNumber is %d", hash_value);
        return b;
    }
    b.file_path = (char *) malloc(strlen(file_path) * sizeof(char));
    b.hash_value = hash_value;
    return b;
}


int main(){
    svc_init();
    return 0;
}
