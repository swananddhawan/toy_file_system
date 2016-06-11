#include"file_system.h"

int readFile(int fd, char *buff, int noOfBytes)
{
	int FTentry, inodeNumber;
	fd = checkFD(fd);
	if (fd == -1)
		return -1;
	FTentry = UA.UFDT[fd];
	inodeNumber = (FT[FTentry].inode_number);
	noOfBytes = readDataInFile(inodeNumber, fd, buff, noOfBytes);

	return noOfBytes;

}
