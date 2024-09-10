﻿# OS-projects
This repo contains a few projects I have made for the Operating Systems course in  university. 
> New Syscalls and Scheduling algorithms implementations were done for Pheonix RTOS. (https://github.com/phoenix-rtos).
>Now a bit about each Project:
    -Syscalls: 
        ◦Simple get and set variable syscalls, that can read and write a variable defined in the OS.  
        ◦MaxChildren - return the PID of a process that has the largest number of child processes.
        ◦To Test the above mentioned syscalls a few simple user programms were added.
    -Scheduling:
        ◦Implementation of 2 addtional scheuling algorithms, namely execution time and age based ones, inside PheonixRTOS, besides preexisting Round-Robin. These new algorithms can be applied to a process via changing its group.
        ◦To test the implementations 3 user programms were added (1 addtional to check whether the Round-Robin works as expected).
    -Semaphores:
        ◦A Semaphores based simulation of Dumbpling Producer-Consumer relation and interaction. The goal was to properly understand semaphores and how to deal with multithreading and deadlocks.
    -Virtual Disk:
        ◦An attempt to make a Virtual disk with handmade file system. Eventhough, not going to lie, it is quite junky it still works approximately as expected. <Future modifications are planned>
