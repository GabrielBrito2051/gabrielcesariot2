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
/// @param p O pacote da forma
/// @return Retorna 1 se a forma tiver o id inserido e 0 caso contrario
int compara_forma(int id, Forma p);

/// @brief Libera a memoria de uma forma dentro do pacote
/// @param pac O pacote
void destruirFormaPacote(Pacote pac);

/// @brief Libera memoria do pacote
/// @param pac O pacote que sera liberado
void freePacote(Pacote pac);

/// @brief Obtem as coordenadas do segmento de linha para as formas linha, texto e circulo
/// @param f A forma
/// @param tipo O tipo da forma
/// @param x1 Ponteiro para armazenar a coordenada x1 da forma
/// @param y1 Ponteiro para armazenar a coordenada y1 da forma
/// @param x2 Ponteiro para armazenar a coordenada x2 da forma
/// @param y2 Ponteiro para armazenar a coordenada y2 da forma
/// @param orient Indica se os circulos serao trnasformados em segmentos verticais ou horizontais
void getSegmentoLinha(Forma f, tipoforma tipo, double* x1, double*y1, double *x2, double* y2, char orient);

/// @brief Obtem as coordenadas do segmento de linha para o retangulo
/// @param f A forma
/// @param x1 Ponteiro para armazenar a coordenada x1 da forma
/// @param y1 Ponteiro para armazenar a coordenada y1 da forma
/// @param x2 Ponteiro para armazenar a coordenada x2 da forma
/// @param y2 Ponteiro para armazenar a coordenada y2 da forma
/// @param func Variavel extra para indicar qual lado do retangulo sera transformado em segmento
void getSegmentoRetangulo(Forma f, double* x1, double* y1, double* x2, double* y2, int func);

/// @brief Pega a cor de borda de uma forma generica
/// @param pac O pacote contendo a forma
/// @return Retorna o ponteiro para a string contendo a cor de borda
char* getCORBforma(Pacote pac);

/// @brief Define a cor de borda de uma forma generica
/// @param f A forma
/// @param tipo O tipo da forma
/// @param corb Ponteiro para a string contendo a cor de borda
void setCORBforma(Forma f, tipoforma tipo, char* corb);

/// @brief Faz a clonagem de um forma
/// @param f A forma que sera clonada
/// @param tipo O tipo da forma
/// @param dx A distancia que o clone sera deslocado no eixo x
/// @param dy A distancia que o clone sera deslocado no eixo y
/// @param maior_id Valor que indica o maior id
Pacote clonarForma(Forma f, tipoforma tipo, double dx, double dy, int maior_id);

/// @brief Imprime uma forma generica no arquivo svg
/// @param svg Ponteiro para o arquivo svg
/// @param tipo O tipo da forma
/// @param f A forma
/// @param ts O estilo do texto
void printSVGforma(FILE* svg, tipoforma tipo, Forma f, Estilo ts);

#endif