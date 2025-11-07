#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linha.h"

void print_info(Linha f){
    printf("ID:%d, X1;%lf, Y1:%lf, X2:%lf, Y2:%lf, corb:%s, corcompl:%s\n",getIDlinha(f),getX1linha(f),getY1linha(f),getX2linha(f),getY2linha(f),getCORBlinha(f),getCORCOMPLlinha(f));
}

int main()
{

    int id = 1;
    double x1 = 10, y1 = 15, x2 = 5, y2=20;
    char *corb = malloc(8*sizeof(char)), *corp = malloc(8 *sizeof(char));
    if(corb==NULL || corp==NULL){
        printf("Erro ao alocar memoria para as cores");
        return 1;
    }
    strcpy(corb,"#123456");

    Linha f = criar_linha(id,x1,y1,x2,y2,corb);

    print_info(f);
    setX1linha(f, 11);
    setY1linha(f, 22);
    setX2linha(f,32);
    setY2linha(f,18);
    setCORBlinha(f, "#1234FF");

    print_info(f);

 return 0;
}