#include <stdio.h>

#define YES 1
#define NO 0
int main()
{
    int c, nl, nw, nc, inword;
    inword = NO;
    nl = 0;
    nw = 0;
    nc = 0;
    c = getchar();
    while ( c != EOF ) {
        nc = nc + 1;
        if ( c == '\n')
            nl = nl + 1;
        if ( c == ' ' || c == '\n' || c == '\t' )
            inword = NO;
        else if (inword == NO) {
            inword = YES;
            nw = nw + 1;
        }
        c = getchar();
    }
    printf("%d \n", nl);
    printf("%d \n", nw);
    printf("%d \n", nc);

    return 0;
}
