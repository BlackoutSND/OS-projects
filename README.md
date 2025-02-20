# Operating Systems Projects  

This repository contains projects I made for my university's **Operating Systems** course. The projects include **new system calls, scheduling algorithms, semaphores, and a virtual disk** in **Phoenix-RTOS** ([GitHub Repository](https://github.com/phoenix-rtos)).  

## Projects Overview  

### 1. System Calls  
I added new system calls to **Phoenix-RTOS**:  
- **Get and Set Variable Syscalls** – Read and write a variable inside the OS.  
- **MaxChildren** – Get the PID of the process with the most child processes.  
- **Testing Programs** – Simple programs to test these system calls.  

### 2. Scheduling Algorithms  
I added **two new scheduling algorithms** to **Phoenix-RTOS**, in addition to the existing **Round-Robin**:  
- **Execution-Time-Based Scheduling**  
- **Age-Based Scheduling**  
- These algorithms can be used by changing a process's scheduling group.  
- **Testing Programs** – Three programs to test the new algorithms (including one for Round-Robin).  

### 3. Semaphores  
I made a **semaphore-based** simulation of the **Dumpling Producer-Consumer** problem:  
- Helps understand **semaphores, multithreading, and deadlocks**.  

### 4. Virtual Disk  
I created a **virtual disk** with a simple handmade **file system**:  
- It’s not perfect, but it works **more or less** as expected.  
