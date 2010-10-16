/*
%use buffer_put;
%use buffer_puthex;
%use buffer_0;
%use buffer_1;
%use buffer_2;
%use strerr_die;
%use strerr_sys;
%use stralloc_ready;
%use crypto_str_hash_sha512;
%use appendchunk;
%use stralloc_copys;
%use error_str;
%use str_diff;
*/
/* Public Domain */
#include <nacl/crypto_hash.h>
#include "crypto_str.h"
#include "stralloc.h"
#include "buffer.h"
#include "strerr.h"
#include "appendchunk.h"
#include "byte.h"

static stralloc m = {0};
static stralloc h = {0};
#define FATAL "crypto-hash-sha512: error: "

int main(int argc, char * argv[])
{
    int r;

    /* Check args */
    if(argc>2) 
        strerr_die1x(111,"crypto-hash-sha512: usage: crypto-hash-sha512 < message");

    /* Read entire input */
    for (;;) {

        /* Read message */
        if((r=appendchunk(&m,buffer_0))==-1) 
            strerr_die2sys(111,FATAL,"unable to read input: ");
        else if(r==0) 
            break;

    }

    /* Hash message */
    if(crypto_str_hash_sha512(&h,&m)!=0) 
        strerr_die2x(111,FATAL,"hash failed");

    /* Output hash */
    if(argc==2 && !str_diff(argv[1],"-b")) 
        buffer_put(buffer_1,h.s,h.len);
    else 
        buffer_puthex(buffer_1,h.s,h.len);
    
  
    buffer_putsflush(buffer_1,"\n");

    return 0;
}

