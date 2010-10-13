/*
%use stralloc_copys;
%use buffer_get;
%use error;
%use error_str;
*/

/* Public Domain */
#include "error.h"
#include "readchunk.h"
#include "byte.h"
#include "buffer.h"

int readchunk(stralloc *sa, buffer* in)
{
  int r;
  char tmp[READALLBUF];
  if (!stralloc_copys(sa,"")) { return -1; }

  for (;;) {
    r = buffer_get(in,tmp,READALLBUF); 
    if (r == -1) { 
        if (errno == error_intr) continue;
        else return -1;
    }
    if (r == 0) break;
    if (!stralloc_readyplus(sa,r)) { return -1; }
    byte_copy(sa->s+sa->len,r,tmp);
    sa->len += r;
    break;
  } 

  return r;
}
