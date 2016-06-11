#include"file_system.h"

void ifree(int inodeNumber)
{
	int i, j, entryInDir;
	SB.no_of_free_inode++;
	if (DILB[inodeNumber].type == RegularFile) {
		free(DILB[inodeNumber].data);
		DILB[inodeNumber].data = NULL;
	}
	if (inodeNumber < SB.remember_inode_number)
		SB.remember_inode_number = inodeNumber;

	for (i = 2; i < NO_OF_FILES_IN_DIR; i++) {
		if (AllDir[UA.current_working_directory].file[i].inode_number == inodeNumber) {

			if (DILB[AllDir[UA.current_working_directory].file[i].inode_number].type == Directory) {
				for (j = 0; j < NO_OF_DIR; j++) {
					if (AllDir[j].inode_number == inodeNumber) {
						entryInDir = j;
						break;
					}
				}
				for (j = 2; j < NO_OF_FILES_IN_DIR; j++) {
					if (AllDir[entryInDir].file[j].inode_number != -1) {
						printf ("\n\tDeletion Failed...!!");
						printf ("\n\tDirectory is not empty...!! Delete all the contents in Directory first \n");
						return;
					}
				}
			}
			AllDir[UA.current_working_directory].file[i].inode_number = -1;
			memset(AllDir[UA.current_working_directory].file[i].file_name, '\0', 20);
		}
	}
	DILB[inodeNumber].type = Free;
}
