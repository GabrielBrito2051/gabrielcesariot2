#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "texto.h"

void print_info(Texto f, Estilo ts){
    printf("ID:%d, X;%lf, Y:%lf, A:%c, corb:%s, corp:%s, texto:%s\n",getIDtexto(f),getXtexto(f),getYtexto(f),getAtexto(f),getCORBtexto(f),getCORPtexto(f),getTXTOtexto(f));
    printf("FAMILY:%s, WEIGHT:%s, SIZE:%s\n",getFAMILY(ts),getWEIGHT(ts),getSIZE(ts));
}

int main()
{

    int id = 1;
    double x = 10, y = 15;
    char a = 'm';
    char *corb = malloc(8*sizeof(char)), *corp = malloc(8 *sizeof(char)), *txto = malloc(15*sizeof(char));
    if(corb==NULL || corp==NULL||txto==NULL){
        printf("Erro ao alocar memoria para as cores");
        return 1;
    }
    strcpy(corb,"#FFFFFF");
    strcpy(corp,"#123456");
    strcpy(txto,"testeMaluco");

    Texto f = criar_texto(id,x,y,corb,corp,a,txto);
    Estilo ts = criar_estilo("sans", "n", "12");

    print_info(f,ts);
    setXtexto(f, 11);
    setYtexto(f, 22);
    setCORBtexto(f, "#123456");
    setCORPtexto(f, "#FFFFFF");

    setFAMILY(ts,"cursive");
    setWEIGHT(ts,"b");
    setSIZE(ts,"22");

    print_info(f,ts);

 return 0;
}