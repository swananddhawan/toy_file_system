#include"file_system.h"

int create(char *fileName)
{
	int fd, inodeNumber, FTAdd = 0;
	inodeNumber = ialloc();
	DILB[inodeNumber].type = RegularFile;

	insertFileInDir(inodeNumber, fileName);

	FTAdd = makeEntryInFT(inodeNumber, 1);

	if (isUFDTFull()) {
		printf("\nSorry no free space is available\n");
		return -1;
	}
	fd = putFTAddIntoUFDT(FTAdd);
	return fd;

}
