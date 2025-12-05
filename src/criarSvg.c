#include <stdio.h>
#include <stdlib.h>
#include "formas.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

void startSVG(FILE* svg){
    fprintf(svg,"<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
}

void insere_circulo_svg(FILE* svg, Circulo c){
    fprintf(svg,"<circle id=\"%d\" style=\"fill:%s;fill-opacity:0.5;stroke:%s\" r=\"%lf\" cy=\"%lf\" cx=\"%lf\" />\n", getIDcirculo(c), getCORPcirculo(c), getCORBcirculo(c), getRcirculo(c), getYcirculo(c), getXcirculo(c));
    }

void insere_retangulo_svg(FILE *svg, Retangulo r){
    fprintf(svg, "<rect id=\"%d\" style=\"fill:%s;fill-opacity:0.5;stroke:%s\" height=\"%lf\" width=\"%lf\" y=\"%lf\" x=\"%lf\" />\n", getIDretangulo(r),getCORPretangulo(r), getCORBretangulo(r), getHretangulo(r), getWretangulo(r), getYretangulo(r), getXretangulo(r));
}

void insere_linha_svg(FILE* svg, Linha l){
    fprintf(svg, "<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"2\" />\n", getIDlinha(l), getX1linha(l), getY1linha(l), getX2linha(l), getY2linha(l), getCORBlinha(l));
}

void insere_texto_svg(FILE* svg, Texto t, Estilo ts){
fprintf(svg, "<text id=\"%d\" x=\"%lf\" y=\"%lf\" style=\"font-family: '%s'; font-size: %spx; font-weight: %s; fill: %s;\"> %s </text>\n",getIDtexto(t), getXtexto(t),  getYtexto(t), getFAMILY(ts),getSIZE(ts),getWEIGHT(ts), getCORPtexto(t),  getTXTOtexto(t));
}

void insere_bomba_svg(FILE* svg, double x, double y){
    fprintf(svg,"<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" fill=\"purple\" stroke=\"purple\" stroke-width=\"2\"/>",x, y);
}

void fechasvg(FILE* svg){
    fprintf(svg,"</svg>\n");
}