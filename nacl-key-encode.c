/*
%use strerr_die;
%use strerr_sys;
%use base32_encode;
*/
/* Public Domain */
#include "readwrite.h"
#include "base32.h"
#include "strerr.h"

#define FATAL "nacl-key-encode: error: "

static void err_usage()
{
    strerr_die1x(100,"nacl-key-encode: usage: nacl-key-encode < key");
}
static void err_read()
{
    strerr_die2x(111,FATAL,"input size differed from expected 32 bytes");
}
static void err_write()
{
    strerr_die2x(111,FATAL,"failed to output encoded key");
}
static void err_encode()
{
    strerr_die2sys(111,FATAL,"failed to encode key: ");
}

int main(int argc, char *argv[])
{
    uint8_t msg[32];
    uint8_t buf[52];
    unsigned int buflen = 52;
    if(argc!=1) err_usage();
    if(read(0,(uint8_t*)msg,32)!=32) err_read();
    if(!base32_encode(buf,&buflen,(uint8_t*)msg,32)) err_encode();
    buf[buflen] = 0;
    if(write(1,(uint8_t*)buf,51)!=51) err_write();
    return 0;
}
