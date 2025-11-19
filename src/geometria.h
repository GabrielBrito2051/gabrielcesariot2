#ifndef geometria_h
#define geometria_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef void* Segmento;

/*
    Arquivo .h relacionado as funcoes de geometria, com funcoes de comparar segmentos, calcular produtos vetoriais, distancia entre
    dois pontos e angulacao
*/

/// @brief Calcula a distancia entre dois pontos no plano euclidiano
/// @param x1 Coordenada x do ponto 1
/// @param y1 Coordenada y do ponto 1
/// @param x2 Coordenada x do ponto 2
/// @param y2 Coordenada y do ponto 2
/// @return Retorna distancia entre os pontos 1 e 2
double calcula_distancia_pontos(double x1, double y1, double x2, double y2);

/// @brief Calcula o valor maximo entre dois reais
/// @param a O primeiro valor
/// @param b O segundo valor
/// @return Retorna o valor maximo entre 'a' e 'b'
double max(double a, double b);

/// @brief Calcula o valor minimo entre dois numeros reais
/// @param a O primeiro valor
/// @param b O segundo valor
/// @return Retorna o minimo entre os valores 'a' e 'b'
double min(double a, double b);

/// @brief Calcula o angulo em radianos de um ponto em relacao a bomba
/// @param cx A coordenada x da bomba
/// @param cy A coordenada y da bomba
/// @param x Coordenada x do vertice
/// @param y Coordenada y do vertice
/// @return Retorna o valor do angulo em radianos entre a bomba e o vertice
double calcula_angulo(double cx, double cy, double x, double y);


double calcula_orientacao(double ax, double ay, double bx, double by, double px, double py);


int interseccao_segmentos(double ax, double ay, double bx, double by, double cx, double cy, double dx, double dy, double* ix, double* iy);


double distancia_raio(double bx, double by, double vx, double vy, double p1x, double p1y, double p2x, double p2y);

#endif