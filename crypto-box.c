/*
%use buffer_put;
%use buffer_0;
%use buffer_1;
%use buffer_2;
%use openreadclose;
%use env;
%use strerr_die;
%use strerr_sys;
%use stralloc_ready;
%use surf;
%use crypto_str_box_beforenm;
%use crypto_str_box_afternm;
%use netstring_write;
%use readchunk;
*/
/* Public Domain */
#include <nacl/crypto_box.h>
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
#include "env.h"

static stralloc pk = {0};
static stralloc sk = {0};
static stralloc k = {0};
static stralloc m = {0};
static stralloc c = {0};
static stralloc n = {0};
#define FATAL "crypto-box: error: "
/*
void show(const char *desc, stralloc *s)
{ 
  buffer_puts(buffer_2,desc);
  buffer_puthex(buffer_2,s->s,s->len); 
  buffer_putsflush(buffer_2,"\n"); 
}
*/

int main(int argc, char * argv[])
{
    int r;
    const char* pk0;
    const char* sk0;

    /* Check args */
    pk0 = ((argc<2) ? env_get("NACL_PUBLICKEY_FILE") : argv[1]);
    sk0 = ((argc<3) ? env_get("NACL_SECRETKEY_FILE") : argv[2]);

    if(pk0==0 || sk0==0) 
        strerr_die1x(100,"crypto-box: usage: crypto-box [ publickeyfile ] [ secretkeyfile ]");

    /* Read public key */
    if(openreadclose(argv[1],&pk,crypto_box_PUBLICKEYBYTES)<=0)
        strerr_die2sys(111,FATAL,"unable to read public key: ");

    /* Read secret key */
    if(openreadclose(argv[2],&sk,crypto_box_SECRETKEYBYTES)<=0)
        strerr_die2sys(111,FATAL,"unable to read secret key: ");

    /* Allocate space for nonce */
    stralloc_ready(&n,crypto_box_NONCEBYTES);
    n.len = crypto_box_NONCEBYTES;

    /* Create shared key */
    if(crypto_str_box_beforenm(&k,&pk,&sk))
        strerr_die2x(111,FATAL,"failed to create shared-key");

    /* Encrypt each chunk */
    for (;;) {

        /* Read message */
        if((r=readchunk(&m,buffer_0))==-1) 
            strerr_die2sys(111,FATAL,"unable to read input: ");
        else if(r==0) 
            break;

        /* Create nonce */
        surf_randombytes((unsigned char*)n.s,crypto_box_NONCEBYTES); 

        /* Encrypt message */
        if(crypto_str_box_afternm(&c,&m,&n,&k)!=0) 
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

