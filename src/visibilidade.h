#ifndef visibilidade_h
#define visibilidade_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "arvore.h"
#include "poligono.h"
#include "lista.h"
#include "formas.h"
#include "geometria.h"

/// @brief Calcula a regiao de visibilidade a partir de um ponto
/// @param listaSegmentos Lista contendo todos os anteparos existentes
/// @param bx Coordenada x da bomba
/// @param by Coordenada y da bomba
/// @return Retorna uma nova lista contendo os pares ordenados que formam o poligono de visibilidade
Lista calcular_visibilidade(Lista listaSegmentos, double bx, double by);

/// @brief Verifica se uma determinada forma esta dentro da regiao de visibilidade
/// @param poligono A lista de pares ordenados do poligono
/// @param forma A forma que sera verificada se foi atingida
/// @param tipo O tipo da forma
/// @return Retorna 1 caso a forma tenha sido atingida e 0 caso contrario
int atinge_forma(Poligono poligono, Forma forma, tipoforma tipo);

/// @brief Verifica se um ponto esta dentro da regiao de visibilidade
/// @param poligono O poligono formado pela regiao de visibilidade
/// @param x A coordenada x do ponto
/// @param y A coordenada y do potno
/// @return Retorna 1 se o ponto estiver dentro do poligono e 0 caso contrario
int ponto_na_regiao(Poligono poligono, double x, double y);

#endif