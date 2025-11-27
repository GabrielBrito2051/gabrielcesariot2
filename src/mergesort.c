#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.h"

static void merge(char* inicio, char* temp, size_t esq, size_t meio, size_t dir, size_t tam, comparador_merge cmp){
    size_t i = esq;
    size_t j = meio+1;
    size_t k = esq;

    while (i<=meio && j<= dir){
        void* elem_i = inicio + (i*tam);
        void* elem_j = inicio + (j*tam);
        if(cmp(elem_i, elem_j)<=0){
            memcpy(temp + (k*tam), elem_i, tam);
            i++;
        }else{
            memcpy(temp+(k*tam),elem_j,tam);
            j++;
        }
        k++;
    }

    while(i<=meio){
        memcpy(temp + (k*tam), inicio + (i*tam),tam);
        i++;
        k++;
    }

    while(j<=dir){
        memcpy(temp + (k*tam), inicio + (j*tam),tam);
        j++;
        k++;
    }

    size_t tam_copia = (dir - esq +1) * tam;
    memcpy(inicio + (esq * tam), temp + (esq*tam), tam_copia);
}

static void merge_sort_recursivo(char* inicio, char* temp, size_t esq, size_t dir, size_t tam, comparador_merge cmp, size_t param_qsort){
    if((dir - esq + 1)<= param_qsort){
        qsort(inicio+(esq*tam), (dir-esq+1),tam, cmp);
        return;
    }
    if(esq<dir){
        size_t meio = esq + (dir - esq) / 2;

        merge_sort_recursivo(inicio, temp, esq, meio, tam, cmp, param_qsort);
        merge_sort_recursivo(inicio, temp, meio+1, dir, tam, cmp, param_qsort);
        merge(inicio, temp, esq, meio, dir, tam, cmp);
    }
}

void merge_sort(void* inicio, size_t tam, size_t size, comparador_merge cmp,int param_qsort){
    if(tam<2||inicio == NULL) return;
    char* temp = malloc(tam*size);
    if(temp==NULL){
        qsort(inicio, tam, size, cmp);
        return;
    }
    merge_sort_recursivo((char*)inicio, temp, 0, tam-1, size, cmp, param_qsort);
    free(temp);
}