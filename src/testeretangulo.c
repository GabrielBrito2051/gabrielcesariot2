#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retangulo.h"

void print_info(Retangulo f){
    printf("ID:%d, X;%lf, Y:%lf, W:%lf, H:%lf, corb:%s, corp:%s\n",getIDretangulo(f),getXretangulo(f),getYretangulo(f),getWretangulo(f),getHretangulo(f),getCORBretangulo(f),getCORPretangulo(f));
}

int main()
{

    int id = 1;
    double x = 10, y = 15, w = 5, h=6;
    char *corb = malloc(8*sizeof(char)), *corp = malloc(8 *sizeof(char));
    if(corb==NULL || corp==NULL){
        printf("Erro ao alocar memoria para as cores");
        return 1;
    }
    strcpy(corb,"#FFFFFF");
    strcpy(corp,"#123456");

    Retangulo f = criar_retangulo(id,x,y,w,h,corb,corp);

    print_info(f);
    setXretangulo(f, 11);
    setYretangulo(f, 22);
    setCORBretangulo(f, "#123456");
    setCORPretangulo(f, "#FFFFFF");

    print_info(f);

 return 0;
}