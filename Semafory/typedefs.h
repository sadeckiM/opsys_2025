#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H

#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/mman.h>

const int N = 10;
extern const char * name;
extern int * ptr_write;
extern int * ptr_read;

#endif

