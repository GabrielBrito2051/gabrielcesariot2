#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formas.h"
#include "texto.h"
#include "linha.h"
#include "circulo.h"
#include "retangulo.h"
#include "lista.h"
#include "ler_arquivo.h"
#include "criarSvg.h"

#define tamLinha 256
#define max_cor 8
#define max_font 64
#define max_text 1024

void le_geo(FILE* geo, FILE* svgGeo, Estilo ts, Lista listaFormas, int* nformas){
    char* linhaGeo = malloc(sizeof(char)*tamLinha);
    if(linhaGeo==NULL) return;
    int id = 0;
    *nformas = 0;
    double x, x2, y, y2, r, h, w;
    char corb[max_cor], corp[max_cor];
    char font[max_font], size[max_font], weight[max_font];
    char txto[max_text], tipo[3], a;
    while(le_linha(geo, linhaGeo)!=NULL){
        sscanf(linhaGeo, "%s", tipo);
        if(tipo[0]=='c'){
            Pacote pac = criarPacote();
            sscanf(linhaGeo,"%*s %d %lf %lf %lf %7s %7s",&id, &x, &y, &r, corb, corp);
            Circulo c = criar_circulo(id, x, y ,r, corb, corp);
            setTipoForma(pac, 'c');
            setFormaPacote(pac, c);
            insere_lista(listaFormas,pac);
            insere_circulo_svg(svgGeo, c);
        }

        else if(tipo[0]=='r'){
            Pacote pac = criarPacote();
            sscanf(linhaGeo,"%*s %d %lf %lf %lf %lf %7s %7s", &id, &x, &y, &w, &h, corb, corp);
            Retangulo r = criar_retangulo(id, x, y, w, h, corb, corp);
            setTipoForma(pac, 'r');
            setFormaPacote(pac, r);
            insere_lista(listaFormas,pac);
            insere_retangulo_svg(svgGeo,r);
        }

        else if(tipo[0]=='l'){
            Pacote pac = criarPacote();
            sscanf(linhaGeo,"%*s %d %lf %lf %lf %lf %7s",&id, &x, &y, &x2, &y2, corb);
            Linha l = criar_linha(id, x, y, x2, y2, corb);
            setTipoForma(pac, 'l');
            setFormaPacote(pac, l);
            insere_lista(listaFormas, pac);
            insere_linha_svg(svgGeo, l);
        }

        else if(strcmp(tipo,"t")==0){
            Pacote pac = criarPacote();
            sscanf(linhaGeo, "%*s %d %lf %lf %7s %7s %c %1023[^\n]", &id, &x, &y, corb, corp, &a, txto);
            Texto t = criar_texto(id, x, y, corb, corp, a, txto);
            setTipoForma(pac, 't');
            setFormaPacote(pac, t);
            insere_lista(listaFormas,pac);
            insere_texto_svg(svgGeo, t, ts);
        }

        else if(strcmp(tipo, "ts")==0){
            sscanf(linhaGeo,"%*s %63s %1s %63s", font, weight, size);
            setFAMILY(ts, font);
            setWEIGHT(ts, weight);
            setSIZE(ts, size);
        }
        if(id>*nformas && strcmp(tipo,"ts")!=0){
            *nformas = id;
        }
    }

    free(linhaGeo);
}