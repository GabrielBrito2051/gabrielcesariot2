#ifndef linha_h
#define linha_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef void* Linha;

/*
    Arquivo .h relacionado a forma de uma linha, com funcoes de get, set, criar uma nova linha e liberar a memoria das strings de cores
*/

/// @brief Calcula e define o valor hexadecimal da cor complementar da linha l
/// @param l A linha que tera sua cor lida
void setCORCOMPLlinha(Linha l);

/// @brief Cria uma linha com os valores dos parametros especificados
/// @param i O valor do identificador da linha
/// @param x1 O valor da coordenada x do inicio da linha
/// @param y1 O valor da coordenada y do inicio da linha
/// @param x2 O valor da coordenada x do fim da linha
/// @param y2 O valor da coordenada y do fim da linha
/// @param cor O valor haxadecimal da cor da linha
/// @return Retorna um ponteiro para a linha criada
Linha criar_linha(int i, double x1, double y1, double x2, double y2, char* corb);

/// @brief Pega o valor do identificador da linha l
/// @param l A linha que tera seu identificador lido
/// @return Retorna o valor do identificador da linha l
int getIDlinha(Linha l);

/// @brief Pega o valor da coordenada x do inicio da linha l
/// @param l A linha que tera sua coordenada x de inicio lida
/// @return Retorna o valor da coordenada x do inicio da linha l
double getX1linha(Linha l);

/// @brief Pega o valor da coordenada y do inicio da linha l
/// @param l A linha que tera sua coordenada y do inicio lida
/// @return Retorna o valor da coordenada y do inicio da linha l
double getY1linha(Linha l);

/// @brief Pega o valor da coordenada x do fim da linha l
/// @param l A linha que tera sua coordenada x do fim lida
/// @return Retorna o valor da coordenada x do fim da linha l
double getX2linha(Linha l);

/// @brief Pega o valor da coordenada y do fim da linha l
/// @param l A linha que tera sua coordenada y do fim lida
/// @return Retorna o valor da coordenada y do fim da linha l
double getY2linha(Linha l);

/// @brief Pega o valor hexadecimal da cor da linha l
/// @param l A linha que tera sua cor lida
/// @return Retorna um array de caracteres com o valor hexadecimal da cor da linha l
char* getCORBlinha(Linha l);

/// @brief Pega o valor hexadecimal da cor complementar da linha l
/// @param l A linha que tera sua cor lida
/// @return Retorna um array de caracteres com o valor hexadecimal da cor complementar da linha
char* getCORCOMPLlinha(Linha l);

/// @brief Define o valor da coordenada x de inicio da linha l
/// @param l A linha que tera sua coordenada x de incio definida
/// @param x1 O valor da coordenada x de inicio da linha
void setX1linha(Linha l,double x1);

/// @brief Define o valor da coordenada y de inicio da linha l
/// @param l A linha que tera sua coordenada y de inicio lida
/// @param y1 O valor da coordenada y de incio
void setY1linha(Linha l, double y1);

/// @brief Define o valor da coordenada x do fim da linha l
/// @param l A linha que tera sua coordenada x de fim lida
/// @param x2 O valor da coordenada x do fim da linha
void setX2linha(Linha l, double x2);

/// @brief Define o valor da coordenada y do fim da linha l
/// @param l A linha que tera sua coordenada y de fim lida
/// @param y2 O valor da coordenada y de fim da linha
void setY2linha(Linha l, double y2);

/// @brief Deifne o valor da cor hexadecimal da linha
/// @param l A linha que tera sua cor definida
/// @param cor O valor hexadecimal da cor da linha
void setCORBlinha(Linha l, char* corb);

/// @brief Libera a memoria da cor de borda da linha
/// @param l A linha
void freeCORBlinha(Linha l);

/// @brief Libera a memoria da cor de preenchimento da linha
/// @param l A linha
void freeCORPlinha(Linha l);

/// @brief Define se o segmento esta ativo ou não
/// @param l O segmento
/// @param ativo True or false
void setAtivo(Linha l, bool ativo);

/// @brief Obtem se o segmento esta ativo ou nao
/// @param l O segmento
bool getAtivo(Linha l);

/// @brief Compara uma linha com um id fornecido
/// @param id O id fornecido
/// @param l A linha
/// @return Retorna 1 se a linha tiver o id fornecido e 0 caso contrario
int compara_linha(int id, Linha l);

#endif