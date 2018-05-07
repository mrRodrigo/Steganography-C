#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// Para usar strings
#include <errno.h>   // para errno
#include <limits.h>  // para o max int

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
void load(char* name, Img* pic);  //responsavel por ler uma imagem
void gravaBitPalavra(int cor,int pixelPos,Img pic, unsigned char w,  unsigned char ww); // Grava dois bits (W e WW) no final de uma cor de um pixel
char encript(char* texto, int chave, int tipo); //Encripta um texto utilizando a Cifra de César
void steganography (Img pic, char* frase); //Metodo inicial de esteganografia
void undoGraphy (Img pic, int chave); //Metodo inicial para desvendar alguma esteganografia
int  getBit (int cor,int pixelPos,Img pic, int position); //retorna um bit de um pixel em uma determinada posição 



char encript(char* texto, int chave, int tipo) // tipo = 0 cifrar 
                                               // tipo = 1  decifrar
{
    int tam=strlen(texto); 
    int i=0; 
    int cont=0; 
    char letra; 
    printf("Mensagem : %s\n",texto);
    for (letra='a'; letra<='z'; letra++) {
            while(i<=tam){
                    if(texto[i] == letra){
                          //Condição para cifrar/decifrar o texto/codigo
                            if(tipo == 0)
                                texto[i] = letra+chave;

                            else if (tipo == 1)
                                texto[i] = letra-chave;

                            i++;
                            cont ++;
                            letra='a';

                        }

                    else if(texto[i] == ' '){
                            i++;
                            cont ++;
                            letra='a';
                        }

                    else if(texto[i] == toupper(letra)){

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

                    if(cont == tam){
                        break;
                    }
                    if(texto[i] == FINALCHAR){
                        break;
                    }
                }
        }

    if(tipo == 0)
        return printf("Mensagem cifrada com chave %d : %s\n",chave,texto);
    else
        return printf("Mensagem decifrada: %s\n",texto);
}




void load(char* name, Img* pic){
    int chan;
    pic->img = (unsigned char*) SOIL_load_image(name, &pic->width, &pic->height, &chan, SOIL_LOAD_RGB);
    if(!pic->img)
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        exit(1);
    }
    printf("Imagem carregada: %d x %d x %d %s\n", pic->width, pic->height, chan,name);
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


void steganography (Img pic, char* frase){
    int cor = 0 ;
    int pixelPos = 0 ;
    unsigned char w;
    unsigned char ww;
    int a=0;
    int b=0;
    int tam=strlen(frase);
    printf("Iniciando...\n");
    while(a<=tam){
        for(b = 7; 0 <= b; b-=2){
             w = ((frase[a] >> b) & 0x01);

             ww = (frase[a] >> b-1) & 0x01;

            if (cor >= 3){
                pixelPos ++;
                cor=0;
            }
            gravaBitPalavra(cor,pixelPos,pic, w, ww);
            cor ++;
        }
        a++;
    }
    //Grava o char final para marcar o final da mensagem gravada na imagem
    printf("%s\n","Gravando simbolo final...");
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

int getBit (int cor,int pixelPos,Img pic, int position){
    int bit =0;
  switch (cor){
            case 0:
                bit = (pic.img[pixelPos].r >> position) & 0x01;
                break;
            case 1:
                bit = (pic.img[pixelPos].g >> position) & 0x01;
                break;
            case 2:
                bit = (pic.img[pixelPos].b >> position) & 0x01;
                break;
        }
        return bit;
}

void undoGraphy (Img pic, int chave){
    unsigned char frase[300];
    unsigned char ch;
    int cor= 0;
    int pixelPos=0;
    for (int a=0;  a<pic.height * pic.width; a++){
        ch = 0x00;
        for(int b = 7; 0 <= b; b-=2){
                if (cor >= 3){
                    pixelPos ++;
                    cor=0;
                }
                 ch ^= (-(getBit( cor,pixelPos,pic,1)) ^ ch) & (0x01 << b);
                 ch ^= (-(getBit( cor,pixelPos,pic,0)) ^ ch) & (0x01 << b - 1);
                 cor ++;
            }
            if (ch == FINALCHAR){
                frase[a] = ch;
                break;
            }
            frase[a] = ch;
    }
    encript(frase,chave, 1);

}

int main(int argc, char** argv)
{
    Img pic;
    char* p;

    if(argc < 2) {
        printf("loader ERRO [img]\n");
        exit(1);
    }
    load(argv[1], &pic);
    int chave = strtol(argv[3], &p, 10);

    if (errno != 0 || *p != '\0' || chave > INT_MAX) {
            printf("%s", "ERRO: Chave deve ser um numero inteiro.");
            return 0;
    }

    if (strcmp(argv[2], "-hide") == 0){
        char* frase  = argv[4];

        encript(frase, chave, 0);
        steganography(pic,frase);

    }else{
        if (strcmp(argv[2], "-reveal") == 0){
            undoGraphy (pic, chave);
        }else{
            printf("%s", "ERRO: Argumento 2 não reconhecido use -hide ou -reveal.");
        }
    }

}



