#ifndef __DATAFILE_H
#define __DATAFILE_H

#include <stddef.h>


struct datafile {
    FILE * file;
};

struct datafile * datafile_open(char * filename);
struct datafile * datafile_create(char * filename);

#endif