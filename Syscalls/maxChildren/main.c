#include <stdio.h>
#include <stdlib.h>
#include <sys/maxChildren.h>

int main(int argc, char** argv){
	int numberOfChildren = atoi(argv[1]);
	for (int i = 0; i < numberOfChildren; ++i)
	{
		if (fork() == 0)
		{
			sleep(5);

			exit(0);
		}
	}

	pid_t whoMaxChildren = 0;
	int maxChildren1 =0;
	maxChildren1 = maxChildren(&whoMaxChildren);
	printf("Process %d has the largest number of children: %d \n",(int)whoMaxChildren, maxChildren1);
	return 0;
}