#ifndef geo_h
#define geo_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formas.h"
#include "texto.h"
#include "linha.h"
#include "circulo.h"
#include "retangulo.h"
#include "lista.h"
#include "ler_arquivo.h"

/*
    Arquivo .h relacionado a leitura do arquivo .geo, com uma funcao que le o arquivo e insere as formas na lista
*/

/// @brief Le o arquivo geo
/// @param geo O nome do arquivo geo
/// @param svgGeo O nome do arquivo svg que sera printado apos a leitura do geo
/// @param ts O estilo do texto
/// @param formas A lista de formas
///@param nformas VAlor passado por referencia que mostra a quantidade de formas da lista
void le_geo(FILE* geo, FILE* svgGeo,Estilo ts, Lista listaFormas, int* nformas);

#endif