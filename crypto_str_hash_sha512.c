/*
%lib nacl;
*/
/* Public Domain */
#include <nacl/crypto_hash_sha512.h>
#include "stralloc.h"
#include "crypto_str.h"

int crypto_str_hash_sha512(stralloc* h, const stralloc* m)
{
  int i;
  if(!stralloc_ready(h,crypto_hash_sha512_BYTES)) return 111;
  h->len = crypto_hash_sha512_BYTES;
  h->s[crypto_hash_sha512_BYTES]=0;
  if(crypto_hash_sha512(h->s,m->s,m->len)!=0) return 111;
  return 0;
}
