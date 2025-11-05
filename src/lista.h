#ifndef lista_h
#define lista_h
#include <stdio.h>
#include <stdlib.h>
#include "formas.h"

typedef void* Lista;

/*
    Arquivo .h relacionado a uma lista, contendo funcoes de criar uma lista, pegar o tamanho, inserir da lista, remover de lista
    e liberar a memoria da lista
*/

/// @brief Cria uma nova lista vazia
/// @return Retorna o ponteiro para a lista criada
Lista criar_lista();

/// @brief Pega o tamanho da lista
/// @param l A lista
/// @return Retorna o tamanho da lista l
int getTAMANHOlista(Lista l);

/// @brief Insere um elemento no final da lista
/// @param l A lista
/// @param pac O elemento que sera inserido na lista
void insere_lista(Lista l, Forma forma);

/// @brief Remove um elemento da lista
/// @param l A lista
/// @param pac O elemento que sera removido
void remove_lista(Lista l, Forma forma);

/// @brief Pega o primeiro elemento da lista
/// @param l A lista
/// @return Retorna um ponteiro com o primeiro elemento
Forma get_inicio_lista(Lista l);

/// @brief Pega o ultimo elemnto da lista
/// @param l A lista
/// @return Retorna um ponteiro com o ultimo elemento
Forma get_final_lista(Lista l);

#endif