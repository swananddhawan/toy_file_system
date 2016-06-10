#include"file_system.h"
#include<string.h>

#define NO_OF_FILES_IN_DIR 10

extern UArea UA;
extern SuperBlock SB;
extern Inode DILB[];
extern FileTable FT[];
extern DIR AllDir[];
extern int remember_inode_number;
extern int getDirEntry();

int reName(char * existingFileName, char * newFileName)
{
	int i;
	int dirEntry=getDirEntry(UA.current_working_directory);
		
	for(i=2; i<NO_OF_FILES_IN_DIR;i++)
	{
		if( strcmp(AllDir[dirEntry].file[i].file_name,existingFileName)==0)
		{
			memset(AllDir[dirEntry].file[i].file_name, '\0', 20);		
			strcpy(AllDir[dirEntry].file[i].file_name,newFileName);
			return 0;
		}
	}
	return (-1);	
}
