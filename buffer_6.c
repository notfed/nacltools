#include "readwrite.h"
#include "buffer.h"

int buffer_6_read(fd,buf,len) int fd; char *buf; int len;
{
  if (buffer_flush(buffer_7) == -1) return -1;
  return read(fd,buf,len);
}

char buffer_6_space[BUFFER_INSIZE];
static buffer it = BUFFER_INIT(buffer_6_read,6,buffer_6_space,sizeof buffer_6_space);
buffer *buffer_6 = &it;
