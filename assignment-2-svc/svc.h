#ifndef svc_h
#define svc_h

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
typedef struct resolution{
    char *file_name;
    char *resolved_file;
} resolution;

void *svc_init(void)
{
	void* helper = (resolution*)malloc(sizeof(resolution));
	return helper;
}

void cleanup(void *helper)
{	

	free(helper);
}

int hash_file(void *helper, char *file_path)
{  
	if(file_path == NULL)
		return -1;
	
	if(access(file_path,F_OK) == -1)
		return -2;

//if the file can't read what to do?
	char *file_contents = NULL;
	FILE *fp = NULL;
	if((fp = fopen(file_path,"r")) != NULL)
	{
		fseek(fp,0,SEEK_END);
		size_t file_length = ftell(fp);
		file_contents = (char*)malloc((file_length+1)*sizeof(char));
		rewind(fp);
		file_length = fread(file_contents,1,file_length,fp);
		file_contents[file_length] = '\0';
		fclose(fp);

		int hash = 0;
		size_t i;
		for(i=0;i<strlen(file_path);i++)
			hash = (hash+file_path[i]) %1000;
		
		for(i=0;i<file_length;i++)
			hash = (hash + file_contents[i]) % 2000000000;
	
		return hash;
	}
}
char *svc_commit(void *helper, char *message)
{
	if(message == NULL)
		return NULL;
	//if no change
	//
}
void *get_commit(void *helper, char *commit_id);

char **get_prev_commits(void *helper, void *commit, int *n_prev);

void print_commit(void *helper, char *commit_id);

int svc_branch(void *helper, char *branch_name);

int svc_checkout(void *helper, char *branch_name);

char **list_branches(void *helper, int *n_branches);

int svc_add(void *helper, char *file_name)
{
	if(file_name ==NULL)
		return -1;
	//如果已被记录则返回-2；
	if(access(file_name,F_OK)==-1)
		return -3;
	
	//否则将该文件添加到SVCX系统中。返回哈希值
	return hash_file(helper,file_name);
}

int svc_rm(void *helper, char *file_name);

int svc_reset(void *helper, char *commit_id);

char *svc_merge(void *helper, char *branch_name, resolution *resolutions, int n_resolutions);

#endif

