#ifndef OBJECT_H
#define OBJECT_H

struct object {
    const char *type; // blob/tree/commit
    void *util;
    struct object *next;
};

/*
struct object_list {
    struct object *item;
    struct object_list *next;
};
*/

struct blob {
    char *file_path;
    int hash_value;
};

struct tree_entry_list {
    struct tree_entry_list *next;
    union {
        struct tree *tree;
        struct blob *blob;
    } item;
    struct tree_entry_list *parent;
};

struct tree {
    struct tree_entry_list *entries;
};

struct commit {
    struct commit *parents;
    struct tree *tree;

    char *commit_id[10];
    char *author;
    char *committer;
    char *changelog;
};

struct blob create_blob (void *helper, char* file_path);

#endif //OBJECT_H
