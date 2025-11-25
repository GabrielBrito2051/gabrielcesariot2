#ifndef poligono_h
#define poligono_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"
#include "geometria.h"

typedef void* Poligono;
typedef void* Ponto;

/// @brief Cria um novo poligono
/// @return Retorna o ponteiro para o poligono
Poligono criar_poligono();

/// @brief Insere um ponto no poligono
/// @param p O poligono
/// @param x A coordenada x do ponto
/// @param y A coordenada y do ponto
/// @return Retorna o ponteiro para o poligono
Poligono inserir_ponto(Poligono p, double x, double y);

/// @brief Libera a memoria do poligono
/// @param p O poligono
void free_poligono(Poligono p);

/// @brief Verifica se um ponto pertence ao poligono
/// @param p O poligono
/// @param x A coordenada x do ponto
/// @param y A coordenada y do ponto
/// @return Retorna true se o ponto faz parte do poligono e false caso contrario
bool contem_ponto(Poligono p,double x, double y);

/// @brief Verifica se um segmento intercepta qualquer aresta do poligono
/// @param p O poligono
/// @param x1 A coordenada x do inicio do segmento
/// @param y1 A coordenada y do inicio do segmento
/// @param x2 A coordenada x do fim do segmento
/// @param y2 A coordenada y do fim do segmento
/// @return Retorna true se o segmento intercepta o poligono e false caso contrario
bool intercepta_seg(Poligono p, double x1, double y1, double x2, double y2);

/// @brief Libera a memoria de um ponto
/// @param p O ponto
void free_ponto(Ponto p);

/// @brief Imprime o poligono criado pela regiao de visibilidade no arquivo svg
/// @param svg Ponteiro para o arquivo svg
/// @param p O poligono
/// @param corp A cor de preenchimento
/// @param opacity A opacidade
void print_poligono_svg(FILE* svg, Poligono p, char* corp, double opacity);

#endif