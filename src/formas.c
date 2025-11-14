#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formas.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

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

int compara_forma(int id,Pacote pac){
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