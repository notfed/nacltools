/* Public domain */
#include <crypto_box.h>
#include "stralloc.h"
#include "strerr.h"
#include "crypto_str.h"

static void err_size(const char *param)
{
    strerr_die3x(111,"crypto_str_box_open failed: incorrect ",
                 param," length");
}
static void err_decrypt(const char *reason)
{
    strerr_die2x(111,"crypto_str_box_open failed: ciphertext ",
                 reason);
}
int crypto_str_box_open(stralloc* m,
                    const stralloc* c,
                    const stralloc* n,
                    const stralloc* pk,
                    const stralloc* sk)
{
  int i;
  if (pk->len != crypto_box_PUBLICKEYBYTES) err_size("public-key");
  if (sk->len != crypto_box_SECRETKEYBYTES) err_size("secret-key");
  if (n->len != crypto_box_NONCEBYTES) err_size("nonce");
  unsigned int clen = c->len + crypto_box_BOXZEROBYTES;
  unsigned char cpad[clen];
  for (i = 0;i < crypto_box_BOXZEROBYTES;++i) cpad[i] = 0;
  for (i = crypto_box_BOXZEROBYTES;i < clen;++i) cpad[i] = c->s[i - crypto_box_BOXZEROBYTES];
  unsigned char mpad[clen];
  if (crypto_box_open(mpad,cpad,clen,
                       (const unsigned char *) n->s,
                       (const unsigned char *) pk->s,
                       (const unsigned char *) sk->s
                     ) != 0) err_decrypt("fails verification");
  if (clen < crypto_box_ZEROBYTES) err_decrypt("too short");
  if(!stralloc_catb(m,(const char *)mpad+crypto_box_ZEROBYTES, 
                clen-crypto_box_ZEROBYTES)) return 111;
  return 0;
}
