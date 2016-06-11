#include"file_system.h"

void unmountFileSystem(char *FileName)
{
	FILE *filePointer;
	int i;
	filePointer = fopen(FileName, "w+");

	fwrite(&SB, sizeof(SuperBlock), 1, filePointer);

	for (i = 0; i < NO_OF_DIR; i++)
		fwrite(&AllDir[i], sizeof(DIR), 1, filePointer);

	for (i = 0; i < NO_OF_DIR; i++)
		fwrite(&DirMap[i], sizeof(DirMapEntry), 1, filePointer);

	for (i = 0; i < MAX_FILES; i++) {
		if (DILB[i].type == RegularFile) {
			fprintf(filePointer, "%d %d %d %ld %ld %ld %s",
				DILB[i].type, DILB[i].file_size, DILB[i].status,
				DILB[i].last_modified, DILB[i].last_accessed,
				DILB[i].inode_modified, DILB[i].data);
			fprintf(filePointer, "- ");
		} else {
			fprintf(filePointer, "%d %d %d %ld %ld %ld ",
				DILB[i].type, DILB[i].file_size, DILB[i].status,
				DILB[i].last_modified, DILB[i].last_accessed,
				DILB[i].inode_modified);
			fprintf(filePointer, "- ");
		}
	}
	fclose(filePointer);
}
