#include<stdio.h>
#include<string.h>
#include"file_system.h"

extern UArea UA;
extern SuperBlock SB;
extern Inode DILB[];
extern FileTable FT[];
extern DIR AllDir[];
extern int remember_inode_number;

extern int changeDirectory();
extern int getInodeNumberFromDirectory();
extern int checkInodeInFT();
extern int makeEntryInFT();
extern Bool isUFDTFull();
extern int putFTAddIntoUFDT();

int openFile(char *path,char *mode)
{
	char parameter [20][20], *ptr = NULL;	
	int i=0,cnt,j;
	int FTAdd,inodeNumber,fd;	
	
	ptr = strtok(path,"/");
	while( ptr )
	{
		strcpy(parameter[i++],ptr);
		ptr = strtok(NULL,"/");
	}
	i--;
	cnt=i;
	j=0;	
	while(i>0)
	{
		int st=changeDirectory(parameter[j++]);
		i--;
		if(st==-1)
			printf("\n No such directory found %s ", parameter[j-1]);
	}	
		
	if(i==0)
		inodeNumber = getInodeNumberFromDirectory(parameter[j]);
	else
		inodeNumber = getInodeNumberFromDirectory(parameter[cnt-1]);
	
	if(inodeNumber == -1)
	{
		printf("\n\tInvalid file name specified\n");
		return -1;	
	}
	inodeNumber = checkInodeInFT(inodeNumber);
	if(inodeNumber == -1)
	{
		printf("\n\tFile is already opened..!!\n");
		return -1;	
	}
	if(*mode == 'R')
		FTAdd = makeEntryInFT(inodeNumber, R);
	else
	if(*mode == 'W')
		FTAdd = makeEntryInFT(inodeNumber, W);
	else
	if(*mode == 'A')
		FTAdd = makeEntryInFT(inodeNumber, A);
	else
	{
		printf("\n\tInvalid mode specified..!! Type \"help\" for help.\n");
		return -1;
	}
	FT[FTAdd].inode_number = inodeNumber;
	if(isUFDTFull())
	{
			printf("\nSorry no free space is available\n");
			return (-1);
	}
	fd=putFTAddIntoUFDT(FTAdd);	
	return fd;
}
