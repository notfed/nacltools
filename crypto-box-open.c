/* Public Domain */
#include <crypto_box.h>
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
#define FATAL "crypto-box-open: error: "

void show(const char *desc, stralloc *s)
{ 
  buffer_puts(buffer_2,desc);
  buffer_puthex(buffer_2,s->s,s->len); 
  buffer_putsflush(buffer_2,"\n"); 
}
int main(int argc, char * argv[])
{
    int r;

    /* Check args */
    if(argc!=3) {
        if( (argv[1] = env_get("NACL_PUBLICKEY_FILE"))==0 
        ||  (argv[2] = env_get("NACL_SECRETKEY_FILE"))==0 )
        strerr_die1x(111,"usage: crypto-box [ publickeyfile secretkeyfile ]");
    }

    /* Read public key */
    if(openreadclose(argv[1],&pk,crypto_box_PUBLICKEYBYTES)<=0)
        strerr_die2sys(111,FATAL,"unable to read public key: ");

    /* Read secret key */
    if(openreadclose(argv[2],&sk,crypto_box_SECRETKEYBYTES)<=0)
        strerr_die2sys(111,FATAL,"unable to read secret key: ");

    /* Create shared key */
    if(crypto_str_box_beforenm(&k,&pk,&sk))
        strerr_die2x(111,FATAL,"failed to create shared-key");

    /* Decrypt each chunk */
    for (;;) {

        /* Read nonce */
        if((r=netstring_read(buffer_0,&n))!=0)
            strerr_die2x(111,FATAL,"failed to read nonce");
        if(n.len==0) break;
        if(n.len!=crypto_box_NONCEBYTES)
            strerr_die2x(111,FATAL,"nonce was incorrect size");

        /* Read cipher */
        if(netstring_read(buffer_0,&c)!=0)
            strerr_die2x(111,FATAL,"failed to read cipher");

        /* Decrypt message */
        if(crypto_str_box_open_afternm(&m,&c,&n,&k)!=0) 
            strerr_die2x(111,FATAL,"decryption failed");

        /* Write message */
        if(buffer_put(buffer_1,m.s,m.len)!=0) 
            strerr_die2sys(111,FATAL,"failed to output message: ");

    }
    buffer_flush(buffer_1);

    return 0;
}

