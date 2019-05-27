#ifndef SCHEDULER_H
#define SCHEDULER_H

#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include "lists.h"

typedef struct job {
    LIST_NODE_HEADER(struct Job);
    char name[100];
    float time;
    int priority;
} job;

typedef struct listProcess {
    //Zeigt auf den ersten Knoten
    LIST_HEADER(job);
} listProcess;


job* createJob(listProcess*, char[50], int, int);
void firstComeFirstServed(listProcess*);

#endif
