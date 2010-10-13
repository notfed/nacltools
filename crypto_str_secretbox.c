/* Public Domain */
#include <nacl/crypto_secretbox.h>
#include "stralloc.h"
#include "crypto_str.h"

int crypto_str_secretbox(stralloc* c,
                     const stralloc* m,
                     const stralloc* n,
                     const stralloc* k)
{
  int i;
  if (k->len != crypto_secretbox_KEYBYTES) return 110;
  if (n->len != crypto_secretbox_NONCEBYTES) return 110;
  unsigned int mlen = m->len + crypto_secretbox_ZEROBYTES;
  unsigned char mpad[mlen];
  for (i = 0;i < crypto_secretbox_ZEROBYTES;++i) mpad[i] = 0;
  for (i = crypto_secretbox_ZEROBYTES;i < mlen;++i) mpad[i] = m->s[i - crypto_secretbox_ZEROBYTES];
  unsigned char cpad[mlen];
  crypto_secretbox(cpad,mpad,mlen,(const unsigned char *) n->s,(const unsigned char *) k->s);
  if(!stralloc_copyb(c, (const char*)cpad+crypto_secretbox_BOXZEROBYTES,
                 mlen-crypto_secretbox_BOXZEROBYTES)) return 111;
  return 0;
}
