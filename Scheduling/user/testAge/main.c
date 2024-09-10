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
#include <unistd.h> 
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/scheduling.h>



int main(int argc, char** argv) {
	if(argc != 4)
    {
        printf("Incorrect number of parameters.\n");
        return 1;
    }
    int ageFir = atoi(argv[1]);
	int ageSec = atoi(argv[2]);
	int ageThi = atoi(argv[3]);
	printf("This time around the scheduling will decided based on the 'Age' of a thread (oldest first).\n");
	int priority = 9;
	int ages[3] = { ageFir, ageSec, ageThi };
	printf("Making 3 children...\n");
	for (int i = 0; i < 3; i++) {
		if (fork() == 0) {
			printf("Child #%d with priority: %d has been 'born' and is %d years old.\n",i, setThreadPriority(priority), setThreadBaseAge(ages[i]));
			while (1);
		}
	}
	wait(NULL);
	return 0;
}
