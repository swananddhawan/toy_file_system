#include"file_system.h"

int reName(char *existingFileName, char *newFileName)
{
	int i;
	int dirEntry = getDirEntry(UA.current_working_directory);

	for (i = 2; i < NO_OF_FILES_IN_DIR; i++) {
		if (strcmp(AllDir[dirEntry].file[i].file_name, existingFileName) == 0) {
			memset(AllDir[dirEntry].file[i].file_name, '\0', 20);
			strcpy(AllDir[dirEntry].file[i].file_name, newFileName);
			return 0;
		}
	}
	return -1;
}
