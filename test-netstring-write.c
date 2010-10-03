/* Public Domain */
#include "buffer.h"
#include "stralloc.h"
#include "netstring.h"
#include "fmt.h"
int main()
{
    int i;
    char buf[8192];

for (;;) {
    i = buffer_get(buffer_0,buf,8192);
    if(i==-1) return 111;
    if(i==0) break;
    if(netstring_write(buffer_1,buf,i)!=0) return 111;
}
    buffer_flush(buffer_1);

    return 0;
}
