#include"file_system.h"

void mkDir(char *dirName)
{
	int inodeNumber;

	inodeNumber = ialloc();
	DILB[inodeNumber].type = Directory;

	insertFileInDir(inodeNumber, dirName);
}
