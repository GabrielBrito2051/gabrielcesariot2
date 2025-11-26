#include <stdio.h>
#include <stdlib.h>
#include "visibilidade.h"
#include "poligono.h"
#include "lista.h"
#include "formas.h" 
#include "linha.h"
#include "circulo.h"
#include "retangulo.h"

#define ASSERT(teste, msg) printf("   [%s] %s\n", (teste) ? "OK" : "ERRO", msg)

int main() {
    printf("=== TESTE DE INTEGRACAO: VISIBILIDADE ===\n");

    Lista anteparos = criar_lista();

    Linha parede_cima = criar_linha(1, 0, 0, 100, 0, "#000000");
    Linha parede_dir = criar_linha(2, 100, 0, 100, 100, "#000000");
    Linha parede_baixo = criar_linha(3, 100, 100, 0, 100, "#000000");
    Linha parede_esq = criar_linha(4, 0, 100, 0, 0, "#000000");
    
    Linha muro = criar_linha(5, 50, 20, 50, 80, "#0000FF");

    insere_lista(anteparos, parede_cima);
    insere_lista(anteparos, parede_dir);
    insere_lista(anteparos, parede_baixo);
    insere_lista(anteparos, parede_esq);
    insere_lista(anteparos, muro);

    printf("1. Cenario criado: Caixa 100x100 com muro no meio (50,20->50,80).\n");

    double bombaX = 20, bombaY = 50;
    printf("2. Explodindo bomba em (%.1f, %.1f)...\n", bombaX, bombaY);

    Poligono explosao = (Poligono) calcular_visibilidade(anteparos, bombaX, bombaY);

    if (explosao == NULL) {
        printf("ERRO FATAL: Poligono de visibilidade nulo.\n");
        return 1;
    }
    printf("   Calculo concluido.\n");

    printf("\n--- Teste de Pontos ---\n");
    
    int resA = ponto_na_regiao(explosao, 30, 50);
    ASSERT(resA == 1, "Ponto (30,50) deve ser visivel.");

    int resB = ponto_na_regiao(explosao, 80, 50);
    ASSERT(resB == 0, "Ponto (80,50) deve estar na sombra (invisivel).");

    printf("\n--- Teste de Formas ---\n");

    Circulo c1 = criar_circulo(10, 30, 50, 5, "#00FF00", "#00FF00"); 
    int hit1 = atinge_forma(explosao, c1, CIRCULO);
    ASSERT(hit1 == 1, "Circulo na frente foi atingido.");

    Circulo c2 = criar_circulo(11, 80, 50, 5, "#00FF00", "#00FF00"); 
    int hit2 = atinge_forma(explosao, c2, CIRCULO);
    ASSERT(hit2 == 0, "Circulo na sombra ficou seguro.");

    printf("\n--- Gerando SVG de Debug ---\n");
    FILE* svg = fopen("debug_visibilidade.svg", "w");
    if(svg){
        fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"120\" height=\"120\">\n");
        
        fprintf(svg, "<rect width=\"100%%\" height=\"100%%\" fill=\"white\" />\n");

        print_poligono_svg(svg, explosao, "red", 0.3);

        fprintf(svg, "<line x1=\"50\" y1=\"20\" x2=\"50\" y2=\"80\" stroke=\"blue\" stroke-width=\"2\" />\n"); // Muro
        fprintf(svg, "<rect x=\"0\" y=\"0\" width=\"100\" height=\"100\" fill=\"none\" stroke=\"black\" />\n"); // Borda

        fprintf(svg, "<circle cx=\"%.1f\" cy=\"%.1f\" r=\"2\" fill=\"red\" />\n", bombaX, bombaY);

        fprintf(svg, "<circle cx=\"30\" cy=\"50\" r=\"5\" fill=\"green\" fill-opacity=\"0.5\" stroke=\"black\"/>\n");
        fprintf(svg, "<circle cx=\"80\" cy=\"50\" r=\"5\" fill=\"green\" fill-opacity=\"0.5\" stroke=\"black\"/>\n");

        fprintf(svg, "</svg>");
        fclose(svg);
        printf("Arquivo 'debug_visibilidade.svg' gerado com sucesso.\n");
    }

    free_poligono(explosao);

    return 0;
}