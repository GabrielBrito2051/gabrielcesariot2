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
/// @param flag Flag do comando que indica se sera utilizado o qsort ou o mergesort para ordenar na arvore
/// @param i Flag do comando que indica o tamanho maximo que o subvetor deve ter para comecar a utilizar o insertion sort
/// @return Retorna uma nova lista contendo os pares ordenados que formam o poligono de visibilidade
Poligono calcular_visibilidade(Lista listaSegmentos, double bx, double by, char flag, int i);

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