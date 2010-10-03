/* Public Domain */
#include <stdint.h>
#include <errno.h>
static const char kChars[] = "0123456789abcdefghijklmnopqrstuv";
int base32_encode(unsigned char *output,  
                  unsigned int *ooutlen, 
                  const unsigned char *in, 
                  unsigned int inlen) 
{
  unsigned int i = 0, j = 0;
  unsigned int v = 0, bits = 0;
  const unsigned int outlen = *ooutlen;

  while (j < inlen) {
    v |= ((unsigned int) in[j++]) << bits;
    bits += 8;
    while (bits >= 5) {
      if (i >= outlen) { errno = E2BIG; return 0; }
      output[i++] = kChars[v & 31];
      bits -= 5;
      v >>= 5;
    }
  }

  if (bits && i >= outlen) { errno = E2BIG; return 0; }
  output[i++] = kChars[v];

  *ooutlen = i;
  return 1;
}
