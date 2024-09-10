/*
 * Phoenix-RTOS
 *
 * Hello World
 *
 * Example of user application
 *
 * Copyright 2021 Phoenix Systems
 * Author: Hubert Buczynski
 *
 * This file is part of Phoenix-RTOS.
 *
 * %LICENSE%
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/scheduling.h>

int main(int argc, char** argv) {

	if(argc != 2)
    {
        printf("Incorrect number of parameters.\n");
        return 1;
    }
    int children = atoi(argv[1]);
	printf("Nothing special should be observed 'cause it is the default scheduling algorithm of PhoenixS.\n");
	int priority = 8;
	printf("Making children...\n");

	for (int i = 0; i < children; i++) {
		if (fork() == 0) {
			printf("Child #%d with priority: %d has been 'born'.\n", i, setThreadPriority(priority));
			while (1);
		}
	}
	
	return 0;
}