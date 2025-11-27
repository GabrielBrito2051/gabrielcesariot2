#ifndef txt_h
#define txt_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "formas.h"
#include "ler_arquivo.h"

/*
    Arquivo .h relacionado aos prints no arquivo .txt
*/

/// @brief Imprime o id e o tipo da forma original, id e extremos dos segmentos produzidos
/// @param txt Ponteiro para o arquivo txt
/// @param f A forma que foi transformada em anteparo
/// @param tipo O tipo da forma transformada em anteparo
/// @param anteparo O anteparo criado
void printInfoAnteparos(FILE* txt, Forma f, tipoforma tipo, Forma anteparo);

/// @brief Impirme o id e o tipo da forma destruidas
/// @param txt Ponteiro para o arquivo txt
/// @param f A forma destruida
/// @param tipo O tipo da forma
void printBombaDestruicao(FILE* txt, Forma f, tipoforma tipo);

/// @brief Imprime o id e o tipo da forma pintada
/// @param txt Ponteiro para o arquivo txt
/// @param f A forma destruida
/// @param tipo O tipo da forma
void printBombaPintura(FILE* txt, Forma f, tipoforma tipo);

/// @brief Imprime o id e o tipo da forma original e da forma clonada
/// @param txt Ponteiro para o arquivo txt
/// @param original A forma original
/// @param tipo O tipo da forma original
/// @param clone O clone
void printBombaClonagem(FILE* txt, Forma original, tipoforma tipo, Forma clone);

#endif