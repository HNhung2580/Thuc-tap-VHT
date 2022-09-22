#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int disturb(int id)
{
	int i, j, temp;
	//printf("disturb: %d\n", id);
	for(int j = 0; j < 200000; j++)
	{
		for(int i = 0; i < 200000; i++)
		{
			temp = temp + i;
		}
	}
	exit(0);
}

int main(int argc, char **argv)
{
	int i;
	pid_t pid;

	if(argc != 2)
	{
		printf("Supply with one number (number of disturb to run)\n");
	}	
	else
	{
		for(int i = 0; i < atoi(argv[1]); i++)
		{
			//printf("Loop: %d\n", i);
			pid = fork();
			if(!pid)
			{
				disturb(i);
			}
		}
		printf("\n");
	}
	return 0;
}
