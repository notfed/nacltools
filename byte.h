#ifndef BYTE_H
#define BYTE_H

extern unsigned int byte_chr(char *one, unsigned int len, int c);
extern unsigned int byte_rchr(char *one, unsigned int len, int c);
extern void byte_copy(char *out, unsigned int len, const char *in);
extern void byte_copyr(char *out, unsigned int len, const char *in);
extern int byte_diff(const char *one, unsigned int len, const char *two);
extern void byte_zero(char *out, unsigned int len);

#define byte_equal(s,n,t) (!byte_diff((s),(n),(t)))

#endif
