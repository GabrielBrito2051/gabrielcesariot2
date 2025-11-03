#ifndef retangulo_h
#define retangulo_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void* Retangulo;

/*
    Arquivo .h relacionado a forma de um retangulo, com funcoes de get, set, criar retangulo e free nas strings de cores
*/

/// @brief Cria um novo retangulo com os valores dos parmetros
/// @param i O valor do identificador do retangulo
/// @param x O valor da coordenada x da ancora do retangulo
/// @param y O valor da coordenada y da ancora do retangulo
/// @param w O valor da largura do retangulo
/// @param h O valor da altura do retangulo
/// @param corb O valor hexadeimal da cor da borda do retangulo
/// @param corp O valor hexadecimal da cor do preenchimento do retangulo
/// @return Retorna um ponteiro para o retangulo criado
Retangulo criar_retangulo(int i, double x, double y, double w, double h, char* corb, char* corp);

/// @brief Pega o valor do identificador do retangulo r
/// @param r O retangulo no qual tera seu identificador lido
/// @return Retorna o valor do identificador do retangulo r
int getIDretangulo(Retangulo r);

/// @brief Pega o valor da coordenada x da ancora do retangulo r
/// @param r O retangulo no qual tera sua coordenada x lida
/// @return Retorna o valor da coordenada x da ancora do retangulo r
double getXretangulo(Retangulo r);

/// @brief Pega o valor da coordenada y da ancora do retangulo r
/// @param r O retangulo no qual tera sua coordenada y lida
/// @return Retorna o valor da coordenada y da ancora do retangulo r
double getYretangulo(Retangulo r);

/// @brief Pega o valor da largura do retangulo r
/// @param r O retangulo que tera sua largura lida
/// @return Retorna o valor da largura dp retangulo r
double getWretangulo(Retangulo r);

/// @brief Pega o valor da altura do retangulo r
/// @param r O retangulo que tera sua altura lida
/// @return Retorna o valor da altura do retangulo r
double getHretangulo(Retangulo r);

/// @brief Pega o valor hexadecimal da cor da borda do retangulo r
/// @param r O retangulo que tera a cor de borda lida
/// @return Retorna um array de caracteres com o valor hexadecimal da cor de borda do retangulo r
char* getCORBretangulo(Retangulo r);

/// @brief Pega o valor hexadecimal da cor do preenchimento do retangulo r
/// @param r O retangulo que tera a cor de preenchimento lida
/// @return Retorna um array de caracteres com o valor hexadecimal da cor do preenchimento do retangulo r
char* getCORPretangulo(Retangulo r);

/// @brief Define o valor da coordenada x da ancora do retangulo r
/// @param r O retangulo que tera sua coordenada x da ancora definida
/// @param x O valor da coordenada x da ancora do retangulo
void setXretangulo(Retangulo r, double x);

/// @brief Define o valor da coordenada y da ancora do retangulo r
/// @param r O retangulo no qual tera sua coordenada y da ancora deinida
/// @param y O valor da coordenada da ancora do retangulo
void setYretangulo(Retangulo r, double y);

/// @brief Define o valor da cor da borda do retangulo r
/// @param r O retangulo no qual tera sua cor de borda definida
/// @param corb O valor hexadecimal da cor de borda do retangulo
void setCORBretangulo(Retangulo r, char* corb);

/// @brief Define o valor da cor do preenchimento do retangulo r
/// @param r O retangulo que tera sua cor de preenchimento definida
/// @param corp O valor da cor do preenchimento do retangulo
void setCORPretangulo(Retangulo r, char* corp);

/// @brief Libera a memoria da cor de borda do retangulo
/// @param r O retangulo 
void freeCORBretangulo(Retangulo r);

/// @brief Libera a memoria da cor de preenchimento do retangulo
/// @param r O retangulo
void freeCORPretangulo(Retangulo r);

#endif