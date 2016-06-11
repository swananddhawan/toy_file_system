#include"file_system.h"

int closeFile(int fd)
{
	int FTentry;
	fd = checkFD(fd);
	if (fd == -1)
		return -1;
	FTentry = UA.UFDT[fd];

	FT[FTentry].byte_offset = 0;
	FT[FTentry].capability = R;
	FT[FTentry].inode_number = -1;

	UA.UFDT[fd] = -1;
	return 0;
}
