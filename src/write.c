#include"file_system.h"

int writeFile(int fd)
{
	int FTentry, inodeNumber, noOfBytes;
	char temp[1024], flush[2];
	fd = checkFD(fd);
	if (fd == -1)
		return -1;
	FTentry = UA.UFDT[fd];
	if (FT[FTentry].capability == R) {
		printf("\n\tPermission denied..!!\n");
		return -1;
	}
	printf("Enter what you want to write in the file :\n");
	scanf("%[\nA-Za-z0-9 ., \\\"\'_+?/!@#$%&* ()_+; ]", temp);
	scanf("%s", flush);
	inodeNumber = (FT[FTentry].inode_number);
	noOfBytes = writeDataInFile(inodeNumber, temp);
	if (noOfBytes == -1) {
		printf("\n Unable to write data in file \n");
		return (-1);
	}
	return noOfBytes;
}
