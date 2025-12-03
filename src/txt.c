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
        fprintf(txt,"O CIRCULO DE ID %d FOI TRANSFORMADO EM ANTEPARO\n",getIDcirculo(f));
    }
    else if(tipo==RETANGULO){
        fprintf(txt,"O RETANGULO DE ID %d FOI TRANSFORMADO EM ANTEPARO\n",getIDretangulo(f));
    }
    else if(tipo==LINHA){
        fprintf(txt,"A LINHA DE ID %d FOI TRANSFORMADA EM ANTEPARO\n",getIDlinha(f));
    }
    else if(tipo==TEXTO){
        fprintf(txt,"O TEXTO DE ID %d FOI TRANFOMADO EM ANTEPARO\n",getIDtexto(f));
    }
    fprintf(txt,"ID DO ANTEPARO CRIADO: %d\tCOORDENADAS DO ANTEPARO CRIADO: (%lf,%lf) -> (%lf,%lf)\n",getIDlinha(anteparo),getX1linha(anteparo),getY1linha(anteparo),getX2linha(anteparo),getY2linha(anteparo));

}

void printBombaDestruicao(FILE* txt, Forma f, tipoforma tipo){
    if(tipo==CIRCULO){
        fprintf(txt,"O CIRCULO DE ID %d FOI DESTRUIDO\n",getIDcirculo(f));
    }
    else if(tipo==RETANGULO){
        fprintf(txt,"O RETANGULO DE ID %d FOI DESTRUIDO\n",getIDretangulo(f));
    }
    else if(tipo==LINHA){
        fprintf(txt,"A LINHA DE ID %d FOI DESTRUIDA\n",getIDlinha(f));
    }
    else if(tipo==TEXTO){
        fprintf(txt,"O TEXTO DE ID %d FOI DESTRUIDO\n",getIDtexto(f));
    }
}

void printBombaPintura(FILE* txt, Forma f, tipoforma tipo){
    if(tipo==CIRCULO){
        fprintf(txt,"O CIRCULO DE ID %d FOI PINTADO\n",getIDcirculo(f));
    }
    else if(tipo==RETANGULO){
        fprintf(txt,"O RETANGULO DE ID %d FOI PINTADO\n",getIDretangulo(f));
    }
    else if(tipo==LINHA){
        fprintf(txt,"A LINHA DE ID %d FOI PINTADA\n",getIDlinha(f));
    }
    else if(tipo==TEXTO){
        fprintf(txt,"O TEXTO DE ID %d FOI PINTADO\n",getIDtexto(f));
    }
}

void printBombaClonagem(FILE* txt, Forma original, tipoforma tipo, Forma clone){
    if(tipo==CIRCULO){
        fprintf(txt,"O CIRCULO DE ID %d FOI CLONADO E GEROU O CIRCULO DE ID %d\n",getIDcirculo(original), getIDcirculo(clone));
    }
    else if(tipo==RETANGULO){
        fprintf(txt,"O RETANGULO DE ID %d FOI CLONADO E GEROU O RETANGULO DE ID %d\n",getIDretangulo(original),getIDretangulo(clone));
    }
    else if(tipo==LINHA){
        fprintf(txt,"A LINHA DE ID %d FOI CLONADA E GEROU A LINHA DE ID %d\n",getIDlinha(original),getIDlinha(clone));
    }
    else if(tipo==TEXTO){
        fprintf(txt,"O TEXTO DE ID %d FOI CLONADO E GEROU O TEXTO DE ID %d\n",getIDtexto(original),getIDtexto(clone));
    }
}