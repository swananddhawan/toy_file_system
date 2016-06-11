#include"file_system.h"

int mountFileSystem(char *FileName)
{
	FILE *filePointer;
	int i, status, type;
	filePointer = fopen(FileName, "r");
	if (filePointer == NULL)
		return -1;

	fread(&SB, sizeof(SuperBlock), 1, filePointer);
	for (i = 0; i < NO_OF_DIR; i++)
		fread(&AllDir[i], sizeof(DIR), 1, filePointer);

	for (i = 0; i < NO_OF_DIR; i++)
		fread(&DirMap[i], sizeof(DirMapEntry), 1, filePointer);

	for (i = 0; i < MAX_FILES; i++) {
		char flush[5];
		fscanf(filePointer, "%d%u%d%ld%ld%ld", &type,
						       &DILB[i].file_size,
						       &status,
						       &DILB[i].last_modified,
						       &DILB[i].last_accessed,
						       &DILB[i].inode_modified);
		if (type == 0)
			DILB[i].type = Free;
		if (type == 2)
			DILB[i].type = RegularFile;
		if (type == 1)
			DILB[i].type = Directory;
		if (status == 0)
			DILB[i].status = Unlocked;
		if (status == 1)
			DILB[i].status = Locked;
		if (DILB[i].type == RegularFile)
			DILB[i].data = (char *)malloc(sizeof(char) * DILB[i].file_size);
		else if (DILB[i].type == Directory || DILB[i].type == Free)
			DILB[i].data = (char *)malloc(sizeof(char) * 2);

		fscanf(filePointer, "%[\nA-Za-z0-9 ., \\\"\'_+?/!@#$%&* ()_+; ]",
		       DILB[i].data);
		fscanf(filePointer, "%s", flush);
	}

	initializeFT();
	initializeUArea();
	fclose(filePointer);
	return 0;
}
