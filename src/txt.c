#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "formas.h"
#include "ler_arquivo.h"
#include "txt.h"

void printInfoAnteparos(FILE* txt, Forma f, tipoforma tipo, Forma anteparo){
    if(tipo==CIRCULO){
        fprintf(txt,"O CIRCULO DE ID %d FOI TRANSFORMADO EM ANTEPARO",getIDcirculo(f));
    }
    else if(tipo==RETANGULO){
        fprintf(txt,"O RETANGULO DE ID %d FOI TRANSFORMADO EM ANTEPARO",getIDretangulo(f));
    }
    else if(tipo==LINHA){
        fprintf(txt,"A LINHA DE ID %d FOI TRANSFORMADA EM ANTEPARO",getIDlinha(f));
    }
    else if(tipo==TEXTO){
        fprintf(txt,"O TEXTO DE ID %d FOI TRANFOMADO EM ANTEPARO",getIDtexto(f));
    }
}

void printBombaDestruicao(FILE* txt, Forma f, tipoforma tipo){
    if(tipo==CIRCULO){
        fprintf(txt,"O CIRCULO DE ID %d FOI DESTRUIDO",getIDcirculo(f));
    }
    else if(tipo==RETANGULO){
        fprintf(txt,"O RETANGULO DE ID %d FOI DESTRUIDO",getIDretangulo(f));
    }
    else if(tipo==LINHA){
        fprintf(txt,"A LINHA DE ID %d FOI DESTRUIDA",getIDlinha(f));
    }
    else if(tipo==TEXTO){
        fprintf(txt,"O TEXTO DE ID %d FOI DESTRUIDO",getIDtexto(f));
    }
}

void printBombaPintura(FILE* txt, Forma f, tipoforma tipo){
    if(tipo==CIRCULO){
        fprintf(txt,"O CIRCULO DE ID %d FOI PINTADO",getIDcirculo(f));
    }
    else if(tipo==RETANGULO){
        fprintf(txt,"O RETANGULO DE ID %d FOI PINTADO",getIDretangulo(f));
    }
    else if(tipo==LINHA){
        fprintf(txt,"A LINHA DE ID %d FOI PINTADA",getIDlinha(f));
    }
    else if(tipo==TEXTO){
        fprintf(txt,"O TEXTO DE ID %d FOI PINTADA",getIDtexto(f));
    }
}

void printBombaClonagem(FILE* txt, Forma original, tipoforma tipo, Forma clone){
    if(tipo==CIRCULO){
        fprintf(txt,"O CIRCULO DE ID %D FOI CLONADO E GEROU O CIRCULO DE ID %d",getIDcirculo(original), getIDcirculo(clone));
    }
    else if(tipo==RETANGULO){
        fprintf(txt,"O RETANGULO DE ID %d FOI CLONADO E GEROU O RETANGULO DE ID %d",getIDretangulo(original),getIDretangulo(clone));
    }
    else if(tipo==LINHA){
        fprintf(txt,"A LINHA DE ID %d FOI CLONADA E GEROU A LINHA DE ID %d",getIDlinha(original),getIDlinha(clone));
    }
    else if(tipo==TEXTO){
        fprintf(txt,"O TEXTO DE ID %d FOI CLONADO E GEROU O TEXTO DE ID %d",getIDtexto(original),getIDtexto(clone));
    }
}