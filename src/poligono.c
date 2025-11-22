#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "poligono.h"
#include "boundingbox.h"
#include"lista.h"
#include "geometria.h"


typedef struct{
    double x, y;
}ponto;

typedef struct{
    Lista pontos;
}poligono;

Poligono criar_poligono(){
    poligono* p = malloc(sizeof(poligono));
    if(p==NULL){
        printf("Erro ao alocar memoria para o poligono");
        return NULL;
    }
    p->pontos = criar_lista();

    return (poligono*)p;
}

Poligono inserir_ponto(Poligono p, double x, double y){
    poligono* var = (poligono*)p;
    ponto* novoponto = malloc(sizeof(ponto));
    if(novoponto==NULL){
        return;
    }
    novoponto->x = x;
    novoponto->y = y;

    insere_lista(var->pontos, novoponto);
}

void free_poligono(Poligono p){
    poligono* var = (poligono*)p;
    destroiListaPoligono(var->pontos);
    free(var);
}

void free_ponto(Ponto p){
    ponto* var = (ponto*) p;
    free(var);
}

bool contem_ponto(Poligono p,double x, double y){
    poligono* var = (poligono*) p;
    if(getTAMANHOlista(var->pontos)<3) return 0;
    bool dentro = false;
    void* atual = get_inicio_lista(var->pontos);
    ponto* p1 = get_conteudo_lista(atual);
    ponto* primeiro = p1;
    while(atual!=NULL){
        ponto* p2;
        void* prox = proximo_lista(var->pontos, atual);
        if(prox != NULL){
            p2 = get_conteudo_lista(prox);
        }else{
            p2 = primeiro;
        }
        bool dentroy = (p1->y>y) != (p2->y>y);
        if(dentroy){
            double tracox = (p2->x) * (y-p1->y) / (p2->y - p1->y) + p1->x;
            if(x<tracox){
                dentro = !dentro;
            }
        }
        p1 = p2;
        atual = prox;
    }
    return dentro;
}

bool intercepta_seg(Poligono p, double x1, double y1, double x2, double y2){
    poligono* var = (poligono*)p;
    void* atual = get_inicio_lista(var->pontos);
    ponto* primeiro = get_conteudo_lista(atual);
    ponto* inicio_aresta = primeiro;
    while(atual!=NULL){
        void* prox = proximo_lista(var->pontos,atual);
        ponto* fim_aresta;
        if(prox!=NULL){
            fim_aresta = get_conteudo_lista(prox);
        }else{
            fim_aresta = primeiro;
        }
        bool colidiu = interseccao_segmentos(x1,y1,x2,y2,inicio_aresta->x,inicio_aresta->y,fim_aresta->x,fim_aresta->y,NULL,NULL);
        if(colidiu){
            return true;
        }
        inicio_aresta = fim_aresta;
        atual = prox;
    }
    return false;
}

void print_poligono_svg(FILE* svg, Poligono p, char* corp, double opacity){
    poligono* var = (poligono*)p;
    if(var==NULL||svg==NULL) return;

    fprintf(svg,"\n<polygon points=\"");
    if(var->pontos==NULL){
        void* atual = get_inicio_lista(var->pontos);
        while(atual!=NULL){
            ponto* pt = get_conteudo_lista(atual);
            fprintf(svg,"%.2f,%.2f ", pt->x, pt->y);
            atual = proximo_lista(var->pontos,atual);
        }
    }
    fprintf(svg,"\" fill=\"%s\" fill-opacity=\"%.2f\" stroke=\"none\" />",  corp, opacity);
}
