#ifndef OBJECT_H
#define OBJECT_H

struct object {
    int hash_value;
    char *commit_id[10];
    const char *type; // blob/tree/commit
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
    struct object object;
    struct tree_entry_list *entries;
};

struct commit {
    struct object object;
    struct commit *parents;
    struct tree *tree;
    char *buffer;
};

#endif //OBJECT_H
