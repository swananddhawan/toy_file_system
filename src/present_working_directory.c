#include"file_system.h"

char *presentWorkingDirectory(char *path)
{
	int parent[10], i, workingDir, dirEntry, j;
	for (i = 0; i < 10; i++)
		parent[i] = -1;

	workingDir = UA.current_working_directory;
	dirEntry = getDirEntry(workingDir);
	i = 0;
	while (AllDir[dirEntry].file[0].inode_number != 0) {

		parent[i++] = AllDir[dirEntry].file[0].inode_number;
		workingDir = AllDir[dirEntry].file[1].inode_number;
		dirEntry = getDirEntry(workingDir);
	}
	i--;
	for (; i >= 0; i--) {
		strcat(path, "/");
		for (j = 0; j < NO_OF_FILES_IN_DIR; j++) {
			if (AllDir[dirEntry].file[j].inode_number == parent[i]) {
				strcat(path, AllDir[dirEntry].file[j].file_name);
				dirEntry = getDirEntry(parent[i]);
			}
		}
	}
	return path;
}
