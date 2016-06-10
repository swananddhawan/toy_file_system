#include"file_system.h"
/*extern UArea UA;*/
/*extern SuperBlock SB;*/
/*extern Inode DILB[MAX_FILES];*/
/*extern FileTable FT[MAX_OPEN_FILES];*/

/*extern Bool isListEmpty();*/
/*extern unsigned int fillInodeList();*/
/*extern int getFirstFreeInode();*/
int ialloc()
{
	int done=0,inodeNumber;
	while(!done)
	{		
		if(isListEmpty())
		{
			 SB.remember_inode_number=fillInodeList( SB.remember_inode_number);
			if(isListEmpty())
				return(-1);
		}
		inodeNumber=getFirstFreeInode();
		
		SB.no_of_free_inode=SB.no_of_free_inode-1;
		return (inodeNumber);
	}
	return -1;
}
