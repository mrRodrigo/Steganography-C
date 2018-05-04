#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// Para usar strings

// SOIL é a biblioteca para leitura das imagens
#include "SOIL.h"


// CONSTANTE QUE REPRESENTA O FINAL DA GRAVAÇÃO
#define FINALCHAR '$'

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
void gravaBitPalavra(int cor,int pixelPos,Img pic, unsigned char w,  unsigned char ww);
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



void gravaBitPalavra(int cor,int pixelPos,Img pic, unsigned char w,  unsigned char ww){

        switch (cor){
            case 0:
                pic.img[pixelPos].r ^= (-ww ^ pic.img[pixelPos].r) & (0x01);
                pic.img[pixelPos].r ^= (-w ^ pic.img[pixelPos].r) & (0x01 << 1);
                break;
            case 1:
                pic.img[pixelPos].g ^= (-ww ^ pic.img[pixelPos].g) & (0x01 );
                pic.img[pixelPos].g ^= (-w ^ pic.img[pixelPos].g) & (0x01 << 1);
                break;
            case 2:
                pic.img[pixelPos].b ^= (-ww ^ pic.img[pixelPos].b) & (0x01);
                pic.img[pixelPos].b ^= (-w ^ pic.img[pixelPos].b) & (0x01 << 1);
                break;
        }
    return 0;
}


int main(int argc, char** argv)
{
    Img pic;
    int cor = 0 ;
    int pixelPos = 0 ;




    if(argc < 2) {
        printf("loader [img]\n");
        exit(1);
    }

    load(argv[1], &pic);

    char* frase  = argv[2];
    encript(frase, 0, 0);

    unsigned char w;
    unsigned char ww;
    int a=0;
    int b=0;
    int tam=strlen(frase);
   // int tam=1;
    printf("Bits de cada palavra:\n");
    while(a<=tam){



        printf("%c",frase[a]);
        printf("%s"," -> ");
        for(b = 7; 0 <= b; b--){
                printf("%d",(frase[a] >> b) & 0x01);
            }
            printf("\n");
        for(b = 7; 0 <= b; b-=2){
             w = ((frase[a] >> b) & 0x01); //pega o bit na posicao b e faz um AND com o bit 1 retorna um se
                                                      //forem iguais ou seja se b for 1 e retorna 0 se forem diferentes
                                                      //ou seja quando b for zero

             ww = (frase[a] >> b-1) & 0x01;
             printf("\n");
             printf("%s%d","Valor de W: ",w);
             printf("\n");
             printf("%s%d","Valor de WW: ",ww);
             printf("\n");
            if (cor >= 3){
                pixelPos ++;
                cor=0;
            }

            printf("%s%d%s%d\n","COR ",cor,"  PIXEL ",pixelPos);
            printf("%s\n","antes : ");
            for(int d = 7; 0 <= d; d--){
                printf("%d",(pic.img[pixelPos].r >> d) & 0x01);
            }
            printf("\n");
            for(int r = 7; 0 <= r; r--){
                printf("%d",(pic.img[pixelPos].g >> r) & 0x01);
            }
            printf("\n");
            for(int g = 7; 0 <= g; g--){
                printf("%d",(pic.img[pixelPos].b >> g) & 0x01);
            }
            printf("\n");


            gravaBitPalavra(cor,pixelPos,pic, w, ww);
            cor ++;

            printf("%s\n","depois: ");

            for(int h = 7; 0 <= h; h--){
                printf("%d",(pic.img[pixelPos].r >> h) & 0x01);
            }
            printf("\n");
            for(int n = 7; 0 <= n; n--){
                printf("%d",(pic.img[pixelPos].g >> n) & 0x01);
            }
            printf("\n");
            for(int m = 7; 0 <= m; m--){
                printf("%d",(pic.img[pixelPos].b >> m) & 0x01);
            }

        }
        printf("\n");
        printf("%s\n","FIM");
        a++;
    }

    //grava o char final para marcar o final da mensagem gravada na imagem
    for(int aa = 7; 0 <= aa; aa--){
            printf("%d",(FINALCHAR >> aa) & 0x01);
    }
    for(b = 7; 0 <= b; b-=2){
        if (cor >= 3){
            pixelPos ++;
            cor=0;
        }
        w = (FINALCHAR >> b) & 0x01;
        ww = (FINALCHAR >> b-1) & 0x01;
        gravaBitPalavra(cor,pixelPos,pic, w, ww);
        cor ++;
    }







    printf("\n");
    SOIL_save_image("saida.bmp", SOIL_SAVE_TYPE_BMP, pic.width,
                    pic.height, 3, pic.img);
    free(pic.img);
}




