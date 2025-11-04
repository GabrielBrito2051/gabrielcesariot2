#ifndef circulo_h
#define circulo_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void* Circulo;

/*
    Arquivo .h relacionado a forma circulo, com funcoes de get, set, criar um novo circulo e free das strings de cores
*/

/// @brief Cria um novo circulo com os parametros especificados
/// @param id O id do circulo
/// @param x A coordenada x do centro do circulo
/// @param y A coordenada y do centro do circulo
/// @param r O raio do circulo
/// @param corb A cor de borda do circulo
/// @param corp A cor de preenchmento do circulo
/// @return Retorna o ponteiro para o circulo criado
Circulo criar_circulo(int id, double x, double y, double r, char* corb, char* corp);

/// @brief Define a coordenada x do centro do ciruclo c
/// @param c O circulo em questao
/// @param x A nova coordenada x do centro do circulo
void setXcirculo(Circulo c, double x);

/// @brief Define a coordenada y do centro do circulo c
/// @param c O ciruclo em questao
/// @param y A nova coordenada y do centro do circulo
void setYcirculo(Circulo c, double y);

/// @brief Define a cor de borda do circulo c
/// @param c O circulo
/// @param corb A nova cor de borda do circulo
void setCORBcirculo(Circulo c, char*corb);

/// @brief Define a cor de preenchimento do circulo c
/// @param c O circulo
/// @param corp A nova cor de preenchimento do circulo
void setCORPcirculo(Circulo c, char* corp);

/// @brief Pega o id do circulo c
/// @param c O circulo que tera seu id lido
/// @return Retorna o id do circulo
int getIDcirculo(Circulo c);

/// @brief Pega a coordenada x do circulo c
/// @param c O circulo que tera sua coordenada x do centro  lida
/// @return Retorna a coordenada x do centro do circulo
double getXcirculo(Circulo c);

/// @brief Pega a coordenada y do circulo c
/// @param c O circulo que tera sua coordenada y do centro  lida
/// @return Retorna o valor da coordenada y do centro do circulo
double getYcirculo(Circulo c);

/// @brief Pega o tamanho do raio do circulo
/// @param c O circulo que tera o tamanho do raio lido
/// @return Retorna o valor do raio do circulo
double getRcirculo(Circulo c);

/// @brief Pega o valor hexadecimal da cor de borda do circulo c
/// @param c O circulo
/// @return Retorna o valor hexadecimal da cor de borda do circulo
char* getCORBcirculo(Circulo c);

/// @brief Pega o valor hexadecimal da cor de preenchimento do circulo c
/// @param c O circulo
/// @return Retorna o valor hexadecimal da cor de preenchimento do circulo
char* getCORPcirculo(Circulo c);

/// @brief Libera a memoria da cor de borda do circulo
/// @param c O circulo
void freeCORBcirculo(Circulo c);

/// @brief Libera a memoria da cor de preenchimento do ciruclo
/// @param c O circulo
void freeCORPcirculo(Circulo c);

#endif