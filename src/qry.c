#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "formas.h"
#include "geometria.h"
#include "poligono.h"
#include "visibilidade.h"
#include "geo.h"
#include "lista.h"
#include "criarSvg.h"
#include "arvore.h"
#include "mergesort.h"
#include "txt.h"

#define tam_linha 256

void bounding_box_poligono(Lista anteparos, Lista formas, double bx, double by, char orient){
    double minX = bx, minY = by;
    double maxX = bx, maxY = by;

    if(getTAMANHOlista(formas)>0){
        Forma no = get_inicio_lista(formas);
        while(no!=NULL){
            Pacote pac = get_conteudo_lista(no);
            Forma f = getFORMApacote(pac);
            tipoforma tipo = getTipoForma(pac);

            if (tipo == CIRCULO) {
                double cx = getXcirculo(f); double cy = getYcirculo(f); double r = getRcirculo(f);
                if (cx - r < minX) minX = cx - r;
                if (cx + r > maxX) maxX = cx + r;
                if (cy - r < minY) minY = cy - r;
                if (cy + r > maxY) maxY = cy + r;
            } else if (tipo == RETANGULO) {
                double x = getXretangulo(f); double y = getYretangulo(f);
                double w = getWretangulo(f); double h = getHretangulo(f);
                if (x < minX) minX = x;
                if (x + w > maxX) maxX = x + w;
                if (y < minY) minY = y;
                if (y + h > maxY) maxY = y + h;
            } else if (tipo == LINHA) {
                double x1 = getX1linha(f); double y1 = getY1linha(f);
                double x2 = getX2linha(f); double y2 = getY2linha(f);
                if (x1 < minX) minX = x1;
                 if (x2 < minX) minX = x2;
                if (x1 > maxX) maxX = x1;
                if (x2 > maxX) maxX = x2;
                if (y1 < minY) minY = y1;
                if (y2 < minY) minY = y2;
                if (y1 > maxY) maxY = y1; 
                if (y2 > maxY) maxY = y2;
            } else if(tipo==TEXTO){
                double x1, y1, x2, y2;
                getSegmentoLinha(f, TEXTO, &x1, &y1, &x2, &y2, orient);
                if (x1 < minX) minX = x1; 
                if (x2 < minX) minX = x2;
                if (x1 > maxX) maxX = x1; 
                if (x2 > maxX) maxX = x2;
                if (y1 < minY) minY = y1;
                if (y2 < minY) minY = y2;
                if (y1 > maxY) maxY = y1; 
                if (y2 > maxY) maxY = y2;
            }
            no = proximo_lista(formas, no);
        }
    double margem = 50.0;
    minX -= margem; minY -= margem;
    maxX += margem; maxY += margem;

    Linha l1 = criar_linha(-1, minX, minY, maxX, minY, "black"); 
    setAtivo(l1, false);
    insere_lista(anteparos, l1);

    Linha l2_cima = criar_linha(-2, maxX, minY, maxX, by, "black");
    setAtivo(l2_cima, false);
    insere_lista(anteparos, l2_cima);

    Linha l2_baixo = criar_linha(-3,maxX, by, maxX, maxY, "black");
    setAtivo(l2_baixo, false);
    insere_lista(anteparos, l2_baixo);

    Linha l3 = criar_linha(-4, maxX, maxY, minX, maxY, "black");
    setAtivo(l3, false);
    insere_lista(anteparos, l3);

    Linha l4 = criar_linha(-5, minX, maxY, minX, minY, "black");
    setAtivo(l4, false);
    insere_lista(anteparos, l4);
    }
}

void leComandoQry(FILE* qry, FILE* svgQry,FILE* txt, Lista formas, Lista anteparos, int* maior_id, char flag, int isortParam, char* nomeBase, Estilo ts){
    char* linhaQry = malloc(sizeof(char) * tam_linha);
    if(linhaQry==NULL){
        printf("Erro ao alocar memoria para a linha do Qry\n");
        return;
    }
    char comando[4], sfx[64], cor[8];
    int i, j, novo_id = *maior_id;
    char orient;
    double x, y, dx, dy, xa, ya, xb, yb;
    Poligono final;
    while(le_linha(qry, linhaQry)!=NULL){
        sscanf(linhaQry, "%s", comando);

        if(strcmp(comando,"a")==0){
            sscanf(linhaQry,"%*s %d %d %c",&i ,&j, &orient);
            for(int ini = i;ini<=j;ini++){
                Pacote f = busca_conteudo(formas,compara_forma, ini);
                if(f==NULL){
                    fprintf(txt,"Nao foi encontrada a forma de id %d",ini);
                }
                tipoforma tipo = getTipoForma(f);
                if(tipo==RETANGULO){
                    for(int k=1;k<=4;k++){
                        getSegmentoRetangulo(getFORMApacote(f), &xa, &ya, &xb, &yb, k);
                        novo_id++;
                        Linha anovo = criar_linha(novo_id, xa, ya, xb, yb, getCORBretangulo(getFORMApacote(f)));
                        insere_lista(anteparos, anovo);
                        printInfoAnteparos(txt, getFORMApacote(f),getTipoForma(f),anovo);
                    }
                }else{
                    getSegmentoLinha(getFORMApacote(f), getTipoForma(f), &xa, &ya, &xb, &yb, orient);
                    novo_id++;
                    Linha anovo = criar_linha(novo_id, xa,ya,xb,yb,getCORBforma(f));
                    insere_lista(anteparos, anovo);
                    printInfoAnteparos(txt, getFORMApacote(f),getTipoForma(f),anovo);
                }
                Pacote removido = remove_lista(formas, compara_forma, ini);
                freePacote(removido);
            }
        } 

        else if(strcmp(comando, "d")==0){
            sscanf(linhaQry,"%*s %lf %lf %s",&x,&y,sfx);
            fprintf(txt,"BOMBA DE DESTRUICAO JOGADA NA COORDENADA (%lf,%lf)\n",x, y);
            insere_bomba_svg(svgQry, x, y);
            bounding_box_poligono(anteparos, formas, x, y, orient);
            Poligono explosao = calcular_visibilidade(anteparos, x, y, flag, isortParam);
            final = explosao;
            Forma no = get_inicio_lista(formas);
            fprintf(txt,"-----FORMAS-----\n");
            while(no!=NULL){
                Pacote pac = get_conteudo_lista(no);
                tipoforma tipo = getTipoForma(pac);
                Forma f = getFORMApacote(pac);
                int id = getIDforma(f, tipo);
                no = proximo_lista(formas, pac);
                if(atinge_forma(explosao, f, tipo)==1){
                    Pacote removido = remove_lista(formas, compara_forma, id);
                    printBombaDestruicao(txt, f, tipo);
                    freePacote(removido);
                }
            }
            Linha anteparo = get_inicio_lista(anteparos);
            fprintf(txt,"----- ANTEPAROS -----\n");
            while(anteparo!=NULL){
                Linha l = get_conteudo_lista(anteparo);
                int id = getIDlinha(l);
                anteparo = proximo_lista(anteparos, anteparo);
                if(getAtivo(l) && id>0){
                    Linha removida = remove_lista(anteparos, compara_linha, id);
                    printBombaDestruicao(txt, removida, LINHA);
                    freeCORBlinha(removida);
                    freeCORPlinha(removida);
                    free(removida);
                }
                
            }
        }

        else if(strcmp(comando,"p")==0){
            sscanf(linhaQry, "%*s %lf %lf %s %s",&x,&y,cor,sfx);
            fprintf(txt,"BOMBA DE PINTURA JOGADA NA COORDENADA (%lf,%lf)\n",x, y);
            bounding_box_poligono(anteparos, formas, x, y, orient);
            Poligono pintura = calcular_visibilidade(anteparos, x, y, flag, isortParam);
            final = pintura;
            Forma no = get_inicio_lista(formas);
            fprintf(txt,"-----FORMAS-----\n");
            while(no!=NULL){
                Pacote pac = get_conteudo_lista(no);
                tipoforma tipo = getTipoForma(pac);
                Forma f = getFORMApacote(pac);
                if(atinge_forma(pintura, f, tipo)==1){
                    setCORBforma(f, tipo, cor);
                    printBombaPintura(txt, f, tipo);
                }
                no = proximo_lista(formas, no);
            }
            Linha anteparo = get_inicio_lista(anteparos);
            fprintf(txt,"----- ANEPAROS -----\n");
            while(anteparo!=NULL){
                Linha l =get_conteudo_lista(anteparo);
                int id = getIDlinha(l);
                if(getAtivo(l) && id>0){
                    setCORBlinha(l, cor);
                    printBombaPintura(txt, l, LINHA);
                }
                anteparo = proximo_lista(anteparos, anteparo);
            }
        }

        else if(strcmp(comando,"cln")==0){
            sscanf(linhaQry, "%*s %lf %lf %lf %lf %s", &x, &y, &dx, &dy, sfx);
            fprintf(txt,"BOMBA DE CLONAGEM JOGADA NA COORDENADA (%lf,%lf)\n",x, y);
            bounding_box_poligono(anteparos, formas, x, y, orient);
            Poligono clonagem = calcular_visibilidade(anteparos, x, y, flag, isortParam);
            final = clonagem;
            Forma no = get_inicio_lista(formas);
            fprintf(txt,"-----FORMAS-----\n");
            while(no!=NULL){
                Pacote pac = get_conteudo_lista(no);
                Forma f = getFORMApacote(pac);
                tipoforma tipo = getTipoForma(pac);
                if(atinge_forma(clonagem, f, tipo)==1){
                    Forma clonado = clonarForma(f, tipo,dx,dy, novo_id);
                    novo_id++;
                    printSVGforma(svgQry, tipo, clonado,ts);
                    printBombaClonagem(txt, f, tipo, clonado);
                }
                no = proximo_lista(formas, no);
            }
            Linha anteparo = get_inicio_lista(anteparos);
            fprintf(txt,"-----ANTEPAROS-----");
            while(anteparo!=NULL){
                Linha l = get_conteudo_lista(anteparo);
                int id = getIDlinha(l);
                if(getAtivo(l) && id>0){
                    Linha cloneante = clonarForma(l, LINHA, dx, dy, novo_id);
                    novo_id++;
                    insere_linha_svg(svgQry, cloneante);
                    freeCORBlinha(cloneante);
                    freeCORPlinha(cloneante);
                    printBombaClonagem(txt, l, LINHA, cloneante);
                    free(cloneante);
                }
                anteparo = proximo_lista(anteparos, anteparo);
            }
        }
    }
    if(strcmp(sfx, "-")==0){
        print_poligono_svg(svgQry, final,"red",0.3);
    }else{
        char nomeSfx[1024];
        snprintf(nomeSfx,sizeof(nomeSfx),"%s-%s.svg",nomeBase, sfx);
        FILE* svgSfx = abre_arquivo_escrita(nomeSfx);
        if(svgSfx==NULL){
            printf("Erro ao criar o arquivo svg separado");
            return;
        }
        startSVG(svgSfx);
        print_poligono_svg(svgSfx, final, "red",0.3);
        fechasvg(svgSfx);
        fclose(svgSfx);
    }

    free_poligono(final);
    free(linhaQry);
}