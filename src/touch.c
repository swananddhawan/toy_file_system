#include"file_system.h"
#include<stdio.h>

extern UArea UA;
extern SuperBlock SB;
extern Inode DILB[];
extern FileTable FT[];
extern DIR AllDir[];
extern int remember_inode_number;

extern int getInodeNumberFromDirectory();


int touch_0(char *fileName)
{
	int inodeNumber = getInodeNumberFromDirectory(fileName);
	if(inodeNumber == -1)
	{
		printf("\n\tInvalid file name specified\n");
		return -1;	
	}
		DILB[inodeNumber].last_modified = time(NULL);
		DILB[inodeNumber].last_accessed = time(NULL);
		DILB[inodeNumber].inode_modified = time(NULL);
	return 0;		
}
int touch_1(char *fileName, char *mode)
{
	int inodeNumber = getInodeNumberFromDirectory(fileName);
	if(inodeNumber == -1)
	{
		printf("\n\tInvalid file name specified\n");
		return -1;	
	}
	
	if(*mode=='a')
	{
		DILB[inodeNumber].last_accessed = time(NULL);
		DILB[inodeNumber].inode_modified = time(NULL);
	}
	
	if(*mode=='m')
	{
		DILB[inodeNumber].last_accessed = time(NULL);
		DILB[inodeNumber].inode_modified = time(NULL);
	}
	return 0;		
}
