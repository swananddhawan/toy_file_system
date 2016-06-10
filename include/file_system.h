#ifndef __file_system__
#define __file_system__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_OPEN_FILES 15
#define MAX_FILES 100
#define NO_OF_FILES_IN_DIR 10
#define NO_OF_DIR 10


typedef enum {False,True} Bool;
typedef enum {Unlocked,Locked,InodeChanged,FileFieldsChanged} Status;


typedef struct
{
	int index_in_AllDir;
	int inode_number;
}DirMapEntry;

typedef struct 
{
	int inode_number;
	char file_name[20];
}FileEntry; 

typedef struct
{
	int inode_number;
	FileEntry file[NO_OF_FILES_IN_DIR];
}DIR;


void initializeDIR();
void insertFileInDir(int inode_number, char* fileName);
int cd(char *dirName);


typedef enum {Free,Directory,RegularFile} Type_i;
typedef unsigned int size_t;
typedef struct 
{
	Type_i type;
	size_t file_size;
	Status status;
	time_t last_modified;
	time_t last_accessed;
	time_t inode_modified;
	char *data;
} Inode;


typedef unsigned int size_t;
typedef struct
{
	size_t file_system_size;
	size_t no_of_free_inode;
	size_t size_of_inode_list;
	int list_of_free_inodes[10];
	int remember_inode_number; 
}SuperBlock;
Bool isListEmpty();
unsigned  int fillInodeList( unsigned int  remember_inode_number);
void removeInodeFromList(int inode_number);
Bool isInodeInFreeList(int inode_number);


int scanDILB(int remember_inode_number);
Bool isFileAlreadyExist(int inode_number);
int writeDataInFile(int inode_number, char *buff);
int readDataInFile(int inode_number,int fd, char *buff,unsigned int no_of_bytes);


typedef enum {Read, Write} iomode;
typedef struct 
{
	unsigned int current_working_directory;
	unsigned int current_working_root; 
	int UFDT[MAX_OPEN_FILES];
}UArea;

int getFreeEntryInUFDT();
Bool isUFDTFull();

typedef enum {R, W, A} Capabilities;

typedef struct
{
	unsigned int byte_offset;
	Capabilities capability; 
	int inode_number;
}FileTable;

void initializeFT();



void initializeDILB();
void initializeUArea();
void initializeSB();
void initializeFT();
void initializeDIR();
void initializeDIRMap();

int mountFileSystem();
void statistics();
char *presentWorkingDirectory();
int reName();
void catFile();
int closeFile();
int removeFile();
int cdpath();
int openFile();
int ls_0();
int ls_1();
int touch_0();
int touch_1();
int create();
int copyFile();
int writeFile();
int append();
int readFile();
void mkDir();
void help();
int checkMountStatus();
void unmountFileSystem();
int checkFD();
int appendDataInFile();
int makeEntryInFT(int inodeNumber, Capabilities c);
int putFTAddIntoUFDT(int FAdd);
int getDirEntry(int inodeNumber);
int getInodeNumberFromDirectory(char *name);
int changeDirectory(char *dirName);
int getFirstFreeInode();

int ialloc();

char* my_generator(const char*,int);
char * dupstr (char*);
void *xmalloc (int);
 
UArea UA;
SuperBlock SB;
Inode DILB[MAX_FILES];
FileTable FT[MAX_OPEN_FILES];
DIR AllDir[NO_OF_DIR];
DirMapEntry DirMap[NO_OF_DIR];

#endif
