/* Public Domain */
#include "netstring.h"
#include "buffer.h"
#include "str.h"
#include "fmt.h"
int netstring_write(buffer* outbuf, const char *instr, unsigned int len)
{
    unsigned int sizedigits;
    char sizbuf[FMT_ULONG];
    sizedigits = fmt_uint(sizbuf,len);
    if(buffer_putalign(outbuf,"&",1)==-1) return 111;
    if(buffer_putalign(outbuf,sizbuf,sizedigits)==-1) return 111;
    if(buffer_putalign(outbuf,":",1)==-1) return 111;
    if(buffer_putalign(outbuf,instr,len)==-1) return 111;
    if(buffer_putalign(outbuf,",",1)==-1) return 111;
    return 0;
}
int netstring_writeflush(buffer* outbuf, const char *instr, unsigned int len)
{
    int r;
    if((r=netstring_write(outbuf,instr,len))!=0) return r;
    if((r=buffer_flush(outbuf))!=0) return r;
    return 0;
}
