#ifndef NETSTRING_H
#define NETSTRING_H 
#include "buffer.h"
#include "stralloc.h"
int netstring_write(buffer*,const char *str,unsigned int len);
int netstring_writeflush(buffer*,const char *str,unsigned int len);
int netstring_read(buffer*,stralloc*);
#endif
