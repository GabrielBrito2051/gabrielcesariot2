#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

#define TITULO(t) printf("\n=== TESTE: %s ===\n", t)
#define ASSERT_INT(obtido, esperado) \
    printf("   Resultado: %s (Esperado: %d | Obtido: %d)\n", \
    (obtido == esperado) ? "OK" : "ERRO", esperado, obtido)

int comparar_ints(void* a, void* b) {
    int* i1 = (int*)a;
    int* i2 = (int*)b;
    
    if (*i1 < *i2) return -1;
    if (*i1 > *i2) return 1;
    return 0;
}

int* novo_int(int valor) {
    int* p = (int*) malloc(sizeof(int));
    *p = valor;
    return p;
}

int main() {
    printf("INICIANDO BATERIA DE TESTES - MODULO ARVORE (BST)\n");

    TITULO("Criar Arvore");
    Arvore arv = criar_arvore(comparar_ints);
    
    if (arv != NULL) printf("   Arvore criada com sucesso.\n");
    else { printf("   ERRO FATAL: Arvore nao criada.\n"); return 1; }

    void* busca_vazia = busca_mais_proximo(arv);
    if (busca_vazia == NULL) printf("   Busca em arvore vazia retornou NULL (Correto).\n");
    else printf("   ERRO: Busca em arvore vazia nao retornou NULL.\n");

    TITULO("Insercao");
    
    printf("   Inserindo: 50, 30, 70, 20, 40\n");
    
    int* i50 = novo_int(50); insere_arvore(arv, i50);
    int* i30 = novo_int(30); insere_arvore(arv, i30);
    int* i70 = novo_int(70); insere_arvore(arv, i70);
    int* i20 = novo_int(20); insere_arvore(arv, i20);
    int* i40 = novo_int(40); insere_arvore(arv, i40);

    TITULO("busca_mais_proximo (Menor Elemento)");
    
    int* menor = (int*) busca_mais_proximo(arv);
    if (menor != NULL) {
        ASSERT_INT(*menor, 20);
    } else {
        printf("   ERRO: Retornou NULL apos insercoes.\n");
    }

    TITULO("Remocao de Folha (20)");
    
    int* removido = (int*) remove_arvore(arv, i20);
    
    printf("   Dado retornado pela funcao remove: %d\n", (removido ? *removido : -1));
    
    menor = (int*) busca_mais_proximo(arv);
    if (menor != NULL) {
        printf("   Novo menor apos remover 20:");
        ASSERT_INT(*menor, 30);
    }

    TITULO("Remocao de Raiz com 2 filhos (50)");
 
    remove_arvore(arv, i50);
    
    menor = (int*) busca_mais_proximo(arv);
    if (menor != NULL) {
        printf("   Novo menor apos remover raiz:");
        ASSERT_INT(*menor, 30);
    }

    remove_arvore(arv, i30);
    menor = (int*) busca_mais_proximo(arv);
    if (menor != NULL) {
        printf("   Novo menor apos remover 30:");
        ASSERT_INT(*menor, 40);
    }
    
    TITULO("Remocao de Raiz com 1 Filho (Caso Critico)");
    
    destroi_arvore(arv); 
    arv = criar_arvore(comparar_ints);

    printf("   Cenario: Raiz(100) tem apenas filho esquerdo (60).\n");
    
    int* i100 = novo_int(100); insere_arvore(arv, i100);
    int* i60 = novo_int(60);   insere_arvore(arv, i60);

    int* check = (int*) busca_mais_proximo(arv);
    printf("   Menor antes da remocao: %d (Esperado: 60)\n", *check);

    remove_arvore(arv, i100);

    check = (int*) busca_mais_proximo(arv);
    
    if (check != NULL) {
        ASSERT_INT(*check, 60);
        printf("   Sucesso: O filho unico (60) nao foi perdido.\n");
    } else {
        printf("   ERRO GRAVE: A arvore ficou vazia! O ponteiro da raiz nao foi atualizado corretamente.\n");
    }

    free(i100); free(i60);

    TITULO("destroi_arvore");
    destroi_arvore(arv);
    printf("   Arvore destruida (se nao houve crash, sucesso).\n");

    free(i50); free(i30); free(i70); free(i20); free(i40);

    printf("\nFIM DOS TESTES.\n");
    return 0;
}