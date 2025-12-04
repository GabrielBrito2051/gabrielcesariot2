#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linha.h"

typedef struct{
    int i; 
    double x1, y1, x2, y2;
    char *corb, *corcompl;
    bool ativo;
}linha;

void setCORCOMPLlinha(Linha l){
    int r, g, b;
    int Rcompl, Gcompl, Bcompl;
    char* p = ((linha*)l)->corb;
    sscanf(p, "%*c%2x%2x%2x", &r, &g, &b);
    Rcompl = 255 - r;
    Gcompl = 255 - g;
    Bcompl = 255 - b;
    sprintf(((linha*)l)->corcompl, "#%02X%02X%02X", Rcompl, Gcompl, Bcompl);
}

Linha criar_linha(int i, double x1, double y1, double  x2, double y2, char* corb){
    linha *l = malloc(sizeof(linha));
    l->i = i;
    l->x1 = x1;
    l->y1 = y1;
    l->x2 = x2;
    l->y2 = y2;
    l->ativo = false;

    l->corb = (char*)malloc(strlen(corb)+1);
    if (l->corb==NULL){
        printf("Erro ao alocar memoria para a cor da linha");
        exit(1);
    }
    strcpy(l->corb,corb);

    l->corcompl = (char*) malloc(strlen(corb)+1);
    if(l->corcompl == NULL){
        printf("Erro ao alocar memoria para a cor complementar da linha");
        exit(1);
    }
    strcpy(l->corcompl,l->corb);

    return ((Linha*)l);
}

int getIDlinha(Linha l){
    return ((linha*)l)->i;
}

double getX1linha(Linha l){
    return ((linha*)l)->x1;
}

double getY1linha(Linha l){
    return ((linha*)l)->y1;
}

double getX2linha(Linha l){
    return ((linha*)l)->x2;
}

double getY2linha(Linha l){
    return ((linha*)l)->y2;
}

char* getCORBlinha(Linha l){
    return ((linha*)l)->corb;
}

char* getCORCOMPLlinha(Linha l){
    return ((linha*)l)->corcompl;
}

void setX1linha(Linha l, double x1){
    ((linha*)l)->x1 = x1;
}

void setY1linha(Linha l, double y1){
    ((linha*)l)->y1 = y1;
}

void setX2linha(Linha l, double x2){
    ((linha*)l)->x2 = x2;
}

void setY2linha(Linha l, double y2){
    ((linha*)l)->y2 = y2;
}

void setCORBlinha(Linha l, char* corb){
    strcpy(((linha*)l)->corb, corb);
    setCORCOMPLlinha(l);
}

void freeCORBlinha(Linha l){
    linha* var = (linha*)l;
    free(var->corb);
}

void freeCORPlinha(Linha l){
    linha* var = (linha*)l;
    free(var->corcompl);
}

void setAtivo(Linha l, bool ativo){
    linha* var = (linha*)l;
    var->ativo = ativo; 
}

bool getAtivo(Linha l){
    return ((linha*)l)->ativo;
}

int compara_linha(int id,Linha l){
    linha* var = (linha*)l;
    return (var->i==id) ? 1:0;
}