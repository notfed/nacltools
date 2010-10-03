/* Public Domain */
#include <stdint.h>
#include <errno.h>

static const unsigned char kValues[] =
  {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,
    99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,0,1,
    2,3,4,5,6,7,8,9,99,99,99,99,99,99,99,10,11,12,13,14,15,16,17,18,19,20,21,
    22,23,24,25,26,27,28,29,30,31,99,99,99,99,99,99,99,99,99,99,10,11,12,13,14,
    15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,99,99,99,99,99,99,99,99,99};

int base32_decode(unsigned char *output, 
                  unsigned int *ooutlen,
                  const unsigned char *in, 
                  unsigned int inlen, 
                  int mode) 
{
  unsigned int i = 0, j = 0;
  unsigned int v = 0, bits = 0;
  unsigned char b;
  const unsigned int outlen = *ooutlen;

  while (j < inlen) {
    if (in[j] & 0x80) { errno = EPROTO; return 0; }
    b = kValues[in[j++]];
    if (b > 31) { errno = EPROTO; return 0; }

    v |= ((unsigned int) b) << bits;
    bits += 5;

    if (bits >= 8) {
      if (i >= outlen) { errno = E2BIG; return 0; }
      output[i++] = v;
      bits -= 8;
      v >>= 8;
    }
  }

  if (mode) {
    if (bits && i >= outlen) { errno = E2BIG; return 0; }
    output[i++] = v & ((1 << bits) - 1);
  }

  *ooutlen = i;
  return 1;
}

