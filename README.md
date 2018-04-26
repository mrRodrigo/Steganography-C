# Img-C



```
#include <stdio.h>
int main()
{
    char byte = 0x37;
    int i;

    for(i = 7; 0 <= i; i --)
        printf("%d\n", (byte >> i) & 0x01);

    return 0;
}```
