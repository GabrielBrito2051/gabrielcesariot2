#ifndef formas_h
#define formas_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

typedef enum{
    CIRCULO,
    RETANGULO,
    LINHA,
    TEXTO
}tipoforma;

typedef struct pacote* Pacote;
typedef void* Forma;

/*
    Arquivo .h relacionado as formas genericas, com funcoes de get, set e criar um pacote para as formas
*/

/// @brief Cria um novo pacote para uma forma
/// @return Retorna o ponteiro para o pacote criado
Pacote criarPacote();

/// @brief Pega o tipo de uma da forma no pacote
/// @param Pacote O pacote que tera seu tipo pego
/// @return Retorna o tipo da forma
tipoforma getTipoForma(Pacote pac);

/// @brief Pega a forma contida no pacote
/// @param pacote O pacote que sera lido
/// @return Retorna a forma do pacote
Forma getFORMApacote(Pacote pac);

/// @brief Pega o id de uma forma de acordo com seu tipo
/// @param f A forma
/// @param tipo Seu tipo
/// @return Retorna o id da forma
int getIDforma(Forma f, tipoforma tipo);

/// @brief Define o tipo da forma dentro do pacote pac
/// @param pac O pacote da forma
/// @param tipo O tipo da forma
void setTipoForma(Pacote p, char tipo);

/// @brief Insere uma forma dentro de um pacote
/// @param pac O pacote
/// @param forma A forma que sera inserida no pacote
void setFormaPacote(Pacote pac, Forma forma);

/// @brief Compara uma forma com um id desejado
/// @param id O id que sera comparado com a forma
/// @param pac O pacote da forma
/// @return Retorna 1 se a forma tiver o id inserido e 0 caso contrario
int compara_forma(int id, Pacote pac);

/// @brief Libera a memoria de uma forma dentro do pacote
/// @param pac O pacote
void destruirFormaPacote(Pacote pac);

/// @brief Libera memoria do pacote
/// @param pac O pacote que sera liberado
void freePacote(Pacote pac);

/// @brief Obtem as coordenadas do segmento de linha para as formas linha, texto e circulo
/// @param f A forma
/// @param x1 Ponteiro para armazenar a coordenada x1 da forma
/// @param y1 Ponteiro para armazenar a coordenada y1 da forma
/// @param x2 Ponteiro para armazenar a coordenada x2 da forma
/// @param y2 Ponteiro para armazenar a coordenada y2 da forma
void getSegmentoLinha(Forma f, tipoforma tipo, double* x1, double*y1, double *x2, double* y2);

/// @brief Obtem as coordenadas do segmento de linha para o retangulo
/// @param f A forma
/// @param tipo O tipo da forma
/// @param x1 Ponteiro para armazenar a coordenada x1 da forma
/// @param y1 Ponteiro para armazenar a coordenada y1 da forma
/// @param x2 Ponteiro para armazenar a coordenada x2 da forma
/// @param y2 Ponteiro para armazenar a coordenada y2 da forma
/// @param func Variavel extra para indicar qual lado do retangulo sera transformado em segmento
void getSegmentoRetangulo(Forma f, tipoforma tipo, double* x1, double* y1, double* x2, double* y2, int func);

#endif