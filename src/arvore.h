#ifndef arvore_h
#define arvore_h

#include <stdio.h>
#include <stdlib.h>

typedef void* Arvore;
typedef void* Segmento;
typedef int (*comparador)(  void* a, void*b);

/*
    Arquivo .h relacionado a estrutura de uma arvore binaria, com funcoes de criar, inserir, remover e buscar.
*/

/// @brief Cria uma nova arvore binaria
/// @param f Ponteiro para a funcao que compara os segmentos
/// @return Retorna o ponteiro para a arvore criada
Arvore criar_arvore(comparador f);

/// @brief Insere um elemento na arvore binaria
/// @param a A arvore onde sera inserido o elemento
/// @param s O segmento que sera inserido na arvore
void insere_arvore(Arvore a, Segmento s);

/// @brief Remove um elemento da arvore binaria
/// @param a A arvore que tera um elemento removido
/// @param s O segmento que sera removido da arvore
Segmento remove_arvore(Arvore a, Segmento s);

/// @brief Busca o segmento mais proximo da bomba
/// @param a A arvore de segmentos ativos
/// @param bx A coordenada x da bomba
/// @param by A coordenada y da bomba
/// @param vx A coordenada x do vertice
/// @param vy A coordenada y do vertice
/// @return Retorna o ponteiro para o biombo mais proximo da bomba
Segmento busca_mais_proximo(Arvore a, double bx, double by, double vx, double vy);

/// @brief Libera a memoria da arvore
/// @param a A arvore que tera sua memoria liberada
void destroi_arvore(Arvore a);

#endif