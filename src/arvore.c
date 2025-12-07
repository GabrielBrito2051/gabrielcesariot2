#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "linha.h"
#include "geometria.h"

typedef struct ELEMENTO{
    Segmento seg;
    struct ELEMENTO* esq;
    struct ELEMENTO* dir;
}elemento;

typedef elemento* pont;

typedef struct{
    pont raiz;
    comparador cmp;
}arvore;

static double menor_distg;
static Segmento vg;
static double b_x, b_y, v_x, v_y;

pont criar_no(Segmento seg){
    pont novo = (pont)malloc(sizeof(elemento));
    if(novo==NULL){
        return NULL;
    }
    novo->seg = seg;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

pont inserir_recursivo(pont raiz, Segmento seg, comparador cmp){
    if(raiz==NULL) return criar_no(seg);
    
    int compara = cmp(seg,raiz->seg);
    if(compara<0){
        raiz->esq = inserir_recursivo(raiz->esq,seg,cmp);
    }
    else if(compara>0){
        raiz->dir = inserir_recursivo(raiz->dir,seg,cmp);
    }
    return raiz;
}

pont menor_no(pont raiz){
    pont atual = raiz;
    while(atual && atual->esq != NULL){
        atual = atual->esq;
    }
    return atual;
}

pont remover_recursivo(pont raiz, Segmento seg, comparador cmp, void** seg_removido){
    if(raiz == NULL)return NULL;

    int compara = cmp(seg,raiz->seg);

    if(compara<0){
        raiz->esq = remover_recursivo(raiz->esq, seg, cmp, seg_removido);
    }
    else if(compara>0){
        raiz->dir = remover_recursivo(raiz->dir,seg,cmp,seg_removido);
    }else{
        if(seg_removido!=NULL){
            *seg_removido = raiz->seg;
        }
        if(raiz->esq==NULL){
            pont temp = raiz->dir;
            free(raiz);
            return temp;
        }
        else if(raiz->dir==NULL){
            pont temp = raiz->esq;
            free(raiz);
            return temp;
        }

        pont temp =menor_no(raiz->dir);
        raiz->seg = temp->seg;
        raiz->dir = remover_recursivo(raiz->dir, temp->seg, cmp, NULL);
    }
    return raiz;
}

void liberar_recursivo(pont raiz){
    if(raiz!=NULL){
        liberar_recursivo(raiz->esq);
        liberar_recursivo(raiz->dir);
        free(raiz);
    }
}

void visita_e_compara(pont raiz){
    if(raiz==NULL)return;
    Segmento s = raiz->seg;
    if(s!=NULL){
        double x1 = getX1linha(s);
        double y1 = getY1linha(s);
        double x2 = getX2linha(s);
        double y2 = getY2linha(s);

        double dist = distancia_raio(b_x, b_y, v_x, v_y, x1, y1, x2, y2);
        if(dist<menor_distg){
            menor_distg = dist;
            vg = s;
        }
    }
    visita_e_compara(raiz->esq);
    visita_e_compara(raiz->dir);
}

Arvore criar_arvore(comparador f){
    arvore* a = malloc(sizeof(arvore));
    if(a==NULL){
        return NULL;
    }
    a->raiz = NULL;
    a->cmp = f;
    return a;
}

void insere_arvore(Arvore a, Segmento seg){
    if(a==NULL) return;
    arvore* arv = (arvore*) a;
    arv->raiz = inserir_recursivo(arv->raiz, seg, arv->cmp);
}

Segmento remove_arvore(Arvore a, Segmento seg){
    if(a==NULL) return NULL;
    arvore* arv = (arvore*) a;
    Segmento seg_removido = NULL;
    arv->raiz = remover_recursivo(arv->raiz,seg,arv->cmp,&seg_removido);
    return seg_removido;
}

Segmento busca_mais_proximo(Arvore a, double bx, double by, double vx, double vy){
    if(a==NULL) return NULL;
    arvore* arv = (arvore*)a;
    if(arv->raiz==NULL) return NULL;

    menor_distg = 99999999.0;
    vg = NULL;
    b_x = bx;
    b_y = by;
    v_x = vx;
    v_y = vy;

    visita_e_compara(arv->raiz);

    return vg;
}



void destroi_arvore(Arvore a){
    arvore* arv = (arvore*)a;
    liberar_recursivo(arv->raiz);
    free(arv);
}