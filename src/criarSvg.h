#ifndef criarSvg_h
#define criarSvg_h

#include <stdio.h>
#include <stdlib.h>
#include "formas.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

/*
    Arquivo que gerencia a criacao do arquivo svg
*/

/// @brief Adiciona a tag inicial do arquivo svg
/// @param svg Poneitro para o arquivo svg
void startSVG(FILE* svg);

/// @brief Adiciona a tag circulo do arquivo svg
/// @param svg Ponteiro para o arquivo svg
/// @param c Forma do circulo
void insere_circulo_svg(FILE *svg, Circulo c);

/// @brief Adiciona a tag retangulo do arquivo svg
/// @param svg Ponteiro para o arquivo svg
/// @param r Forma do retangulo
void insere_retangulo_svg(FILE *svg, Retangulo r);

/// @brief Adiciona a tag linha do arquivo svg
/// @param svg Ponteiro para o arquivo svg
/// @param l Forma da linha
void insere_linha_svg(FILE* svg, void* l);

/// @brief Adiciona a tag texto do arquivo svg
/// @param svg Ponteiro para o arquivo svg
/// @param t Forma do texto
void insere_texto_svg(FILE* svg, Texto t, Estilo ts);

/// @brief Adiciona a tag da bomba (ponto) no arquivo svg
/// @param svg O arquivo svg
/// @param x A coordenada x da bomba
/// @param y A coordenada y da bomba
void insere_bomba_svg(FILE* svg, double x, double y);

/// @brief Adiciona a tag final do arquivo svg
/// @param svg Ponteiro para o arquivo svg
void fechasvg(FILE* svg);

#endif