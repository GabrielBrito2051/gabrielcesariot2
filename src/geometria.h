#ifndef geometria_h
#define geometria_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

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

/// @brief Calcula a orientacao de um ponto em relacao a um segmento
/// @param ax A coordenada x de inicio do segmento
/// @param ay A coordenada y de inicio do segmento
/// @param bx A coordenada x do fim do segmento
/// @param by A coordenada y do fim do segmento
/// @param px A coordenada x do ponto(bomba)
/// @param py A coordenada y do ponto(bomba)
/// @return Retorna um valor maior que zero caso o ponto esteja a esquerda do segmento, um valor menor que zerocaso esteja a direita e zero se estiver alinhado com o segmento
double calcula_orientacao(double ax, double ay, double bx, double by, double px, double py);

/// @brief Verifica se ha a interseccao entre dois segmentos e, se houver, mostra em qual posicao ocorre
/// @param ax A coordenada x do inicio do segmento 1
/// @param ay A coordenada y do inicio do segmento 1
/// @param bx A coordenada x do fim do segmento 1
/// @param by A coordenada y do fim do segmento 1
/// @param cx A coordenada x do inicio do segmento 2
/// @param cy A coordenada y do inicio do segmento 2
/// @param ex A coordenada x do fim do segmento 2
/// @param ey A coordenada y do fim do segmento 2
/// @param ix Valor passado por referencia para armazenar a coordenada x da inteseccao dos segmentos
/// @param iy Valor passado por referencia para armazenar a coordenada y da inteseccao dos segmentos
/// @return Retorna true caso ocorra a interseccao dos segmentos e false caso contrario
bool interseccao_segmentos(double ax, double ay, double bx, double by, double cx, double cy, double ex, double ey, double* ix, double* iy);

/// @brief Calcula a distancia de um vertice a bomba
/// @param bx Coordenada x da bomba
/// @param by Coordenada y da bomba
/// @param vx Coordenada x do vertice atual
/// @param vy Coordenada y do vertice atual
/// @param p1x Coordenada x do inicio do segmento que ja esta na arvore
/// @param p1y Coordenada y do inicio do segmento que ja esta na arvore
/// @param p2x Coordenada x do fim do segmento que ja esta na arvore
/// @param p2y Coordenada y do fim do segmento que ja esta na arvore
/// @return Retorna a distancia da bomba ao vertice
double distancia_raio(double bx, double by, double vx, double vy, double p1x, double p1y, double p2x, double p2y);

#endif