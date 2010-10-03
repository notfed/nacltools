#include "surf.h"
#include "byte.h"
#include "str.h"
#include "stralloc.h"

int stralloc_random(stralloc *sa,unsigned int bytes)
{
    if(!stralloc_ready(sa,bytes)) return 0;
    sa->len = bytes;
    surf_randombytes((unsigned char*)sa->s,bytes);
    return 1;
}
