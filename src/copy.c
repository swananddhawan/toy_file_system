#include"file_system.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*extern UArea UA;*/
/*extern SuperBlock SB;*/
/*extern Inode DILB[MAX_FILES];*/
/*extern FileTable FT[MAX_OPEN_FILES];*/
/*extern DIR AllDir[NO_OF_DIR];*/
/*extern int remember_inode_number;*/

/*extern int checkFD();*/
/*extern int readDataInFile();*/
/*extern int create();*/

int copyFile(int sourceFD,char *destination)
{
	int FTentry,inodeNumber,cnt,destFD;
	char *buffer = NULL;
	sourceFD = checkFD(sourceFD);
	if(sourceFD == -1)
	{
		printf("Invalid file descriptor given as input\n");
		return -1;
	}
	FTentry=UA.UFDT[sourceFD];
	inodeNumber=(FT[FTentry].inode_number);
	DILB[inodeNumber].status=Locked;
	
	buffer = (char *)malloc(sizeof(char) * DILB[inodeNumber].file_size);
	cnt = readDataInFile(inodeNumber, sourceFD,buffer,DILB[inodeNumber].file_size);
	
	destFD = create(destination);
	printf("\n\tFile descriptor of %s : %d\n",destination,destFD);
	
	DILB[FT[UA.UFDT[destFD]].inode_number].data = (char *)malloc(sizeof(char) * DILB[inodeNumber].file_size);
	strcpy(DILB[FT[UA.UFDT[destFD]].inode_number].data,buffer);
	DILB[FT[UA.UFDT[destFD]].inode_number].file_size=cnt;

	DILB[UA.current_working_directory].file_size+=cnt;
	if(UA.current_working_directory!=UA.current_working_root)
		DILB[UA.current_working_root].file_size+=cnt;	
	
	return 0;	
}
