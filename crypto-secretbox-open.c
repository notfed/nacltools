/* Public Domain */
#include <crypto_secretbox.h>
#include "crypto_str.h"
#include "stralloc.h"
#include "buffer.h"
#include "strerr.h"
#include "open.h"
#include "openreadclose.h"
#include "readchunk.h"
#include "byte.h"
#include "netstring.h"

static stralloc key = {0};
static stralloc m = {0};
static stralloc c = {0};
static stralloc n = {0};
#define FATAL "crypto-secretbox-open: error: "

int main(int argc, char * argv[])
{
    int r;

    /* Check args */
    if(argc!=2) 
        strerr_die1x(100,"usage: crypto-secretbox-open secretkeyfile");

    /* Read secret key */
    if(openreadclose(argv[1],&key,crypto_secretbox_KEYBYTES)<=0)
        strerr_die2sys(111,FATAL,"unable to read secret key: ");

    /* Decrypt each chunk */
    for (;;) {

        /* Read nonce */
        if((r=netstring_read(buffer_0,&n))!=0)
            strerr_die2x(111,FATAL,"failed to read nonce");
        if(n.len==0) break;
        if(n.len!=crypto_secretbox_NONCEBYTES) 
            strerr_die2x(111,FATAL,"nonce was incorrect size");

        /* Read cipher */
        if(netstring_read(buffer_0,&c)!=0)
            strerr_die2x(111,FATAL,"failed to read cipher");

        /* Decrypt message */
        if(crypto_str_secretbox_open(&m,&c,&n,&key)!=0)
            strerr_die2x(111,FATAL,"decryption failed");

        /* Write message */
        if(buffer_put(buffer_1,m.s,m.len)!=0) 
            strerr_die2x(111,FATAL,"failed to output message: ");

    }
    buffer_flush(buffer_1);

    return 0;
}

