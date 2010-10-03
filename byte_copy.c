#include "byte.h"

void byte_copy(to,n,from)
register char *to;
register unsigned int n;
register const char *from;
{
  for (;;) {
    if (!n) return; *to++ = *from++; --n;
    if (!n) return; *to++ = *from++; --n;
    if (!n) return; *to++ = *from++; --n;
    if (!n) return; *to++ = *from++; --n;
  }
}
