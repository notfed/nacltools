#include "byte.h"
#include "str.h"
#include "stralloc.h"
#include "buffer.h"

void stralloc_puthex(stralloc *sa)
{
  buffer_puthex(buffer_2,sa->s,sa->len);
}
