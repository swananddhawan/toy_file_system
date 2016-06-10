#include "file_system.h"
#include <stdio.h>

int append(int fd)
{
	int FTentry,inodeNumber,noOfBytes;
	char temp[1024], flush[2];
	fd = checkFD(fd);
	if(fd == -1)
		return -1;
	FTentry=UA.UFDT[fd];
	printf("Enter what you want to write in the file :\n");
	scanf("%[\nA-Za-z0-9 .,\\\"\'_+?/!@#$%&*()_+;]", temp);
	scanf("%s",flush);
	inodeNumber=(FT[FTentry].inode_number);
	noOfBytes = appendDataInFile(inodeNumber, temp);
	if(noOfBytes==-1)
	{
		printf("\n Unable to write  data in file \n");
		return (-1);
	}
	DILB[inodeNumber].last_modified=time(NULL);
	DILB[inodeNumber].last_accessed=time(NULL);
	DILB[inodeNumber].inode_modified=time(NULL);
		
	return (noOfBytes);

}
