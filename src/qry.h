#ifndef qry_h
#define qry_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "formas.h"
#include "geometria.h"
#include "poligono.h"
#include "visibilidade.h"
#include "geo.h"
#include "lista.h"
#include "criarSvg.h"
#include "arvore.h"
#include "mergesort.h"

/*
    Arquivo .h relacionado a leitura do arquivo .qry, realizando as acoes de transformar em anteparos, destruicao, pintura, e clonagem
*/

/// @brief Faz a leitura do arquivo de comandos .qry
/// @param qry Ponteiro para o arquivo qry
/// @param svgQry Ponteiro para o arquivo svg do qry
/// @param txt Ponterio para o arquivo txt
/// @param formas A lista de formas
/// @param anteparos A lista de anteparos
/// @param maior_id O maior id das formas
/// @param ts Estilo de texto
/// @param flag Flag do comando que indica se sera utilizado o qsort ou o mergesort para ordenar na arvore
/// @param i Flag do comando que indica o tamanho maximo que o subvetor deve ter para comecar a utilizar o insertion sort
void leComandoQry(FILE* qry, FILE* svgQry,FILE* txt, Lista formas,Lista anteparos, int* maoir_id, Estilo ts, char flag, int i);

#endif