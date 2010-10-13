/*
%use strerr_die;
%use strerr_sys;
%use base32_decode;
*/
/* Public Domain */
#include "readwrite.h"
#include "base32.h"
#include "strerr.h"

#define FATAL "nacl-key-decode: error: "

static void err_usage()
{
    strerr_die1x(100,"nacl-key-decode: usage: nacl-key-decode < encodedkey");
}
static void err_read()
{
    strerr_die2x(111,FATAL,"input size differed from expected 51 bytes");
}
static void err_write()
{
    strerr_die2x(111,FATAL,"failed to output key");
}
static void err_decode()
{
    strerr_die2sys(111,FATAL,"failed to decode key: ");
}

int main(int argc, char *argv[])
{
    uint8_t msg[51];
    uint8_t buf[32];
    unsigned int buflen = 32;
    if(argc!=1) err_usage();
    if(read(0,(uint8_t*)msg,51)!=51) err_read();
    if(!base32_decode(buf,&buflen,(uint8_t*)msg,51,1)) err_decode();
    if(write(1,(uint8_t*)buf,32)!=32) err_write();
    return 0;
}
