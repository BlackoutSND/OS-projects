# OS-projects<br />
This repo contains a few projects I have made for the Operating Systems course in  university. <br />
New Syscalls and Scheduling algorithms implementations were done for Pheonix RTOS. (https://github.com/phoenix-rtos).<br />
Now a bit about each Project:<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-Syscalls: <br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;        ◦Simple get and set variable syscalls, that can read and write a variable defined in the OS.  <br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;        ◦MaxChildren - return the PID of a process that has the largest number of child processes.<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;        ◦To Test the above mentioned syscalls a few simple user programms were added.<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;    -Scheduling:<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;        ◦Implementation of 2 addtional scheuling algorithms, namely execution time and age based ones, inside PheonixRTOS, besides preexisting Round-Robin. These new algorithms can be applied to a process via changing its group.<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;        ◦To test the implementations 3 user programms were added (1 addtional to check whether the Round-Robin works as expected).<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;    -Semaphores:<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;        ◦A Semaphores based simulation of Dumbpling Producer-Consumer relation and interaction. The goal was to properly understand semaphores and how to deal with multithreading and deadlocks.<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;    -Virtual Disk:<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;        ◦An attempt to make a Virtual disk with handmade file system. Eventhough, not going to lie, it is quite junky it still works approximately as expected. <Future modifications are planned>
