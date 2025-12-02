#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ler_arquivo.h"

#define tamLinha 256

arquivo abre_arquivo_escrita(char* nome){
    arquivo arq = fopen(nome, "w");
    if(arq==NULL){
        printf("Erro ao abrir arquivo %s\n",nome);
        exit(1);
    }
    return ((FILE*)arq);
}

arquivo abre_arquivo_leitura(char* nome){
    arquivo arq = fopen(nome, "r");
    if(arq==NULL){
        printf("Erro ao abrir o arquivo %s\n",nome);
        exit(1);
    }
    return ((FILE*)arq);
}

char* le_linha(arquivo arq, char* linha){
    return fgets(linha, tamLinha, arq);
}

void fecha_arquivo(arquivo arq){
    fclose(arq);
}