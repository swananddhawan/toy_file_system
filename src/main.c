#include "file_system.h"

void initialize()
{
	initializeDILB();
	initializeUArea();
	initializeSB();
	initializeFT();
	initializeDIR();
	initializeDIRMap();
}

char *cmd[] = {"lfs", "mount", "new", "create", "write", "read", "close", "open",
	    "mkdir", "cd", "stat", "cat", "append", "copy", "ls", "pwd", "rm",
	    "touch", "clear", "rename", NULL};

static char **my_completion(const char *, int, int);

int main(void)
{
	int cnt, fd, i = 0, prtEntry = 0, flag = 0, mountFlag = 0, new = 0;
	char *temp = (char *)malloc(sizeof(char) * 80), *command, **parameter =
	  NULL, *ptr = NULL;
	char fileName[20];

	/*system ("clear"); */
	while (1) {
		char path[200] = "\nhome";
		const char *p =
		  strcat((char *)presentWorkingDirectory(path), " # : ");
		cnt = 0;
		rl_attempted_completion_function = my_completion;

		command = readline(p);
		if (command == NULL)
			exit(1);
		if (strcmp(command, "") == 0)
			continue;

		rl_bind_key('\t', rl_complete);
		if (*command != '\0')
			add_history(command);

		strcpy(temp, command);
		ptr = strtok(command, " \t");
		while (ptr) {
			cnt++;
			ptr = strtok(NULL, " \t");
		}
		parameter = (char **)malloc(sizeof(char *) * (cnt + 1));
		strcpy(command, temp);

		ptr = strtok(command, " \t");
		i = 0;
		while (ptr) {
			int length_of_parameter = strlen(ptr);
			parameter[i] = (char *)malloc(sizeof(char) * (length_of_parameter + 1));
			strcpy(parameter[i++], ptr);
			ptr = strtok(NULL, " \t");
		}
		parameter[i] = NULL;
		free(command);

		if (strcmp(parameter[0], "lfs") == 0 && (cnt == 1))
			system("ls *.fs");
		else if (strcmp(parameter[0], "mount") == 0 && (cnt == 2)) {
			if (mountFlag == 0) {
				int status = mountFileSystem(parameter[1]);
				strcpy(fileName, parameter[1]);
				if (status == 0)
					mountFlag = 1;
				else {
					printf ("\n\tFile does not exists. Please check the file name specified.\n");
					printf ("\tType \"lfs\" for listing the existing File Systems\n ");
					continue;
				}
			} else
				printf("\nCan't mount file system \n");

		} else if (strcmp(parameter[0], "new") == 0 && (cnt == 1)) {
			if (mountFlag == 0) {
				initialize();
				new = 1;
				mountFlag = 1;
				continue;
			} else
				printf("\nCan't create file system \n");
		} else if (mountFlag == 1) {
			if ((strcmp(parameter[0], "q") == 0) && (cnt == 1)) {
				printf ("\n\t Do you want to save the changes ? (0/1)\n");
				scanf ("%d", &flag);
				if (flag == 1) {
					if (new == 1) {
						printf ("\n\tPlease enter file name : ");
						scanf("%s", fileName);
					}
					unmountFileSystem(fileName);
				}
				exit(0);

			} else
			  if (strcmp(parameter[0], "stat") == 0 && (cnt == 2))
				statistics(parameter[1]);

			else if (strcmp(parameter[0], "pwd") == 0 && (cnt == 1)) {
				char path[200] = { '\0' };
				printf("\n\tPresent Working Diretory Path : %s", (char *)presentWorkingDirectory(path));

			} else if (strcmp(parameter[0], "rename") == 0
				  && (cnt == 3)) {
				int status = reName(parameter[1], parameter[2]);
				if (status == 0)
					printf ("\n\tFile renamed successfully.\n");
				else
					printf ("\n\tFile name could not be changed..!!\n");
			} else if (strcmp(parameter[0], "cat") == 0 && (cnt == 2))
				catFile(parameter[1]);

			else if (strcmp(parameter[0], "clear") == 0 && (cnt == 1))
				system("clear");

			else if (strcmp(parameter[0], "close") == 0 && (cnt == 2)) {
				int status = closeFile(atoi(parameter[1]));
				if (status == 0)
					printf ("\n\tFile closed successfully.\n");
				else
					printf ("\n\tFile could not be closed..!!\n");
			} else if (strcmp(parameter[0], "rm") == 0 && (cnt == 2)) {
				int status = removeFile(parameter[1]);
				if (status != -1)
					printf ("\n\t \" %s \" deleted successfully\n", parameter[1]);
				else
					printf ("\n\tFile could not be deleted..!!\n");

			} else if (strcmp(parameter[0], "cd") == 0 && (cnt == 2)) {
				prtEntry = cdpath(parameter[1]);
				if (prtEntry == -1)
					printf("\n\tNo such directory found\n");
				else
					flag = 1;
			} else
			  if (strcmp(parameter[0], "open") == 0 && (cnt == 3))
			{
				int fd = openFile(parameter[1], parameter[2]);
				if (fd != -1)
					printf ("\n\tFile opened successfully.\n\tFile descriptor for %s is : %d\n",
					   parameter[1], fd);
				else
					printf ("\n\tFile could not be opened..!!\n");
			} else if ((strcmp(parameter[0], "ls") == 0) && (cnt == 1 || cnt == 2)) {
				int status = 0;
				if (cnt == 1)
					status = ls_0();
				if (cnt == 2)
					status = ls_1(parameter[1]);
				if (status == -1)
					printf("Error occured..!!!\n");
				else
					printf("\tTotal Files : %d\n", status);
			} else
			  if ((strcmp(parameter[0], "touch") == 0) && (cnt == 3 || cnt == 2)) {
				int status = 0;
				if (cnt == 2)
					status = touch_0(parameter[1]);
				if (cnt == 3)
					status =
					  touch_1(parameter[1], parameter[2]);
				if (status == -1)
					printf("Error occured..!!!\n");
			} else
			  if ((strcmp(parameter[0], "create") == 0) && (cnt == 2)) {
				fd = create(parameter[1]);
				printf("\tFile descriptor of %s : %d\n", parameter[0], fd);
			} else if ((strcmp(parameter[0], "copy") == 0) && (cnt == 3)) {
				int status = 0;
				status = copyFile(atoi(parameter[1]), parameter[2]);
				if (status == 0)
					printf ("\n\tFile successfuly copied\n");
				else
					printf ("\n\tError occured while copying\n");

			} else if ((strcmp(parameter[0], "write") == 0) && (cnt == 2)) {
				cnt = 0;
				cnt = writeFile(atoi(parameter[1]));
				if (cnt == -1)
					printf ("\n\tError occured..!!!\n");
				else
					printf ("\tNumber of bytes successfully written : %d\n", cnt);
			} else if ((strcmp(parameter[0], "append") == 0) && (cnt == 2)) {
				cnt = 0;
				cnt = append(atoi(parameter[1]));
				if (cnt == -1)
					printf("\n\tError occured..!!!\n");
				else
					printf ("Number of bytes successfully written : %d\n", cnt);
			} 
			 else if ((strcmp(parameter[0], "read") == 0) && (cnt == 3)) {
				cnt = 0;
				temp = (char *)malloc(sizeof(char) * 80);
				cnt = readFile(atoi(parameter[1]), temp, atoi(parameter[2]));
				if (cnt == -1)
					printf("Error occured..!!!\n");
				else {
					printf ("Number of bytes successfully read from the file : %d\n", cnt);
					printf("\t%s\n", temp);
				}
			} else
			  if ((strcmp(parameter[0], "mkdir") == 0) && (cnt == 2))
				mkDir(parameter[1]);

			else if ((strcmp(parameter[0], "help") == 0) && (cnt == 1))
				help();
			else
				printf ("\n\tSyntax error..!! Type \"help\" for correct syntax\n");
		} else if ((strcmp(parameter[0], "q") == 0) && (cnt == 1) && (mountFlag == 0))
			exit(0);
		else if (strcmp(parameter[0], "clear") == 0 && (cnt == 1))
			system("clear");
		else if ((strcmp(parameter[0], "help") == 0) && (cnt == 1))
			help();
		else {
			if (checkMountStatus(mountFlag, parameter[0]) == -1)
				printf ("\n\tPlease mount existing file system or create new file system by typing \"new\". \n");
			else
				printf ("\n\tSyntax error..!! Type \"help\" for correct syntax\n");
		}
	}
	return 0;
}

static char **my_completion(const char *text, int start, int end)
{
	char **matches;

	matches = (char **)NULL;
	end += 1;
	if (start == 0)
		matches = rl_completion_matches((char *)text, &my_generator);
	/* else */
	/*   rl_bind_key ('\t', rl_abort); */

	return (matches);

}

char *my_generator(const char *text, int state)
{
	static int list_index, len;
	char *name;

	if (!state) {
		list_index = 0;
		len = strlen(text);
	}
	while (cmd[list_index]) {
		name = cmd[list_index];
		list_index++;

		if (strncmp(name, text, len) == 0)
			return (dupstr(name));
	}

	return ((char *)NULL);

}

char *dupstr(char *s)
{
	char *r;

	r = (char *)xmalloc((strlen(s) + 1));
	strcpy(r, s);
	return (r);
}

void *xmalloc(int size)
{
	void *buf;

	buf = malloc(size);
	if (!buf) {
		fprintf(stderr, "Error: Out of memory. Exiting.'n");
		exit(1);
	}

	return buf;
}
