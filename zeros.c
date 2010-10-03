/* Public Domain */
#include "readwrite.h"
static char z[8192];
int main(int argc, char *argv[])
{
    int i,b;
    for (i=0;i<8192;i++) { z[i] = '0'; }
    b = 1;
    for (;;) {
        write(1,z,(b++%8192));
    }
}
