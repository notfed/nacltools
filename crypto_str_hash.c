/* Public Domain */
#include <nacl/crypto_hash.h>
#include "stralloc.h"
#include "crypto_str.h"

int crypto_str_hash(stralloc* h, const stralloc* m)
{
  int i;
  if(!stralloc_ready(h,crypto_hash_BYTES)) return 111;
  h->len = crypto_hash_BYTES;
  h->s[crypto_hash_BYTES]=0;
  if(crypto_hash(h->s,m->s,m->len)!=0) return 111;
  return 0;
}
