/*
%lib nacl;
%use /usr/lib/randombytes.o;
%use strerr_die;
%use open_excl;
*/
/* Public Domain */
#include <nacl/crypto_box.h>
#include "buffer.h"
#include "open.h"
#include "readwrite.h"
#include "error.h"
#include "strerr.h"

#define FATAL "crypto-box-keypair: error: "

static void err_usage()
{
    strerr_die1x(100,"crypto-box-keypair: usage: crypto-box-keypair publickeyfile secretkeyfile");
}
static void err_open(const char *file)
{
    strerr_die4sys(111,FATAL,"failed to open file '",file,"': ");
}
static void err_write(const char *file)
{
    strerr_die4sys(111,FATAL,"failed to write to file '",file,"': ");
}
static void err_keypair()
{
    strerr_die2x(111,FATAL,"failed to create keypair");
}
int main(int argc, char *argv[])
{
    int pkfd,skfd;
    unsigned char pk[crypto_box_PUBLICKEYBYTES];
    unsigned char sk[crypto_box_SECRETKEYBYTES];
    if(argc!=3) err_usage();
    pkfd = open_excl(argv[1]); if(pkfd==-1) err_open(argv[1]);
    skfd = open_excl(argv[2]); if(skfd==-1) err_open(argv[2]);
    if(crypto_box_keypair(pk,sk)!=0) err_keypair();
    if(write(pkfd,pk,sizeof(pk))!=sizeof(pk)) err_write(argv[1]);
    if(write(skfd,sk,sizeof(sk))!=sizeof(sk)) err_write(argv[2]);
    return 0;
}
