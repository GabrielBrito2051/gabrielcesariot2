#ifndef ler_arquivo_h
#define ler_arquivo_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef FILE* arquivo;

/*
    Arquivo .h associado a funcoes de arquivos, como ler, fechar e abrir
*/

/// @brief Cria e abre um arquivo para escrita
/// @param nome O nome do arquivo a ser aberto
/// @return Retorna um ponteiro para o arquivo aberto
arquivo abre_arquivo_escrita(char *nome);

/// @brief Cria e abre um arquivo para leitura
/// @param nome O nome do arquivo a ser aberto
/// @return Retorna um ponteiro para o arquivo aberto
arquivo abre_arquivo_leitura(char *nome);

/// @brief Le uma linha do arquivo arq
/// @param arq O arquivo que sera lido
/// @param linha Ponteiro para a string da linha
/// @return Retorna o ponteiro para a string que contem a linha do arquivo que foi lida
char* le_linha(arquivo arq, char* linha);

/// @brief Fecha o arquivo
/// @param arq O arquivo que sera fechado
void fecha_arquivo(arquivo arq);

#endif