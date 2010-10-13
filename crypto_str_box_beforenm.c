/* Public Domain */
#include <nacl/crypto_box.h>
#include "stralloc.h"
#include "crypto_str.h"

int crypto_str_box_beforenm(stralloc* k, 
               const stralloc* pk,
               const stralloc* sk)
{
  if (pk->len != crypto_box_PUBLICKEYBYTES) return 110;
  if (sk->len != crypto_box_SECRETKEYBYTES) return 110;
  if(!stralloc_ready(k,crypto_box_BEFORENMBYTES)) return 110;
  k->len = crypto_box_BEFORENMBYTES;
  if(crypto_box_beforenm(
    (unsigned char *) k->s,
    (const unsigned char *) pk->s,
    (const unsigned char *) sk->s
    )!=0) return 110;
  return 0;
}
