#include <stdio.h>
#include <math.h>
#include "geometria.h"

#define TITULO(t) printf("\n=== TESTE: %s ===\n", t)

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main() {
    printf("INICIANDO BATERIA DE TESTES - MODULO GEOMETRIA\n");

    TITULO("calcula_distancia_pontos");
    double d = calcula_distancia_pontos(0, 0, 3, 4);
    printf("Pontos: (0,0) e (3,4)\n");
    printf("Esperado: 5.000\n");
    printf("Obtido:   %.3f\n", d);

    TITULO("min e max");
    double v1 = 10.5, v2 = 20.1;
    printf("Valores: %.2f e %.2f\n", v1, v2);
    printf("Min obtido: %.2f (Esperado: 10.50)\n", min(v1, v2));
    printf("Max obtido: %.2f (Esperado: 20.10)\n", max(v1, v2));

    TITULO("calcula_angulo");
    double cx = 10, cy = 10; 

    double ang1 = calcula_angulo(cx, cy, 20, 10);
    printf("Ponto (20, 10) [Direita] -> Esperado: 0.00 rad | Obtido: %.3f rad\n", ang1);

    double ang2 = calcula_angulo(cx, cy, 10, 20);
    printf("Ponto (10, 20) [Y+]      -> Esperado: %.3f rad | Obtido: %.3f rad\n", M_PI/2, ang2);

    double ang3 = calcula_angulo(cx, cy, 0, 10);
    printf("Ponto (0, 10)  [Esquerda]-> Esperado: %.3f rad | Obtido: %.3f rad\n", M_PI, ang3);

    double ang4 = calcula_angulo(cx, cy, 10, 0); 
    printf("Ponto (10, 0)  [Y-]      -> Esperado: %.3f rad | Obtido: %.3f rad\n", 3*M_PI/2, ang4);


    TITULO("calcula_orientacao");
    double ax = 0, ay = 0, bx = 10, by = 10;
    
    double orient1 = calcula_orientacao(ax, ay, bx, by, 0, 10);
    printf("Ponto a Esquerda -> Esperado: > 0 | Obtido: %.2f\n", orient1);

    double orient2 = calcula_orientacao(ax, ay, bx, by, 10, 0);
    printf("Ponto a Direita  -> Esperado: < 0 | Obtido: %.2f\n", orient2);

    double orient3 = calcula_orientacao(ax, ay, bx, by, 5, 5);
    printf("Ponto Colinear   -> Esperado: 0.0 | Obtido: %.2f\n", orient3);


    TITULO("interseccao_segmentos");
    double ix, iy;
    bool colidiu;

   
    colidiu = interseccao_segmentos(5, 0, 5, 10, 0, 5, 10, 5, &ix, &iy);
    printf("Teste Cruzamento -> Esperado: Sim (5.0, 5.0)\n");
    if(colidiu) printf("   Resultado: COLIDIU em (%.2f, %.2f)\n", ix, iy);
    else printf("   Resultado: NAO COLIDIU (Erro)\n");

    colidiu = interseccao_segmentos(0,0, 10,0, 0,1, 10,1, &ix, &iy);
    printf("Teste Paralelos  -> Esperado: Nao\n");
    printf("   Resultado: %s\n", colidiu ? "COLIDIU (Erro)" : "NAO COLIDIU (Ok)");


    TITULO("distancia_raio (Parametro u)");

    
    double u = distancia_raio(0, 0, 10, 0, 5, -10, 5, 10);
    
    printf("Cenario: Bomba(0,0)->Olha(10,0) | Muro vertical em X=5\n");
    printf("Esperado: u = 0.500 (metade do vetor raio)\n");
    printf("Obtido:   u = %.3f\n", u);

    double u_paralelo = distancia_raio(0,0, 10,0,0,1, 10,1);
    printf("Cenario: Paralelo -> Esperado: Valor Gigante (HUGE_VAL)\n");
    printf("Obtido:  %e\n", u_paralelo);

    printf("\nFIM DOS TESTES.\n");
    return 0;
}