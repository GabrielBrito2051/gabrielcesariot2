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

/// @brief Libera a memoria de uma forma dentro do pacote
/// @param pac O pacote
void destruirFormaPacote(Pacote pac);

/// @brief Libera memoria do pacote
/// @param pac O pacote que sera liberado
void freePacote(Pacote pac);

#endif