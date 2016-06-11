#include"file_system.h"

int removeFile(char *path)
{
	char parameter[20][20], *ptr = NULL;
	int i = 0, inodeNumber, cnt, j;

	ptr = strtok(path, "/");
	while (ptr) {
		strcpy(parameter[i++], ptr);
		ptr = strtok(NULL, "/");
	}
	i--;
	cnt = i;
	j = 0;
	while (i > 0) {
		int st = changeDirectory(parameter[j++]);
		i--;
		if (st == -1)
			printf("\n No such directory found %s ", parameter[j - 1]);
	}

	if (i == 0)
		inodeNumber = getInodeNumberFromDirectory(parameter[j]);
	else
		inodeNumber = getInodeNumberFromDirectory(parameter[cnt - 1]);

	if (inodeNumber == -1) {
		printf("\n\tInvalid file name specified\n");
		return -1;
	}

	inodeNumber = checkInodeInFT(inodeNumber);
	if (inodeNumber == -1) {
		printf("\n\tFile is opened..!! So can't be deleted.\n");
		return -1;
	}

	ifree(inodeNumber);
	changeDirSize(inodeNumber);
	return 0;
}
