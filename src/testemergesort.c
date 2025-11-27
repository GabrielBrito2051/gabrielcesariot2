#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mergesort.h"

#define TITULO(t) printf("\n=== TESTE: %s ===\n", t)
#define ASSERT(teste, msg) printf("   [%s] %s\n", (teste) ? "OK" : "ERRO", msg)

int cmp_int(const void* a, const void* b) {
    int va = *(const int*)a;
    int vb = *(const int*)b;
    return (va - vb); 
}

int cmp_double(const void* a, const void* b) {
    double va = *(const double*)a;
    double vb = *(const double*)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

int verificar_ordenacao_int(int* v, size_t tam) {
    for (size_t i = 0; i < tam - 1; i++) {
        if (v[i] > v[i+1]) return 0; 
    }
    return 1; 
}

void imprimir_vetor(int* v, size_t tam) {
    printf("   Vetor: [ ");
    size_t limit = (tam > 15) ? 15 : tam;
    for (size_t i = 0; i < limit; i++) {
        printf("%d ", v[i]);
    }
    if (tam > 15) printf("... ");
    printf("]\n");
}

int main() {
    srand(time(NULL)); 
    printf("INICIANDO BATERIA DE TESTES - MODULO MERGESORT HIBRIDO\n");

    TITULO("Vetor Pequeno (Forca InsertionSort)");
    
    size_t tam1 = 10;
    int v1[] = {45, 12, 89, 33, 21, 5, 99, 2, 15, 67};
    
    printf("   Antes:"); imprimir_vetor(v1, tam1);
    
    merge_sort(v1, tam1, sizeof(int), cmp_int, 100);
    
    printf("   Depois:"); imprimir_vetor(v1, tam1);
    ASSERT(verificar_ordenacao_int(v1, tam1), "Ordenacao correta via InsertionSort.");

    TITULO("Vetor Grande (Forca Merge Sort Recursivo)");
    
    size_t tam2 = 50;
    int* v2 = malloc(tam2 * sizeof(int));
    
    for(size_t i=0; i<tam2; i++) v2[i] = rand() % 1000;
    
    printf("   (Exibindo primeiros 15 elementos)\n");
    printf("   Antes:"); imprimir_vetor(v2, tam2);
    
    merge_sort(v2, tam2, sizeof(int), cmp_int, 5);
    
    printf("   Depois:"); imprimir_vetor(v2, tam2);
    ASSERT(verificar_ordenacao_int(v2, tam2), "Ordenacao correta via Merge Sort.");
    
    free(v2);

    TITULO("Teste com Doubles (Genericidade)");
    
    double v3[] = {3.14, 1.41, 2.71, 0.58, 1.73};
    size_t tam3 = 5;
    
    printf("   Antes: [ ");
    for(size_t i=0; i<tam3; i++) printf("%.2f ", v3[i]);
    printf("]\n");
    
    merge_sort(v3, tam3, sizeof(double), cmp_double, 2);
    
    printf("   Depois: [ ");
    for(size_t i=0; i<tam3; i++) printf("%.2f ", v3[i]);
    printf("]\n");
    
    int ok = 1;
    for(size_t i=0; i<tam3-1; i++) if(v3[i] > v3[i+1]) ok = 0;
    ASSERT(ok, "Ordenacao de doubles correta.");

    TITULO("Casos de Borda");
    
    int v_vazio[] = {};
    merge_sort(v_vazio, 0, sizeof(int), cmp_int, 10);
    ASSERT(1, "Vetor vazio nao causou crash.");
    
    int v_unico[] = {42};
    merge_sort(v_unico, 1, sizeof(int), cmp_int, 10);
    ASSERT(v_unico[0] == 42, "Vetor unitario mantido.");

    printf("\nFIM DOS TESTES.\n");
    return 0;
}