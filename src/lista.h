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
Forma remove_lista(Lista l, int(*compara_formas)(int id, Forma forma),int id);

/// @brief Pega o primeiro elemento da lista
/// @param l A lista
/// @return Retorna um ponteiro com o primeiro elemento
Forma get_inicio_lista(Lista l);

/// @brief Pega o ultimo elemnto da lista
/// @param l A lista
/// @return Retorna um ponteiro com o ultimo elemento
Forma get_final_lista(Lista l);

/// @brief Pega o conteudo de um determinado no de uma lista
/// @param no O no
/// @return Retorna o conteudo do no
Forma get_conteudo_lista(void* no);

/// @brief Encontra o proximo item da lista
/// @param l A lista
/// @param f O item atual
/// @return Retorna o ponteiro para o proximo item
Forma proximo_lista(Lista l, Forma f);

/// @brief Busca uma forma pelo seu id
/// @param l A lista que sera buscada
/// @param compara_elemento Funcao que compara formas por id
/// @param i O id que sera comparado
/// @return Retorna a forma com o id desejado, se nao encontrar, retorna NULL
Forma busca_conteudo(Lista l, int (*compara_elemento)(int i, void* elemento), int i);

/// @brief Libera a memoria de uma lista
/// @param l A lista
void destroiListaDeFormas(Lista l);

/// @brief Libera a memoria da lista de pontos do poligono
/// @param l A lista de pontos
void destroiListaPoligono(Lista l);

/// @brief Imprime as formas de uma lista no arquivo svg
/// @param l A lista
/// @param svg Ponteiro para o arquivo svg
/// @param ts O estilo do texto
void printar_lista(Lista l, FILE* svg, Estilo ts);

/// @brief Imprime a lista de angeparos restantes no arquivo svg
/// @param l A lista de anteparos
/// @param svg Ponteiro para o arquivo svg
void printar_lista_anteparos(Lista l, FILE* svg);

/// @brief Libera a memoria da lista de anteparos
/// @param l A lista de anteparos
void destroiListaDeAnteparos(Lista l);

/// @brief Libera a memoria dos nos da lista extra de clones
/// @param l A lista de clones
void destroiListaDeClones(Lista l);

#endif