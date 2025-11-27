#ifndef mergesort_h
#define mergesort_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Arquivo .h relacionado ao merge sort, que utiliza tambem o insertion sort quando o array for menor que um parametro 'i'
*/

typedef int (*comparador_merge)(const void* a, const void* b);

/// @brief Ordena um vetor usando o merge sort e utliza o insertion sort para vetores pequenos
/// @param inicio Ponteiro para o inicio do array
/// @param tam O tamanho do array 
/// @param size Tamanho de cada elemento
/// @param cmp Funcao de comparacao
/// @param param_qsort Parametro que indica qual o tamanho maximo do array para comecar atulizar o quick sort
void merge_sort(void *inicio, size_t tam, size_t size, comparador_merge cmp, int param_insertionsort);

#endif