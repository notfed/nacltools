/* Public Domain */
#include <crypto_secretbox.h>
#include "surf.h"
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
#define FATAL "crypto-secretbox: error: "

int main(int argc, char * argv[])
{
    int r;

    /* Check args */
    if(argc!=2) 
        strerr_die1x(111,"crypto-secretbox usage: crypto-secretbox secretkeyfile");

    /* Read key */
    if(openreadclose(argv[1],&key,crypto_secretbox_KEYBYTES)<=0)
        strerr_die2sys(111,FATAL,"unable to read secret key: ");

    /* Allocate space for nonce */
    if(!stralloc_ready(&n,crypto_secretbox_NONCEBYTES)) return 111;
    n.len = crypto_secretbox_NONCEBYTES;

    /* Encrypt each chunk */
    for (;;) {

        /* Read message */
        if((r=readchunk(&m,buffer_0))==-1) 
            strerr_die2sys(111,FATAL,"unable to read input: ");
        else if(r==0) 
            break;

        /* Create nonce */
        surf_randombytes((unsigned char*)n.s,crypto_secretbox_NONCEBYTES); 

        /* Encrypt message */
        if(crypto_str_secretbox(&c,&m,&n,&key)!=0) 
            strerr_die2x(111,FATAL,"encryption failed");

        /* Write nonce */
        if(netstring_write(buffer_1,n.s,n.len)!=0)
            strerr_die2sys(111,FATAL,"failed to output nonce: ");

        /* Write cipher */
        if(netstring_write(buffer_1,c.s,c.len)!=0)
            strerr_die2sys(111,FATAL,"failed to output cipher: ");
    }
    buffer_flush(buffer_1);

    return 0;
}

