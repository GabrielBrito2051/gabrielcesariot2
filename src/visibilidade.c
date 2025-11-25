#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "visibilidade.h"
#include "arvore.h"
#include "poligono.h"
#include "lista.h"
#include "formas.h"
#include "geometria.h"

#define PI 3.14159265358979323846

typedef enum{
    inicio,
    fim
}tipoevento;

typedef struct{
    double angulo;
    double x, y;
    tipoevento tipo;
    Segmento seg;
}evento;

typedef  void* Evento;

static double gbx, gby, gvx, gvy;

int cmp_eventos(const void* a, const void* b){
    evento* e1 = (evento*) a;
    evento* e2 = (evento*) b;

    if(e1->angulo < e2->angulo) return -1;
    if(e1->angulo > e2->angulo) return 1;

    if(e1->tipo == inicio && e2->tipo == fim) return -1;
    if(e1->tipo == fim && e2->tipo == inicio) return 1;

    return 0;
}

int cmp_segmentos_arvore(Segmento a, Segmento b){
    if(a==b) return 0;

    double ax1 = getX1linha(a), ay1 = getY1linha(a), ax2 = getX2linha(a), ay2 = getY2linha(a);
    double bx1 = getX1linha(b), by1 = getY1linha(b), bx2 = getX2linha(b), by2 = getY2linha(b);

    double dist_a = distancia_raio(gbx, gby, gvx, gvy, ax1, ay1, ax2, ay2);
    double dist_b = distancia_raio(gbx, gby, gvx, gvy, bx1, by1, bx2, by2);

    if(fabs(dist_a - dist_b) > 1e-9){
        return (dist_a < dist_b) ? -1:1;
    }

    int ida = getIDlinha(a);
    int idb = getIDlinha(b);

    return (ida<idb) ? -1 : (ida>idb ? 1:0);
}

Poligono calcular_visibilidade(Lista listaSegmentos, double bx, double by){
    gbx = bx;
    gby = by;

    int num_seg = getTAMANHOlista(listaSegmentos);
    int num_eventos = num_seg * 2;
    evento* e = malloc(sizeof(evento) * num_eventos);

    int i = 0;
    Segmento atual = get_inicio_lista(listaSegmentos);
    while(atual!=NULL){
        double x1, x2, y1, y2;
        x1 = getX1linha(atual);
        x2 = getX2linha(atual);
        y1 = getY1linha(atual);
        y2 = getY2linha(atual);

        double ang1 = calcula_angulo(bx, by, x1, y1);
        double ang2 = calcula_angulo(bx, by, x2, y2);
        double delta = ang2 - ang1;
        while(delta <= -PI) delta += 2*PI;
        while(delta > PI) delta -= 2*PI;

        if(delta >0){
            e[i].x = x1;
            e[i].y = y1;
            e[i].angulo = ang1;
            e[i].tipo = inicio;
            e[i].seg = atual;

            e[i+1].x = x2;
            e[i+1].y = y2;
            e[i+1].angulo = ang2;
            e[i+1].tipo = fim;
            e[i+1].seg = atual;
        }else{
            e[i].x = x2;
            e[i].y = y2;
            e[i].angulo = ang2;
            e[i].tipo = inicio;
            e[i].seg = atual;

            e[i+1].x = x1;
            e[i+1].y = y1;
            e[i+1].angulo = ang1;
            e[i+1].tipo = fim;
            e[i+1].seg = atual;
        }
        i+=2;
        atual = proximo_lista(listaSegmentos, atual);
    }

    qsort(e, num_eventos, sizeof(evento), cmp_eventos);
    Arvore seg_ativos = criar_arvore(cmp_segmentos_arvore);
    Poligono poligono = criar_poligono();

    atual = get_inicio_lista(listaSegmentos);
    while(atual!=NULL){
        double x1 = getX1linha(atual);
        double x2 = getX2linha(atual);
        double y1 = getY1linha(atual);
        double y2 = getY2linha(atual);

        double angulo1 = calcula_angulo(bx,by,x1,y1);
        double angulo2 = calcula_angulo(bx,by,x2,y2);

        double dif = angulo1 - angulo2;
        if(dif<0) dif = -dif;
        if(dif>PI){
            insere_arvore(seg_ativos,atual);
        }
        atual = proximo_lista(listaSegmentos,atual);
    }

    for(int k=0;k<num_eventos;k++){
        evento ev = e[k];
        gvx = ev.x;
        gvy = ev.y;

        Segmento seg_ante = busca_mais_proximo(seg_ativos);

        if(ev.tipo == inicio){
            insere_arvore(seg_ativos, ev.seg);
        }else{
            remove_arvore(seg_ativos, ev.seg);
        }
        Segmento seg_depois = busca_mais_proximo(seg_ativos);
        int vertice_visivel = 0;
        if(seg_ante==NULL){
            vertice_visivel = 1;
        }else{
            double x1, y1, x2, y2;
            x1 = getX1linha(seg_ante);
            y1 = getY1linha(seg_ante);
            x2 = getX2linha(seg_ante);
            y2 = getY2linha(seg_ante);
            double u = distancia_raio(bx, by, ev.x, ev.y, x1, y1, x2, y2);
            if(u>=1.0 - 1e-9){
                vertice_visivel = 1;
            }
        }

        double sombrax = 0;
        double sombray = 0;
        bool tem_sombra = false;

        if(seg_ante!=seg_depois){
            Segmento alvo = NULL;
            if(ev.tipo==fim){
                if(seg_depois !=NULL){
                    alvo = seg_depois;
                }
            }
            else if(ev.tipo==inicio){
                if(seg_ante != NULL){
                    alvo = seg_ante;
                }
            }

            if(alvo != NULL){
                double sx1 = getX1linha(alvo);
                double sy1 = getY1linha(alvo);
                double sx2 = getX2linha(alvo);
                double sy2 = getY2linha(alvo);
                double ix, iy;
                double dirx = ev.x - bx;
                double diry = ev.y - by;
                double comprimento = calcula_distancia_pontos(bx, by, ev.x, ev.y);
                if(comprimento>1e-9){
                    dirx /= comprimento;
                    diry /= comprimento;
                }

                double raiox = bx + dirx * 1000000.0;
                double raioy = by + diry * 1000000.0;

                bool colidiu = interseccao_segmentos(bx, by, raiox, raioy, sx1, sy1, sx2, sy2, &ix, &iy);
                if(colidiu){
                    double du = distancia_raio(bx, by, ev.x, ev.y, sx1, sy1, sx2, sy2);
                    if(du>1.0 + 1e-9){
                        sombrax = ix;
                        sombray = iy;
                        tem_sombra = true;
                    }
                }
            }
        }
        if(ev.tipo==inicio){
            if(tem_sombra){
                inserir_ponto(poligono, sombrax, sombray);
            }
            if(vertice_visivel){
                inserir_ponto(poligono,ev.x,ev.y);
            }
        }else{
            if(vertice_visivel){
                inserir_ponto(poligono,ev.x,ev.y);
            }
            if(tem_sombra){
                inserir_ponto(poligono,sombrax, sombray);
            }
        }
    }

    destroi_arvore(seg_ativos);
    free(e);

    return poligono;
}

int atinge_forma(Poligono poligono, Forma forma, tipoforma tipo){
    if(poligono==NULL || forma==NULL) return 0;

    switch(tipo){
        case CIRCULO: {
            double x, y;
            x = getXcirculo(forma);
            y = getYcirculo(forma);
            if(contem_ponto(poligono, x, y)) return 1;

            return 0;
        }
        case RETANGULO: {
            double x, y, w, h;
            x = getXretangulo(forma);
            y = getYretangulo(forma);
            w = getWretangulo(forma);
            h = getHretangulo(forma);

            if(contem_ponto(poligono, x, y)) return 1;
            if(contem_ponto(poligono, x + w, y)) return 1;
            if(contem_ponto(poligono, x +w, y+h)) return 1;
            if(contem_ponto(poligono, x, y+h)) return 1;

            if(intercepta_seg(poligono, x, y, x+w, y)) return 1;
            if(intercepta_seg(poligono, x, y+h,x+w,y+h)) return 1;
            if(intercepta_seg(poligono, x, y, x, y+h)) return 1;
            if(intercepta_seg(poligono, x+w, y,x+w,y+h)) return 1;

            return 0;
        }
        case LINHA: {
            double x1, y1, x2, y2;
            x1 = getX1linha(forma);
            y1 = getY1linha(forma);
            x2 = getX2linha(forma);
            y2 = getY2linha(forma);

            if(contem_ponto(poligono,x1,y1)) return 1;
            if(contem_ponto(poligono,x2,y2)) return 1;

            if(intercepta_seg(poligono,x1,y1,x2,y2)) return 1;

            return 0;
        }
        case TEXTO: {
            double x1, y1, x2, y2;
            x1 = getXtexto(forma);
            y1 = getYtexto(forma);
            getSegmentoLinha(forma, tipo, &x1, &y1, &x2, &y2);

            if(contem_ponto(poligono,x1,y1)) return 1;
            if(contem_ponto(poligono,x2,y2)) return 1;
            if(intercepta_seg(poligono,x1,y1,x2,y2)) return 1;

            return 0;
        }
        default:
            return 0;
    }
}

int ponto_na_regiao(Poligono poligono, double x, double y){
    return contem_ponto(poligono, x, y);
}