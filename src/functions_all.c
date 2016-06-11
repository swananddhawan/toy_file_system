#include"file_system.h"

void help(void)
{
	printf("\t1. lfs : Lists (existing)file system (s)\n\n");
	printf("\t2. mount FileSystemName : Mount respective (existing)file system\n\n");
	printf("\t3. new : Create new file system\n\n");
	printf("\t4. create FileName : File Descriptor\n\n");
	printf("\t5. write FileDescriptor : Number of bytes written\n\n");
	printf("\t6. read FileDescriptor NumberOfBytesToRead : Number of bytes read\n\n");
	printf("\t7. close FileDescriptor : File is closed\n\n");
	printf("\t8. open FileName Mode : FileDescriptor of opened file\n");
	printf("\t\tMode : (i)R : Open file in read mode\n\t\t    (ii)W : Open file in write mode\n\t\t\t (iii)A : Open file in append mode\n\n");
	printf("\t9. mkdir DirectoryName : Creates new directory in current directory\n\n");
	printf("\t10. cd Path : Change the current directory.\n\n");
	printf("\t11. stat FileName : Display statistics of file\n\n");
	printf("\t12. cat FileName : Display contents of file\n\n");
	printf("\t13. append FileDescriptor : Write in append mode\n\n");
	printf("\t14. copy FileDescriptor DestinationFileName : File is copied\n\n");
	printf("\t15. ls Flags : List the entries in current directory according to flags specified\n\n");
	printf("\t16. pwd : Print name of current/working directory\n\n");
	printf("\t17. rm FileName/DirectoryName : File/Directory is deleted\n\n");
	printf("\t19. clear : Clear Screen\n\n");
	printf("\t20. rename OldFileName NewFileName : Renames old file name to specified file name.\n\n");
	printf("\t21. q : Exit file system\n");
}

int checkFD(int fd)
{
	if (fd >= 0 && fd <= MAX_OPEN_FILES && UA.UFDT[fd] != -1) {
		if ((FT[UA.UFDT[fd]].inode_number) != -1)
			return fd;
		else
			return -1;
	} else {
		printf("\n\tInvalid file descriptor given as input\n");
		return -1;
	}
}

int checkMountStatus(int mountFlag, char *parameter)
{
	if (mountFlag == 0 &&
	    ((strcmp(parameter, "create") == 0) ||
	     (strcmp(parameter, "write")  == 0) ||
	     (strcmp(parameter, "read")   == 0) ||
	     (strcmp(parameter, "close")  == 0) ||
	     (strcmp(parameter, "ls")     == 0) ||
	     (strcmp(parameter, "pwd")    == 0) ||
	     (strcmp(parameter, "open")   == 0) ||
	     (strcmp(parameter, "cat")    == 0) ||
	     (strcmp(parameter, "stat")   == 0) ||
	     (strcmp(parameter, "mkdir")  == 0) ||
	     (strcmp(parameter, "cd")     == 0) ||
	     (strcmp(parameter, "touch")  == 0) ||
	     (strcmp(parameter, "append") == 0) ||
	     (strcmp(parameter, "rm")     == 0) ||
	     (strcmp(parameter, "copy")   == 0)))
		return -1;
	return 0;
}

void initializeSB()
{
	int i;
	SB.no_of_free_inode = MAX_FILES - 2;
	SB.remember_inode_number = 0;
	for (i = 0; i < 10; i++) {
		SB.list_of_free_inodes[i] = -1;
	}
}

int getFirstFreeInode()
{
	int i;
	for (i = 0; i < 10; i++) {
		if (DILB[SB.list_of_free_inodes[i]].type == Free)
			return SB.list_of_free_inodes[i];
	}
	return -1;

}

Bool isListEmpty()
{
	if (SB.list_of_free_inodes[9] == -1)
		return True;
	return False;
}

Bool isListFull()
{
	if (SB.list_of_free_inodes[0] != -1)
		return True;
	return False;
}

unsigned int fillInodeList(unsigned int rememberInodeNumber)
{
	int i;
	for (i = 0; i < 10; i++) {
		rememberInodeNumber = scanDILB(rememberInodeNumber);
		SB.list_of_free_inodes[i] = rememberInodeNumber;
	}
	return rememberInodeNumber;
}

void removeInodeFromList(int inodeNumber)
{
	int i;
	for (i = 0; i < 9; i++) {
		if (SB.list_of_free_inodes[i] == inodeNumber)
			SB.list_of_free_inodes[i] = -1;
	}
}

Bool isInodeInFreeList(int inodeNumber)
{
	int i;
	for (i = 0; i < 9; i++) {
		if (SB.list_of_free_inodes[i] == inodeNumber)
			return True;
	}
	return False;
}

void initializeDILB()
{
	int i;
	for (i = 0; i < MAX_FILES; i++) {
		DILB[i].type = Free;
		DILB[i].file_size = 0;
		DILB[i].status = Unlocked;
	}

	DILB[0].type = Directory;
}

int appendDataInFile(int inodeNumber, char *buff)
{
	DILB[inodeNumber].data =
	    (char *)realloc(DILB[inodeNumber].data,
			    (strlen(buff) + DILB[inodeNumber].file_size));

	if (DILB[inodeNumber].data == NULL)
		return (-1);

	DILB[inodeNumber].file_size =
	    (strlen(buff) + DILB[inodeNumber].file_size);
	DILB[UA.current_working_directory].file_size +=
	    DILB[inodeNumber].file_size;

	if (UA.current_working_directory != UA.current_working_root)
		DILB[UA.current_working_root].file_size +=
		    DILB[inodeNumber].file_size;
	strcat(DILB[inodeNumber].data, buff);

	return (strlen(buff));
}

int writeDataInFile(int inodeNumber, char *buff)
{
	DILB[inodeNumber].data = NULL;
	DILB[inodeNumber].data = (char *)malloc(strlen(buff));
	if (DILB[inodeNumber].data == NULL)
		return (-1);
	DILB[inodeNumber].file_size = (strlen(buff));
	DILB[UA.current_working_directory].file_size +=
	    DILB[inodeNumber].file_size;
	if (UA.current_working_directory != UA.current_working_root)
		DILB[UA.current_working_root].file_size +=
		    DILB[inodeNumber].file_size;
	strcat(DILB[inodeNumber].data, buff);
	return (strlen(buff));
}

int readDataInFile(int inodeNumber, int fd, char *buff, unsigned int noOfByte)
{

	unsigned int i, j = 0;
	if (noOfByte > DILB[inodeNumber].file_size)
		noOfByte = DILB[inodeNumber].file_size;

	if (noOfByte > (DILB[inodeNumber].file_size - FT[fd].byte_offset))
		noOfByte = (DILB[inodeNumber].file_size - FT[fd].byte_offset);

	for (i = FT[fd].byte_offset; i < (noOfByte + FT[fd].byte_offset); i++)
		buff[j++] = DILB[inodeNumber].data[i];

	i = changeUA_FTEntry(inodeNumber, strlen(buff));

	if (i == 0)
		return (strlen(buff));

	else
		return (-1);
}

void changeDirSize(int inodeNumber)
{
	if (UA.current_working_root != UA.current_working_directory)
		DILB[UA.current_working_root].file_size -=
		    DILB[inodeNumber].file_size;
	DILB[UA.current_working_directory].file_size -=
	    DILB[inodeNumber].file_size;
	DILB[inodeNumber].file_size = 0;
	return;
}

int scanDILB(int rememberInodeNumber)
{
	for (; rememberInodeNumber < 100;) {
		if (DILB[rememberInodeNumber + 1].type == Free)
			return (rememberInodeNumber + 1);
		rememberInodeNumber++;
	}
	return -1;
}

void initializeUArea()
{
	int i;
	for (i = 0; i < MAX_OPEN_FILES; i++)
		UA.UFDT[i] = -1;
}

Bool isUFDTFull()
{
	if (UA.UFDT[14] != -1)
		return True;
	return False;
}

int getFreeEntryInUFDT(int FTAdd)
{
	int i;
	for (i = 0; i < MAX_OPEN_FILES; i++) {
		if (UA.UFDT[i] == FTAdd)
			return i;
	}
	return -1;
}

int putFTAddIntoUFDT(int FAdd)
{
	int i;
	for (i = 0; i < MAX_OPEN_FILES; i++) {
		if (UA.UFDT[i] == -1) {
			UA.UFDT[i] = FAdd;
			return i;
		}
	}
	return -1;
}

void initializeFT()
{
	int i;
	for (i = 0; i < MAX_OPEN_FILES; i++) {
		FT[i].byte_offset = 0;
		FT[i].capability = R;
		FT[i].inode_number = -1;
	}
}

int makeEntryInFT(int inodeNumber, Capabilities c)
{
	int i;
	for (i = 0; i < MAX_OPEN_FILES; i++) {
		if (FT[i].inode_number == -1) {
			FT[i].inode_number = inodeNumber;
			FT[i].capability = c;
			return i;
		}
	}
	return (-1);
}

int changeUA_FTEntry(int inodeNumber, int offset)
{
	int i;
	for (i = 0; i < MAX_OPEN_FILES; i++) {
		if (FT[i].inode_number == inodeNumber) {
			FT[i].byte_offset += offset;
			return 0;
		}
	}
	return -1;
}

int checkInodeInFT(int inodeNumber)
{
	int i;
	for (i = 0; i < MAX_OPEN_FILES; i++) {
		if (FT[i].inode_number == inodeNumber)
			return -1;
	}
	return inodeNumber;
}

void initializeDIR()
{
	int i, j;
	for (i = 0; i < NO_OF_DIR; i++) {
		for (j = 0; j < NO_OF_FILES_IN_DIR; j++)
			AllDir[i].file[j].inode_number = -1;
		AllDir[i].inode_number = -1;
	}
	AllDir[0].inode_number = 0;
	AllDir[0].file[0].inode_number = 0;
	strcpy(AllDir[0].file[0].file_name, ".");

	AllDir[0].file[1].inode_number = 0;
	strcpy(AllDir[0].file[1].file_name, "..");
}

void initializeDIRMap()
{
	int i = 0;

	DirMap[i].index_in_AllDir = 0;
	DirMap[i].inode_number = 0;

	for (i = 1; i < NO_OF_DIR; i++) {
		DirMap[i].index_in_AllDir = i;
		DirMap[i].inode_number = -1;

	}
}

void mappingWithAllDir(int inodeNumber)
{
	int i;
	for (i = 0; i < NO_OF_DIR; i++) {
		if (DirMap[i].inode_number == -1) {
			DirMap[i].inode_number = inodeNumber;
			return;
		}
	}
}

int getDirEntry(int inodeNumber)
{
	int i;
	for (i = 0; i < NO_OF_DIR; i++) {
		if (DirMap[i].inode_number == inodeNumber)
			return i;
	}
	return -1;
}

void insertFileInDir(int inodeNumber, char *fileName)
{
	int i, j, k;
	for (i = 2; i < NO_OF_FILES_IN_DIR; i++) {
		int dirEntry = getDirEntry(UA.current_working_directory);
		if (AllDir[dirEntry].file[i].inode_number == -1) {
			AllDir[dirEntry].file[i].inode_number = inodeNumber;
			for (k = 0; k < NO_OF_FILES_IN_DIR; k++) {
				if (strcmp
				    (AllDir[dirEntry].file[k].file_name,
				     fileName) == 0) {
					printf
					    ("\n\tGiven file name already exist please give another file \n\tFile name : ");
					scanf("%s", fileName);
					break;
				}
			}
			strcpy(AllDir[dirEntry].file[i].file_name, fileName);

			if (DILB[AllDir[dirEntry].file[i].inode_number].type ==
			    Directory) {
				for (j = 1; j < NO_OF_DIR; j++) {
					if (AllDir[j].inode_number == -1) {
						AllDir[j].inode_number =
						    inodeNumber;
						AllDir[j].file[0].inode_number =
						    inodeNumber;
						AllDir[j].file[1].inode_number =
						    UA.
						    current_working_directory;
						mappingWithAllDir(inodeNumber);
						strcpy(AllDir[j].file[0].
						       file_name, ".");
						strcpy(AllDir[j].file[1].
						       file_name, "..");
						return;
					}
				}
			}

			return;
		}
	}
	printf("\n No file space available \n");
}

int nameiTemp(char *dirName)
{
	int i, j;
	int dirEntry = getDirEntry(UA.current_working_directory);

	for (i = 0; i < NO_OF_DIR; i++) {
		for (j = 0; j < NO_OF_FILES_IN_DIR; j++) {
			if (strcmp(AllDir[dirEntry].file[i].file_name, dirName))
				return (AllDir[dirEntry].file[i].inode_number);
		}
	}
	return -1;
}

int cdpath(char *path)
{
	char parameter[20][20], *ptr = NULL;
	int j, i = 0, st;

	ptr = strtok(path, "/");
	while (ptr) {
		strcpy(parameter[i++], ptr);
		ptr = strtok(NULL, "/");
	}
	i--;
	j = 0;
	while (i >= 0) {
		st = changeDirectory(parameter[j++]);
		i--;
		if (st == -1) {
			printf("\n No such directory found %s ",
			       parameter[j - 1]);
		}
	}
	return st;
}

int changeDirectory(char *dirName)
{
	int i;
	int dirEntry = getDirEntry(UA.current_working_directory);

	for (i = 0; i < NO_OF_FILES_IN_DIR; i++) {
		if (strcmp(AllDir[dirEntry].file[i].file_name, dirName) == 0) {
			UA.current_working_directory =
			    AllDir[dirEntry].file[i].inode_number;
			return i;
		}
	}
	return -1;
}

int getInodeNumberFromDirectory(char *name)
{
	int i, j;
	int dirEntry = getDirEntry(UA.current_working_directory);

	for (i = 0; i < NO_OF_DIR; i++) {
		for (j = 0; j < NO_OF_FILES_IN_DIR; j++) {
			if (strcmp(AllDir[dirEntry].file[i].file_name, name) ==
			    0)
				return (AllDir[dirEntry].file[i].inode_number);
		}
	}
	return -1;
}
