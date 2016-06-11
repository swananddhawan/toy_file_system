#include"file_system.h"

void statistics(char *fileName)
{
	int inodeNumber;
	inodeNumber = getInodeNumberFromDirectory(fileName);
	if (inodeNumber == -1) {
		printf("\n\tInvalid file name specified\n");
		return;
	}

	printf("\n\t**********Statistics of inode******* \n\n\n");
	printf("\tType : %d\n\n", DILB[inodeNumber].type);
	printf("\tSize : %d\n\n", DILB[inodeNumber].file_size);
}
