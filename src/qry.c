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

void leComandoQry(FILE* qry, FILE* svgQry,FILE* txt, Lista formas, Lista anteparos, int* maior_id, char flag, int isortParam){
    char* linhaQry = malloc(sizeof(tam_linha));
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
                    getSegmentoLinha(getFORMApacote(f), getTipoForma(f), &xa, &ya, &xb, &yb);
                    novo_id++;
                    Linha anovo = criar_linha(novo_id, xa,ya,xb,yb,getCORBforma(getFORMApacote(f)));
                    insere_lista(anteparos, anovo);
                    printInfoAnteparos(txt, getFORMApacote(f),getTipoForma(f),anovo);
                }
            }
        } 

        else if(strcmp(comando, "d")==0){
            sscanf(linhaQry,"%*s %lf %lf %s",&x,&y,sfx);
            Poligono explosao = calcular_visibilidade(anteparos, x, y, flag, isortParam);
            final = explosao;
            Forma no = get_inicio_lista(formas);
            while(no!=NULL){
                Pacote pac = get_conteudo_lista(no);
                tipoforma tipo = getTipoForma(pac);
                Forma f = getFORMApacote(pac);
                int id = getIDforma(f, tipo);
                if(atinge_forma(explosao, f, tipo)==1){
                    Pacote removido = remove_lista(formas, compara_forma, id);
                    printBombaDestruicao(txt, f, tipo);
                    freePacote(removido);
                }
                no = proximo_lista(formas, pac);
            }
            Linha anteparo = get_inicio_lista(anteparos);
            while(anteparo!=NULL){
                Linha l = get_conteudo_lista(anteparo);
                int id = getIDlinha(l);
                if(getAtivo(l)){
                    Linha removida = remove_lista(anteparos, compara_linha, id);
                    fprintf(txt,"----- ANTEPAROS -----\n");
                    printBombaDestruicao(txt, removida, LINHA);
                    freeCORBlinha(removida);
                    freeCORPlinha(removida);
                    free(removida);
                }
                anteparo = proximo_lista(anteparos, anteparo);
            }
        }

        else if(strcmp(comando,"p")==0){
            sscanf(linhaQry, "%*s %lf %lf %s %s",&x,&y,cor,sfx);
            Poligono pintura = calcular_visibilidade(anteparos, x, y, flag, isortParam);
            final = pintura;
            Forma no = get_inicio_lista(formas);
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
            while(anteparo!=NULL){
                Linha l =get_conteudo_lista(anteparo);
                if(getAtivo(l)){
                    setCORBlinha(l, cor);
                    fprintf(txt,"----- ANEPAROS -----\n");
                    printBombaPintura(txt, l, LINHA);
                }
                anteparo = proximo_lista(anteparos, anteparo);
            }
        }

        else if(strcmp(comando,"cln")==0){
            sscanf(linhaQry, "%*s %lf %lf %lf %lf %s", &x, &y, &dx, &dy, sfx);
            Poligono clonagem = calcular_visibilidade(anteparos, x, y, flag, isortParam);
            final = clonagem;
            Forma no = get_inicio_lista(formas);
            while(no!=NULL){
                Pacote pac = get_conteudo_lista(no);
                Forma f = getFORMApacote(pac);
                tipoforma tipo = getTipoForma(pac);
                if(atinge_forma(clonagem, f, tipo)==1){
                    Pacote pac = clonarForma(f, tipo,dx,dy, &novo_id);
                    insere_lista(formas, pac);
                    printBombaClonagem(txt, f, tipo, getFORMApacote(pac));
                }
                no = proximo_lista(formas, no);
            }
            Linha anteparo = get_inicio_lista(anteparos);
            while(anteparo!=NULL){
                Linha l = get_conteudo_lista(anteparo);
                if(getAtivo(l)){
                    Linha clone = clonarForma(l, LINHA, dx, dy, maior_id);
                    insere_lista(anteparos, clone);
                    printBombaClonagem(txt, l, LINHA, clone);
                }
            }
        }
    }
    if(strcmp(sfx, "-")==0){
        print_poligono_svg(svgQry, final,"red",0.3);
    }else{
        // print poligono em outro arquivo
    }
    free_poligono(final);
    free(linhaQry);
}