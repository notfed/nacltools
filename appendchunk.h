/* Public Domain */
#ifndef APPENDCHUNK_H
#define APPENDCHUNK_H

#include "stralloc.h"
#include "buffer.h"

#define READALLBUF 8192

extern int appendchunk(stralloc*, buffer*);

#endif
