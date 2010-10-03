/* Public Domain */
#include "buffer.h"
#include "stralloc.h"
#include "netstring.h"
#include "fmt.h"
stralloc strbuf = {0};
int main()
{
    int len;
    char lenbuf[FMT_ULONG];

for (;;) {
    if((len=netstring_read(buffer_0,&strbuf))==-1) return 111;
    if(strbuf.len==0) break;


    buffer_puts(buffer_1,"netstring:\n");
    buffer_puts(buffer_1," Length: ");
    lenbuf[fmt_ulong(lenbuf,strbuf.len)]=0;
    buffer_puts(buffer_1,lenbuf);
    buffer_puts(buffer_1,"\n");

    buffer_puts(buffer_1," String: ");
    buffer_put(buffer_1,strbuf.s,strbuf.len);
    buffer_putsflush(buffer_1,"\n");
}

    return 0;
}
