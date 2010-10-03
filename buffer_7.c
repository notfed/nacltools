#include "buffer.h"

char buffer_7_space[BUFFER_OUTSIZE];
static buffer it = BUFFER_INIT(buffer_unixwrite,7,buffer_7_space,sizeof buffer_7_space);
buffer *buffer_7 = &it;
