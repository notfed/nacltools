#include "buffer.h"
int buffer_puthex(buffer* b, const char *n, unsigned int nlen)
{
  int i;
  for (i = 0;i < nlen;++i) {
    if(buffer_PUTC(b,("0123456789abcdef"[15 & (n[i] >> 4)]))!=0) return 111;
    if(buffer_PUTC(b,("0123456789abcdef"[15 & n[i]]))) return 111;
  }
  return 0;
}

