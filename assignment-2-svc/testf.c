#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

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

int main(void)
{

	printf("%d\n",hash_file(NULL,"hello.py"));
	printf("%d\n",hash_file(NULL,"task.c"));
	printf("%d\n",hash_file(NULL,"sample.txt"));


	return 0;
}
