#include"file_system.h"

/*extern UArea UA;*/
/*extern SuperBlock SB;*/
/*extern Inode DILB[];*/
/*extern FileTable FT[];*/
/*extern DIR AllDir[];*/
/*extern int checkFD();*/

int closeFile(int fd)
{
	int FTentry;
	fd = checkFD(fd);
	if(fd == -1)
		return -1;
	FTentry=UA.UFDT[fd];

	FT[FTentry].byte_offset=0;
	FT[FTentry].capability=R;
	FT[FTentry].inode_number=-1;
		
	UA.UFDT[fd] = -1;
	return 0;
}
