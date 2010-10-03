/* Public Domain */
#ifndef CRYPTO_STR_BOX_H
#define CRYPTO_STR_BOX_H

#include "stralloc.h"

int crypto_str_secretbox(
               stralloc* c,
               const stralloc* m,
               const stralloc* n,
               const stralloc* k);

int crypto_str_secretbox_open(
               stralloc* m,
               const stralloc* c,
               const stralloc* n,
               const stralloc* k);

int crypto_str_box(stralloc* c,
               const stralloc* m,
               const stralloc* n,
               const stralloc* pk,
               const stralloc* sk);

int crypto_str_box_open(
               stralloc* m,
               const stralloc* c,
               const stralloc* n,
               const stralloc* pk,
               const stralloc* sk);

int crypto_str_box_beforenm(
               stralloc* k,
               const stralloc* pk,
               const stralloc* sk);

int crypto_str_box_afternm(
               stralloc* c,
               const stralloc* m,
               const stralloc* n,
               const stralloc* k);

int crypto_str_box_open_afternm(
               stralloc* m,
               const stralloc* c,
               const stralloc* n,
               const stralloc* k);


#endif
