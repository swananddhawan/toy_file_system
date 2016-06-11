#include"file_system.h"

int touch_0(char *fileName)
{
	int inodeNumber = getInodeNumberFromDirectory(fileName);
	if (inodeNumber == -1) {
		printf("\n\tInvalid file name specified\n");
		return -1;
	}
	return 0;
}

int touch_1(char *fileName, char *mode)
{
	int inodeNumber = getInodeNumberFromDirectory(fileName);
	if (inodeNumber == -1) {
		printf("\n\tInvalid file name specified\n");
		return -1;
	}

	if (*mode == 'a') {
	}

	if (*mode == 'm') {
	}
	return 0;
}
