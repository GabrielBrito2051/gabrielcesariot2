#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"

void print_info(Circulo f){
    printf("ID:%d, X;%lf, Y:%lf, R:%lf, corb:%s, corp:%s\n",getIDcirculo(f),getXcirculo(f),getYcirculo(f),getRcirculo(f),getCORBcirculo(f),getCORPcirculo(f));
}

int main()
{

    int id = 1;
    double x = 10, y = 15, r = 5;
    char *corb = malloc(8*sizeof(char)), *corp = malloc(8 *sizeof(char));
    if(corb==NULL || corp==NULL){
        printf("Erro ao alocar memoria para as cores");
        return 1;
    }
    strcpy(corb,"#FFFFFF");
    strcpy(corp,"#123456");

    Circulo f = criar_circulo(id,x,y,r,corb,corp);

    print_info(f);
    setXcirculo(f, 11);
    setYcirculo(f, 22);
    setCORBcirculo(f, "#123456");
    setCORPcirculo(f, "#FFFFFF");

    print_info(f);

 return 0;
}