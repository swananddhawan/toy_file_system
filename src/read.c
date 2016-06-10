#include"file_system.h"

extern UArea UA;
extern SuperBlock SB;
extern Inode DILB[];
extern FileTable FT[];
extern DIR AllDir[];
extern int remember_inode_number;

extern int checkFD();
extern int readDataInFile();


int readFile(int fd, char * buff, int noOfBytes)
{
	int FTentry, inodeNumber;
	fd = checkFD(fd);
	if(fd == -1)
		return -1;
	FTentry=UA.UFDT[fd];
	inodeNumber=(FT[FTentry].inode_number);
	noOfBytes = readDataInFile(inodeNumber, fd , buff , noOfBytes);
	DILB[inodeNumber].last_accessed=time(NULL);
	DILB[inodeNumber].inode_modified=time(NULL);
		
	return (noOfBytes);

}
