/* Public Domain */
#include <stdio.h>
#include "netstring.h"
#include "buffer.h"
#include "scan.h"
#include "fmt.h"
#include "stralloc.h"
#include "strerr.h"
#define FATAL "netstring_read failed: "
int netstring_read(buffer* inbuf, stralloc *outstr)
{
    char tmp;
    char lenbuf[FMT_ULONG];
    int i;
    unsigned long len;
    int r;
    
    if(!stralloc_copys(outstr,""))
        strerr_die2x(111,FATAL,"failed to initialize stralloc");
    if((r=buffer_GETC(inbuf,&tmp))==-1) 
        strerr_die2x(111,FATAL,"failed to read buffer");
    if(r==0) return 0;

    if(tmp!='&') 
        strerr_die2x(111,FATAL,"expected '&'");

    for(i=0;i<FMT_ULONG-1;i++) {
      if(buffer_GETC(inbuf,&tmp)!=1)
        strerr_die2x(111,FATAL,"failed to read buffer [2]");
      if(tmp==':') { 
          if(i==0) strerr_die2x(111,FATAL,"expected ':'");
          break; 
      }
      if(tmp <'0' || tmp > '9') 
          if(i==0) strerr_die2x(111,FATAL,"expected string length");
      lenbuf[i] = tmp;
    }
    lenbuf[i] = 0;

    if(scan_ulong(lenbuf,&len)==0) 
          strerr_die2x(111,FATAL,"failed to parse string length");
    if(stralloc_ready(outstr,len)==0) 
          strerr_die2x(111,FATAL,"failed to allocate result string");
    outstr->len = len;
    if((r=buffer_getn(inbuf,outstr->s,len))!=len)  {
        strerr_die2x(111,FATAL,"failed to read buffer [3]");
    }
    if(buffer_GETC(inbuf,&tmp)!=1) 
        strerr_die2x(111,FATAL,"failed to read buffer [4]");
    if(tmp!=',') 
          strerr_die2x(111,FATAL,"expected ','");
    return 0;
}
