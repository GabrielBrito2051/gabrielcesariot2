#include <stdio.h>
#include <stdlib.h>
#include "poligono.h"

#define TITULO(t) printf("\n=== TESTE: %s ===\n", t)
#define ASSERT(teste, esperado) printf("   [%s] Esperado: %s | Obtido: %s\n", \
    (teste == esperado) ? "OK" : "ERRO", \
    esperado ? "TRUE" : "FALSE", \
    teste ? "TRUE" : "FALSE")

int main() {
    printf("INICIANDO BATERIA DE TESTES - MODULO POLIGONO\n");

    TITULO("Criacao e Insercao de Pontos");
    
    Poligono poly = criar_poligono();
    if (poly != NULL) printf("   Poligono criado com sucesso.\n");
    else { printf("   ERRO FATAL: Falha ao criar poligono.\n"); return 1; }

    inserir_ponto(poly, 0.0, 0.0);
    inserir_ponto(poly, 10.0, 0.0);
    inserir_ponto(poly, 10.0, 10.0);
    inserir_ponto(poly, 0.0, 10.0);
    
    printf("   4 Pontos inseridos formando um quadrado 10x10 na origem.\n");

    TITULO("contem_ponto (Ray Casting)");

    printf("Testando Ponto (5, 5) [Centro]:");
    ASSERT(contem_ponto(poly, 5.0, 5.0), true);

    printf("Testando Ponto (15, 5) [Fora]:");
    ASSERT(contem_ponto(poly, 15.0, 5.0), false);

    printf("Testando Ponto (-5, 5) [Fora]:");
    ASSERT(contem_ponto(poly, -5.0, 5.0), false);

    printf("Testando Ponto (0, 5) [Borda]:");
    bool borda = contem_ponto(poly, 0.0, 5.0);
    printf("   Resultado: %s\n", borda ? "TRUE (Considera borda)" : "FALSE (Nao considera borda)");

    TITULO("intercepta_seg (Colisoes)");

    printf("Segmento (-5, 5) -> (15, 5) [Atravessa]:");
    ASSERT(intercepta_seg(poly, -5, 5, 15, 5), true);

    printf("Segmento (0, 20) -> (10, 20) [Fora]:");
    ASSERT(intercepta_seg(poly, 0, 20, 10, 20), false);

    printf("Segmento (2, 2) -> (8, 8) [Totalmente Dentro]:");
    ASSERT(intercepta_seg(poly, 2, 2, 8, 8), false); 

    printf("Segmento (-2, 5) -> (5, 5) [Entra e para]:");
    ASSERT(intercepta_seg(poly, -2, 5, 5, 5), true);

    TITULO("print_poligono_svg");
    
    FILE* fsvg = fopen("teste_poligono.svg", "w");
    if (fsvg) {
        fprintf(fsvg, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"100\" height=\"100\">\n");
        fprintf(fsvg, "<rect x=\"0\" y=\"0\" width=\"100\" height=\"100\" fill=\"#eee\" />\n");
        
        print_poligono_svg(fsvg, poly, "red", 0.5);
        
        fprintf(fsvg, "<circle cx=\"5\" cy=\"5\" r=\"1\" fill=\"blue\" />\n");
        fprintf(fsvg, "<circle cx=\"15\" cy=\"5\" r=\"1\" fill=\"black\" />\n");
        
        fprintf(fsvg, "</svg>");
        fclose(fsvg);
        printf("   Arquivo 'teste_poligono.svg' gerado.\n");
    } else {
        printf("   ERRO: Nao foi possivel criar o arquivo SVG.\n");
    }

    TITULO("free_poligono");
    free_poligono(poly);
    printf("   Memoria liberada (se nao houve crash, sucesso).\n");

    printf("\nFIM DOS TESTES.\n");
    return 0;
}