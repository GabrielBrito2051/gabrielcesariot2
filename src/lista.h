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
/// @param forma O elemento que sera inserido na lista
void insere_lista(Lista l, Forma forma);

/// @brief Remove um elemento da lista
/// @param l A lista
/// @param compara_formas Ponteiro para a funcao que compara elementos de um tipo especifico
/// @param id O id da forma que sera removida
///@return Retorna um ponteiro para a forma que foi removida
Pacote remove_lista(Lista l, int(*compara_formas)(int id, Pacote forma),int id);

/// @brief Pega o primeiro elemento da lista
/// @param l A lista
/// @return Retorna um ponteiro com o primeiro elemento
Pacote get_inicio_lista(Lista l);

/// @brief Pega o ultimo elemnto da lista
/// @param l A lista
/// @return Retorna um ponteiro com o ultimo elemento
Pacote get_final_lista(Lista l);

/// @brief Libera a memoria de uma lista
/// @param l A lista
void destroiLista(Lista l);

#endif