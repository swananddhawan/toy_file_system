#include<time.h>
#include<stdio.h>
#include"file_system.h"

/*extern UArea UA;*/
/*extern SuperBlock SB;*/
/*extern Inode DILB[];*/
/*extern FileTable FT[];*/
/*extern DIR AllDir[];*/
/*extern DirMapEntry DirMap[];*/

/*extern void insertFileInDir();*/
/*extern int makeEntryInFT();*/
/*extern int putFTAddIntoUFDT();*/
/*extern Bool isUFDTFull();*/
/*extern int ialloc();*/

int create(char *fileName)
{
	int fd,inodeNumber, FTAdd=0;
	inodeNumber=ialloc() ;
	DILB[inodeNumber].type=RegularFile;
	DILB[inodeNumber].last_modified=time(NULL);
	DILB[inodeNumber].last_accessed=time(NULL);
	DILB[inodeNumber].inode_modified=time(NULL);
	
	insertFileInDir(inodeNumber, fileName);
	
		
	FTAdd = makeEntryInFT(inodeNumber, 1);
	
	if(isUFDTFull())
	{
			printf("\nSorry no free space is available\n");
			return (-1);
	}
	fd=putFTAddIntoUFDT(FTAdd);	
	return(fd);	
	
}
