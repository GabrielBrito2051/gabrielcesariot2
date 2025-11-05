#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "formas.h"

typedef struct ELEMENTO{
    Forma forma;
    struct ELEMENTO* ante;
    struct ELEMENTO* prox;
}elemento;

typedef elemento* pont;

typedef struct{
    pont inicio;
    pont fim;
    int tamanho;
}lista;

Lista criar_lista(){
    lista* l = malloc(sizeof(lista));
    l->inicio=NULL;
    l->fim=NULL;
    l->tamanho=0;

    return l;
}

int getTAMANHOlista(Lista l){
    return ((lista*)l)->tamanho;
}

void insere_lista(Lista l, Forma forma){
    lista* var = (lista*)l;
    pont novo = malloc(sizeof(elemento));
    if(novo==NULL){
        printf("Erro ao alocar memoria para um novo elemento da lista");
        exit(1);
    }

    novo->forma = forma;
    novo->prox = NULL;
    if(var->inicio==NULL){
        var->inicio = novo;
        novo->ante = NULL;
    }else{
        var->fim->prox = novo;
        novo->ante = var->fim;
    }
    var->fim = novo;
    var->tamanho++;
}

void remove_lista(Lista l, Forma forma){
    lista* var = (lista*)l;

}

Forma get_inicio_lista(Lista l){
    return ((lista*)l)->inicio->forma;
}

Forma get_final_lista(Lista l){
    return ((lista*)l)->fim->forma;
}