/*
%use stralloc_copyb;
*/
/* Public Domain */
#include <nacl/crypto_secretbox.h>
#include "stralloc.h"
#include "crypto_str.h"

int crypto_str_secretbox_open(stralloc* m,
                          const stralloc* c,
                          const stralloc* n,
                          const stralloc* k)
{
  int i;
  if (k->len != crypto_secretbox_KEYBYTES) return 110;
  if (n->len != crypto_secretbox_NONCEBYTES) return 110;
  unsigned int clen = c->len + crypto_secretbox_BOXZEROBYTES;
  unsigned char cpad[clen];
  for (i = 0;i < crypto_secretbox_BOXZEROBYTES;++i) cpad[i] = 0;
  for (i = crypto_secretbox_BOXZEROBYTES;i < clen;++i) cpad[i] = c->s[i - crypto_secretbox_BOXZEROBYTES];
  unsigned char mpad[clen];
  if (crypto_secretbox_open(mpad,cpad,clen,
                           (const unsigned char *) n->s,
                           (const unsigned char *) k->s) != 0) return 112;
  if (clen < crypto_secretbox_ZEROBYTES) return 110;
  if(!stralloc_copyb(
     m, (char *) mpad + crypto_secretbox_ZEROBYTES,
    clen - crypto_secretbox_ZEROBYTES
  )) return 110;
  return 0;
}
