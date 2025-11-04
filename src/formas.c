#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        return getIcirculo(f);
    }
    else if(tipo==RETANGULO){
        return getIretangulo(f);
    }
    else if(tipo==LINHA){
        return getIlinha(f);
    }
    else{
        return getItexto(f);
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

void destruirFormaPacote(Pacote pac){

    if(pac->tipo==LINHA){
        freeCorbCir(pac->forma);
        freeCorpCir(pac->forma);
    }
    else if(pac->tipo==LINHA){
        freeCorbRet(pac->forma);
        freeCorpRet(pac->forma);
    }
    else if(pac->tipo==LINHA){
        freeCorbLinha(pac->forma);
        freeCorpLinha(pac->forma);
    }
    else{
        freeCorpTexto(pac->forma);
        freeCorbTexto(pac->forma);
        freeTXTOtexto(pac->forma);
    }
    free(pac->forma);
}

void freePacote(Pacote pac){
    destruirFormaPacote(pac);
    free(pac);
}