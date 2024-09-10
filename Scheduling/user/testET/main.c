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
	int priority = 10;
	if(argc == 4)
	{
		int timeFir = atoi(argv[1]);
		int timeSec = atoi(argv[2]);
		int timeThi = atoi(argv[3]);
		printf("At last the execution time based scheduling. A thread with the shortest exec time should have the priority.\n");
		
		int execTimes[3] = { timeFir, timeSec, timeThi };
		printf("Making 3 children...\n");
		for (int i = 0; i < 3; i++) {
			if (fork() == 0) {
				printf("Child #%d with priority: %d has been 'born' and has %d units of time to live :)\n",i, setThreadPriority(priority), setProcessExecTime(execTimes[i]));
				while(1){
					for (size_t j = 0; j < 100000; j++);
					int ttl = decrProcessExecTime();
					switch (ttl)
					{
					case 1410062569:
						printf("Child %d's has died RIP.\n",i);
						break;
					
					default:
						printf("Child %d's exec time left is: %d\n",i,ttl);
						break;
					}
				}
			}
		}
		wait(NULL);
		return 0;
	}
	else 
    {
		int ages[3];
		for (int i = 0; i < 3; i++) {
			if (fork() == 0) {
				printf("Child #%d with priority: %d has been 'born' and has %d units of time to live :)\n",i, setThreadPriority(priority), setProcessExecTime((i + 1) * 10));
				//sleep((i+1) * 10);
				for (int j = 0; j < 10000; j++) {
					//printf("k: %d\n", k);
				}
				setProcessExecTime(1000);
				while(1);
			}
		}
		wait(NULL);
		return 0;
    }
    
}

