/*
%use strerr_die;
%use strerr_sys;
%use open_excl;
*/
/* Public Domain */
#include <nacl/crypto_secretbox.h>
#include <nacl/randombytes.h>
#include "open.h"
#include "readwrite.h"
#include "error.h"
#include "strerr.h"

#define FATAL "crypto-secretbox-key: error: "

static void err_usage()
{
    strerr_die1x(100,"crypto-secretbox-key: usage: crypto-secretbox-key secretkeyfile");
}
static void err_open(const char *file)
{
    strerr_die4sys(111,FATAL,"failed to open file '",file,"': ");
}
static void err_write(const char *file)
{
    strerr_die4sys(111,FATAL,"failed to write to file '",file,"': ");
}
int main(int argc, char *argv[])
{
    int skfd;
    unsigned char sk[crypto_secretbox_KEYBYTES];
    if(argc!=2) err_usage();
    skfd = open_excl(argv[1]); if(skfd==-1) err_open(argv[1]);
    randombytes(sk,crypto_secretbox_KEYBYTES);
    if(write(skfd,sk,sizeof(sk))!=sizeof(sk)) err_write(argv[1]);
    return 0;
}
