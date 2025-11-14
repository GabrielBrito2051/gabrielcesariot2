#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "formas.h"

typedef struct ELEMENTO{
    Pacote forma;
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

Pacote remove_lista(Lista l, int (*compara_formas)(int id, Pacote forma),int id){
    lista* var = (lista*)l;
    pont atual = var->inicio;
    while(atual!=NULL){
        if(compara_formas(id, atual->forma)==1){
            if(atual->ante!=NULL){
                atual->ante->prox = atual->prox;
            }else{
                var->inicio = atual->prox;
            }
            if(atual->prox!=NULL){
                atual->prox->ante = atual->ante;
            }else{
                var->fim = atual->ante;
            }
            Forma f = atual->forma;
            free(atual);
            var->tamanho--;
            return f;
        }
        atual = atual->prox;
    }
    printf("Nenhuma forma com o id %d encontrada!\n",id);
    return NULL;
}

Pacote get_inicio_lista(Lista l){
    return ((lista*)l)->inicio->forma;
}

Pacote get_final_lista(Lista l){
    return ((lista*)l)->fim->forma;
}

void destroiLista(Lista l){
    lista* var = (lista*)l;
    if(var==NULL){
        return;
    }
    pont atual = var->inicio;
    pont apagar;
    while(atual!=NULL){
        apagar = atual;
        atual = atual->prox;
        freePacote(apagar->forma);
        free(apagar);
    }
    free(var);
}