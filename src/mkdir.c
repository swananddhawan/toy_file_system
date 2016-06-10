#include<time.h>
#include"file_system.h"

extern UArea UA;
extern SuperBlock SB;
extern Inode DILB[];
extern FileTable FT[];
extern DIR AllDir[];
extern DirMapEntry DirMap[];

extern void insertFileInDir();
extern int ialloc();

void mkDir(char *dirName)
{
	int inodeNumber;

	inodeNumber=ialloc() ;
	DILB[inodeNumber].type=Directory;
	DILB[inodeNumber].last_modified=time(NULL);
	DILB[inodeNumber].last_accessed=time(NULL);
	DILB[inodeNumber].inode_modified=time(NULL);
	
	insertFileInDir(inodeNumber, dirName);
}
