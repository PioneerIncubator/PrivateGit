#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void *svc_init(void) {
    // TODO: Implement
    void* helper;
    return NULL;
}

void cleanup(void *helper) {
    // TODO: Implement
}

int hash_file(void *helper, char *file_path) {
    if (file_path == NULL) 
        return -1;
    
    if (access(file_path, F_OK) == -1) 
        // check for file existence 
        return -2;
   
//if the file can't read what to do?
    char *file_contents = NULL;
    FILE *fp = NULL;
    if( (fp = fopen(file_path,"r")) != NULL)
	{
  	 fseek(fp,0,SEEK_END);
    	 long file_length = ftell(fp);
    	 file_contents = (char*)malloc((file_length + 1) * sizeof(char));
	 rewind(fp);
   	 file_length = fread(file_contents, 1, file_length, fp);
     	 file_contents[file_length] = '\0';
    	 fclose(fp);

    	 int hash = 0;
    	 for (int i = 0; i < strlen(file_path); i++)
       	 {
       	  hash = (hash + file_path[i]) % 1000;
    	 }
    	 for (int i = 0; i < file_length; i++)
	 {
          hash = (hash + file_contents[i]) % 2000000000;
    	 }

   	 return hash;
	}
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

