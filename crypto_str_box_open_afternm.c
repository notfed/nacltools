/*
%use strerr_die;
%use stralloc_catb;
*/
#include <nacl/crypto_box.h>
#include "stralloc.h"
#include "strerr.h"
#include "crypto_str.h"

#define FATAL "crypto_str_box_open_afternm failed: "
static void err_size(const char *param)
{
    strerr_die4x(111,FATAL,"incorrect ", param," length");
}
static void err_decrypt(const char *reason)
{
    strerr_die3x(111,FATAL,"ciphertext ", reason);
}
int crypto_str_box_open_afternm(stralloc* m,
                    const stralloc* c,
                    const stralloc* n,
                    const stralloc* k)
{
  int i;
  if (k->len != crypto_box_BEFORENMBYTES) err_size("shared-key");
  if (n->len != crypto_box_NONCEBYTES) err_size("nonce");
  unsigned int clen = c->len + crypto_box_BOXZEROBYTES;
  unsigned char cpad[clen];
  for (i = 0;i < crypto_box_BOXZEROBYTES;++i) cpad[i] = 0;
  for (i = crypto_box_BOXZEROBYTES;i < clen;++i) cpad[i] = c->s[i - crypto_box_BOXZEROBYTES];
  unsigned char mpad[clen];
  if (crypto_box_open_afternm(mpad,cpad,clen,
                       (const unsigned char *) n->s,
                       (const unsigned char *) k->s
                     ) != 0) err_decrypt("fails verification");
  if (clen < crypto_box_ZEROBYTES) err_decrypt("too short");
  if(!stralloc_catb(m,(const char *)mpad+crypto_box_ZEROBYTES, 
                clen-crypto_box_ZEROBYTES)) return 111;
  return 0;
}
