#ifndef BASE_32_H
#define BASE_32_H

#include <stdint.h>

int base32_decode(unsigned char *output, unsigned int *ooutlen,
                  const unsigned char *in, unsigned int inlen, int mode);
int base32_encode(unsigned char *output, unsigned int *ooutlen,
                  const unsigned char *in, unsigned int inlen);

#endif  
