#include"file_system.h"
#include<stdio.h>

#define MAX_OPEN_FILES 15
#define MAX_FILES 100

extern UArea UA;
extern SuperBlock SB;
extern Inode DILB[MAX_FILES];
extern FileTable FT[MAX_OPEN_FILES];
extern DIR AllDir[NO_OF_DIR];
extern int getInodeNumberFromDirectory();

void statistics(char *fileName)
{
	int inodeNumber;
	inodeNumber = getInodeNumberFromDirectory(fileName);
	if(inodeNumber== -1)
	{
		printf("\n\tInvalid file name specified\n");
		return ;	
	}
	
	printf("\n\t**********Statistics of inode******* \n\n\n");
	printf("\tType : %d\n\n",DILB[inodeNumber].type);
	printf("\tSize : %d\n\n",DILB[inodeNumber].file_size);
	printf("\tLast modified : %s\n",ctime(&(DILB[inodeNumber].last_modified)));
	printf("\tLast accessed : %s\n",ctime(&(DILB[inodeNumber].last_accessed)));
	printf("\tInode modifed : %s\n",ctime(&(DILB[inodeNumber].inode_modified)));
}
