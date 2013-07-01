#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <glib.h>

#include "datafile.h"

static struct datafile * datafile_op(char * filename, char * opentype) {
    struct datafile * df;
    df = (struct datafile *)g_malloc(sizeof(struct datafile));

    assert(df);

    df->file = fopen(filename, opentype);

    assert(df->file);

    return df;
}

struct datafile * datafile_open(char * filename) {
    return datafile_op(filename, "rb+");
}

struct datafile * datafile_create(char * filename) {
    return datafile_op(filename, "wb+");
}

void datafile_close(struct datafile * df)
{
    fclose(df->file);
    g_free(df);
}