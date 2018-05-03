# Img-C



Para ler um bit
pegar o bit na posicao i e faz um AND com o bit 1 retorna um se forem iguais ou seja se i for 1 e retorna 0 se forem diferentes ou seja quando i for zero


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
