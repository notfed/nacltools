/* Public Domain */
#include <crypto_box.h>
#include "stralloc.h"
#include "crypto_str.h"

int crypto_str_box(stralloc* c, 
               const stralloc* m,
               const stralloc* n,
               const stralloc* pk,
               const stralloc* sk)
{
  int i;
  if (pk->len != crypto_box_PUBLICKEYBYTES) return 110;
  if (sk->len != crypto_box_SECRETKEYBYTES) return 110;
  if (n->len != crypto_box_NONCEBYTES) return 110;
  unsigned int mlen = m->len + crypto_box_ZEROBYTES;
  unsigned char mpad[mlen];
  for (i = 0;i < crypto_box_ZEROBYTES;++i) mpad[i] = 0;
  for (i = crypto_box_ZEROBYTES;i < mlen;++i) mpad[i] = m->s[i - crypto_box_ZEROBYTES];
  unsigned char cpad[mlen];
  if(crypto_box(cpad,mpad,mlen,
    (const unsigned char *) n->s,
    (const unsigned char *) pk->s,
    (const unsigned char *) sk->s
    )!=0) return 110;
  if(!stralloc_copyb(c, (const char*)cpad+crypto_box_BOXZEROBYTES,
                   mlen-crypto_box_BOXZEROBYTES)) return 110;
  return 0;
}
