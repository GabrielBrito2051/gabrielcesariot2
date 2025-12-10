#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formas.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "criarSvg.h"

struct pacote{
    Forma forma;
    tipoforma tipo;
};

Pacote criarPacote(){
    Pacote pac = malloc(sizeof(struct pacote));
    return pac;
}

tipoforma getTipoForma(Pacote pac){
   return  pac->tipo;
}

Forma getFORMApacote(Pacote pac){
    return pac->forma;
}

int getIDforma(Forma f, tipoforma tipo){
    if(tipo==CIRCULO){
        return getIDcirculo(f);
    }
    else if(tipo==RETANGULO){
        return getIDretangulo(f);
    }
    else if(tipo==LINHA){
        return getIDlinha(f);
    }
    else{
        return getIDtexto(f);
    }
}

void setTipoForma(Pacote pac, char tipo){
    if(tipo=='c'){
        pac->tipo = CIRCULO;
    }
    else if(tipo=='r'){ 
        pac->tipo = RETANGULO;
    }
    else if(tipo=='l'){
        pac->tipo = LINHA;
    }
    else{
        pac->tipo = TEXTO;
    }
}

void setFormaPacote(Pacote pac, Forma forma){
    pac->forma = forma;
}

int compara_forma(int id, Forma p){
    Pacote pac = (Pacote) p;
    Forma f = pac->forma;
    tipoforma tipo = pac->tipo;
   return ( getIDforma(f,tipo)==id) ? 1:0;
}

void destruirFormaPacote(Pacote pac){
    if(pac->tipo==CIRCULO){
        freeCORBcirculo(pac->forma);
        freeCORPcirculo(pac->forma);
    }
    else if(pac->tipo==RETANGULO){
        freeCORBretangulo(pac->forma);
        freeCORPretangulo(pac->forma);
    }
    else if(pac->tipo==LINHA){
        freeCORBlinha(pac->forma);
        freeCORPlinha(pac->forma);
    }
    else{
        freeCORBtexto(pac->forma);
        freeCORPtexto(pac->forma);
        freeTXTOtexto(pac->forma);
    }
    free(pac->forma);
}

void freePacote(Pacote pac){
    destruirFormaPacote(pac);
    free(pac);
}

void getSegmentoLinha(Forma f, tipoforma tipo, double* x1, double*y1, double *x2, double* y2, char orient){
    if(tipo == LINHA){
        *x1 = getX1linha(f);
        *y1 = getY1linha(f);
        *x2 = getX2linha(f);
        *y2 = getY2linha(f);
    }
    else if(tipo==TEXTO){
        double xt = getXtexto(f);
        double yt = getYtexto(f);
        char ancora = getAtexto(f);
        const char* conteudo = getTXTOtexto(f);
        int tamanho = strlen(conteudo);

        *y1 = yt;
        *y2 = yt;

        if(ancora == 'i'){
            *x1 = xt;
            *x2 = xt + 10.0 * tamanho;
        }
        
        else if(ancora == 'f'){
            *x1 = xt - 10.0 * tamanho;
            *x2 = xt;
        }

        else if(ancora == 'm'){
            *x1 = xt - 5*tamanho;
            *x2 = xt + 5*tamanho;
        }
    }
    else if(tipo==CIRCULO){
        if(orient == 'v'){
            *x1 = getXcirculo(f);
            *y1 = getYcirculo(f) - getRcirculo(f);
            *x2 = getXcirculo(f);
            *y2 = getYcirculo(f) + getRcirculo(f);
        }else if(orient =='h'){
            *x1 = getXcirculo(f) - getRcirculo(f);
            *y1 = getYcirculo(f);
            *x2 = getXcirculo(f) + getRcirculo(f);
            *y2 = getYcirculo(f);
        }
    }
}

void getSegmentoRetangulo(Forma f, double* x1, double* y1, double* x2, double* y2, int func){
    if(func==1){
        *x1 = getXretangulo(f);
        *y1 = getYretangulo(f);
        *x2 = getXretangulo(f) + getWretangulo(f);
        *y2 = getYretangulo(f);
    }
    else if(func==2){
        *x1 = getXretangulo(f);
        *y1 = getYretangulo(f) + getHretangulo(f);
        *x2 = getXretangulo(f) + getWretangulo(f);
        *y2 = getYretangulo(f) + getHretangulo(f);
    }
    else if(func==3){
        *x1 = getXretangulo(f);
        *y1 = getYretangulo(f);
        *x2 = getXretangulo(f);
        *y2 = getYretangulo(f) + getHretangulo(f);
    }
    else if(func==4){
        *x1 = getXretangulo(f) + getWretangulo(f);
        *y1 = getYretangulo(f);
        *x2 = getXretangulo(f) + getWretangulo(f);
        *y2 = getYretangulo(f) + getHretangulo(f);
    }
}

char* getCORBforma(Pacote pac){
    Pacote var = (Pacote) pac;
    tipoforma tipo = var->tipo;
    if(tipo==CIRCULO){
        return getCORBcirculo(var->forma);
    }
    else if(tipo==LINHA){
        return getCORBlinha(var->forma);
    }
    else if(tipo==TEXTO){
        return getCORBtexto(var->forma);
    }
    return NULL;
}

void setCORBforma(Forma f, tipoforma tipo, char* corb){
    if(tipo == CIRCULO){
        setCORBcirculo(f, corb);
    }
    else if(tipo==RETANGULO){
        setCORBretangulo(f, corb);
    }
    else if(tipo==LINHA){
        setCORBlinha(f, corb);
    }
    else if(tipo==TEXTO){
        setCORBtexto(f,corb);
    }
}

Pacote clonarForma(Forma f, tipoforma tipo, double dx, double dy, int maior_id){
    int id = maior_id;
    double x, y;
    char* corb, *corp;
    Forma clone = NULL;
    if(tipo==CIRCULO){
        x = getXcirculo(f);
        y = getYcirculo(f);
        double r = getRcirculo(f);
        corb = getCORBcirculo(f);
        corp = getCORPcirculo(f);
        clone = criar_circulo(id, x+dx, y+dy, r, corb, corp);
    }
    else if(tipo==RETANGULO){
        x = getXretangulo(f);
        y = getYretangulo(f);
        double w = getWretangulo(f), h = getHretangulo(f);
        corb = getCORBretangulo(f);
        corp = getCORPretangulo(f);
        clone = criar_retangulo(id, x+dx, y+dy, w, h, corb, corp);
    }
    else if(tipo==LINHA){
        x = getX1linha(f);
        y = getY1linha(f);
        double x2 = getX2linha(f), y2 = getY2linha(f);
        corb = getCORBlinha(f);
        clone = criar_linha(id, x+dx, y+dy, x2+dx, y2+dy, corb);
    }
    else if(tipo==TEXTO){
        x = getXtexto(f);
        y = getYtexto(f);
        corb = getCORBtexto(f);
        corp = getCORPtexto(f);
        char a = getAtexto(f);
        char* txto = getTXTOtexto(f);
        clone = criar_texto(id, x+dx, y+dy, corb, corp, a, txto);
    }
    return clone;
}

void printSVGforma(FILE* svg, tipoforma tipo, Forma f, Estilo ts){
    if(tipo==CIRCULO){
        insere_circulo_svg(svg, f);
    }
    else if(tipo==RETANGULO){
        insere_retangulo_svg(svg, f);
    }
    else if(tipo==LINHA){
        insere_linha_svg(svg, f);
    }
    else{
        insere_texto_svg(svg, f, ts);
    }
}