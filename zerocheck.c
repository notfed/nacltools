/* Public Domain */
#include "readwrite.h"
#include "error.h"
#include "strerr.h"
int main(int argc, char *argv[])
{
    int r;
    char c[2];
    c[1] = 0;
    for (;;) {
        r = read(0,&c[0],1);
	if(r==-1 && errno == error_intr) continue;
	if(r==0) break;
        if(c[0]!='0') 
            strerr_die3x(111,"zerocheck: error: expected '0', received '",c,"'\n");
        do {
        r = write(1,&c[0],1);
        } while(r==-1 && errno == error_intr);
    }
    return 0;
}
