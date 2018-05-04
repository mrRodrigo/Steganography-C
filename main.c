#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// Para usar strings

// SOIL é a biblioteca para leitura das imagens
#include "SOIL.h"

// Um pixel RGB
typedef struct {
    unsigned char r, g, b;
} RGB;

// Uma imagem em RGB
typedef struct {
    int width, height;
    RGB* img;
} Img;

// Protótipos
void load(char* name, Img* pic);
gravaBitPalavra( unsigned char w,  unsigned char ww);
char encript(char* texto, int chave, int tipo);


char encript(char* texto, int chave, int tipo) // tipo = 0 -> cifrar| tipo = 1 -> decifrar
{
    /*-----VARIAVEIS PRINCIPAIS--------*/
    int tam=strlen(texto); //recupera o tamanho da string texto
    int i=0; // variavel aux. incremento
    int cont=0; // variavel contador... impendido cifrar uma posicao já cifrada...
    char letra; //variavel alfabeto xD
    printf("Mensagem : %s\n",texto);
    for (letra='a'; letra<='z'; letra++)
        {
            while(i<=tam)
                {
                    if(texto[i] == letra)
                        {
                          /*Condição para cifrar/decifrar o texto/codigo*/
                            if(tipo == 0)
                                texto[i] = letra+chave;

                            else if (tipo == 1)
                                texto[i] = letra-chave;

                            i++;
                            cont ++;
                            letra='a';

                        }

                    else if(texto[i] == ' ')
                        {
                            i++;
                            cont ++;
                            letra='a';
                        }

                    else if(texto[i] == toupper(letra))
                        {

                            if(tipo == 0)
                                texto[i] = toupper(letra+chave);
                            else if (tipo == 1)
                                texto[i] = toupper(letra-chave);

                            i++;
                            cont ++;
                            letra='a';
                        }

                    else
                        letra++;

                    if(cont == tam)
                        break;

                }
        }
    /*-----------------------------------------*/

    if(tipo == 0)
        return printf("Mensagem cifrada em rot %d : %s\n",chave,texto);
    else
        return printf("Mensagem decifrada: %s\n",texto);
}



// Carrega uma imagem para a struct Img
void load(char* name, Img* pic)
{
    int chan;
    pic->img = (unsigned char*) SOIL_load_image(name, &pic->width, &pic->height, &chan, SOIL_LOAD_RGB);
    if(!pic->img)
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        exit(1);
    }
    printf("Load: %d x %d x %d\n", pic->width, pic->height, chan);
}



void gravaBitPalavra( int cor,int pixelPos,Img pic, unsigned char w,  unsigned char ww){
    switch (cor){
        case cor == 0:
            pic.img[pixelPos].r ^= (!w ^ pic.img[a].r) & (0x01 << 0);
            pic.img[pixelPos].r ^= (!ww ^ pic.img[a].r) & (0x01 << 1);
            break;
        case cor == 1:
            pic.img[pixelPos].g ^= (!w ^ pic.img[a].g) & (0x01 << 0);
            pic.img[pixelPos].g ^= (!ww ^ pic.img[a].g) & (0x01 << 1);
            break;
        case cor == 2:
            pic.img[pixelPos].b ^= (!w ^ pic.img[a].b) & (0x01 << 0);
            pic.img[pixelPos].b ^= (!ww ^ pic.img[a].b) & (0x01 << 1);
            break;
    }


}


int main(int argc, char** argv)
{
    Img pic;

    if(argc < 2) {
        printf("loader [img]\n");
        exit(1);
    }

    load(argv[1], &pic);

    char* frase  = argv[2];
    encript(frase, 1, 0);


    int a=0;
    int b=0;
   // int tam=strlen(frase);
    int tam=1;
    printf("Bits de cada palavra:\n");
    while(a<tam){



        printf("%c",frase[a]);
        printf("%s"," -> ");
        for(b = 7; 1 <= b; b--){
                printf("%d",(frase[a] >> b) & 0x01);
            }
            printf("\n");
        for(b = 7; 1 <= b; b-=2){
             unsigned char w = ((frase[a] >> b) & 0x01); //pega o bit na posicao b e faz um AND com o bit 1 retorna um se
                                                      //forem iguais ou seja se b for 1 e retorna 0 se forem diferentes
                                                      //ou seja quando b for zero

             unsigned char ww = (frase[a] >> b-1) & 0x01;

             printf("%s%d","Valor de W: ",w);
             printf("\n");
             printf("%s%d","Valor de WW: ",ww);

             printf("\n");

            printf("%s","antes : ");
            for(b = 7; 1 <= b; b--){
                printf("%d",(pic.img[a].r >> b) & 0x01);
            }
            printf("\n");

            pic.img[a].r ^= (!w ^ pic.img[a].r) & (0x01 << 0);
            pic.img[a].r ^= (!ww ^ pic.img[a].r) & (0x01 << 1);

            printf("%s","depois : ");

            for(b = 7; 1 <= b; b--){
                printf("%d",(pic.img[a].r >> b) & 0x01);
            }

        }
        printf("\n");
        a++;
    }





    printf("\n");
    SOIL_save_image("saida.bmp", SOIL_SAVE_TYPE_BMP, pic.width,
                    pic.height, 3, pic.img);
    free(pic.img);
}




