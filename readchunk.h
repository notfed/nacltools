/* Public Domain */
#ifndef READCHUNK_H
#define READCHUNK_H

#include "stralloc.h"
#include "buffer.h"

#define READALLBUF 8192

extern int readchunk(stralloc*, buffer*);

#endif
