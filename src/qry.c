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

void leComandoQry(FILE* qry, FILE* svgQry,FILE* txt, Lista formas, Lista anteparos, int* maior_id, Estilo ts, char flag, int i){
    char* linhaQry = malloc(sizeof(tam_linha));
    char comando[4], sfx[64], cor[8];
    int i, j;
    char orient;
    double x, y, dx, dy, xa, ya, xb, yb;
    while(le_linha(qry, linhaQry)!=NULL){
        sscanf(linhaQry, "%s", comando);

        if(strcmp(comando,"a")==0){
            sscanf(linhaQry,"%*s %d %d %c",&i ,&j, &orient);
            for(i;i<=j;i++){
                Pacote f = busca_conteudo(formas,compara_forma, i);
                if(f==NULL){
                    fprintf("Nao foi encontrada a forma de id %d",i);
                }
                tipoforma tipo = getTipoForma(f);
                if(tipo==RETANGULO){
                    for(int k=1;k<=4;k++){
                        getSegmentoRetangulo(getFORMApacote(f), &xa, &ya, &xb, &yb, k);
                        *maior_id++;
                        Linha anovo = criar_linha(*maior_id, xa, ya, xb, yb, getCORBretangulo(getFORMApacote(f)));
                        insere_lista(anteparos, anovo);
                        printInfoAnteparos(txt, getFORMApacote(f),getTipoForma(f),anovo);
                    }
                }else{
                    getSegmentoLinha(getFORMApacote(f), getTipoForma(f), &xa, &ya, &xb, &yb);
                    *maior_id++;
                    Linha anovo = criar_linha(*maior_id, xa,ya,xb,yb,getCORBforma(getFORMApacote(f)));
                    insere_lista(anteparos, anovo);
                    printInfoAnteparos(txt, getFORMApacote(f),getTipoForma(f),anovo);
                }
            }
        }

        else if(strcmp(comando, "d")==0){
            sscanf(linhaQry,"%*s %lf %lf %s",&x,&y,sfx);
            Poligono explosao = calcular_visibilidade(anteparos, x, y, flag, i);
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
                    Linha removida = remove_lista(anteparos, compara_forma, id);
                    freeCORBlinha(l);
                    freeCORPlinha(l);
                    free(l);
                }
                anteparo = proximo_lista(anteparos, anteparo);
            }
        }

        else if(strcmp(comando,"p")==0){
            sscanf(linhaQry, "%*s %lf %lf %s %s",&x,&y,cor,sfx);
            Poligono pintura = calcular_visibilidade(anteparos, x, y, flag, i);
            Forma no = get_inicio_lista(formas);
            while(no!=NULL){
                Pacote pac = get_conteudo_lista(no);
                tipoforma tipo = getTipoForma(pac);
                Forma f = getFORMApacote(pac);
                if(atinge_forma(pintura, f, tipo)==1){
                    setCORBforma(f, tipo, cor);
                }
                no = proximo_lista(formas, no);
            }
            Linha anteparo = get_inicio_lista(anteparos);
            while(anteparo!=NULL){
                Linha l =get_conteudo_lista(anteparo);
                int id = getIDlinha(l);
                if(getAtivo(anteparo)){
                    setCORBlinha(l, cor);
                }
                anteparo = proximo_lista(anteparos, anteparo);
            }
        }

        else if(strcmp(comando,"cln")==0){
            sscanf(linhaQry, "%*s %lf %lf %lf %lf %s", &x, &y, &dx, &dy, sfx);
            Poligono clonagem = calcular_visibilidade(anteparos, x, y, flag, i);
            Forma no = get_inicio_lista(formas);
            while(no!=NULL){
                Pacote pac = get_conteudo_lista(no);
                Forma f = getFORMApacote(pac);
                tipoforma tipo = getTipoForma(pac);
                if(atinge_forma(clonagem, f, tipo)==1){
                    Pacote pac = clonarForma(f, tipo,dx,dy, &maior_id);
                    insere_lista(formas, pac);
                }
            }
        }
    }
    free(linhaQry);
}