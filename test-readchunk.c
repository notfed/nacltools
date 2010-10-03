/* Public Domain */
#include "readchunk.h"
#include "buffer.h"
stralloc sa = {0};
int main()
{
    readchunk(&sa,buffer_0);
    buffer_putflush(buffer_1,sa.s,sa.len);
    return 0;
}
