#include"file_system.h"
#include<stdio.h>
#include<string.h>

/*extern UArea UA;*/
/*extern SuperBlock SB;*/
/*extern Inode DILB[];*/
/*extern FileTable FT[];*/
/*extern DIR AllDir[];*/
/*extern int remember_inode_number;*/
/*extern int getInodeNumberFromDirectory();*/
/*extern int changeDirectory();*/

void catFile(char *path)
{
	char parameter [20][20], *ptr = NULL;	
	int cnt,j,i=0;
	int inodeNumber;	
	
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
		return ;	
	}
	printf("\n\n%s\n\n",DILB[inodeNumber].data);
	return;
}
