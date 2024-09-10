#ifndef _SYS_SCHEDULING_H_
    #define _SYS_SCHEDULING_H_
    #include <unistd.h>
    #include <sys/types.h>
    #ifdef __cplusplus
    extern "C" {
    #endif
    extern int setThreadPriority(int priority);
    extern int getThreadPriority();
    extern int getThreadAge();
    extern int setThreadBaseAge(int baseAge);
    extern int getProcessExecTime();
    extern int setProcessExecTime(int time);
    extern int decrProcessExecTime();
    #ifdef __cplusplus
    }
    #endif
    #endif