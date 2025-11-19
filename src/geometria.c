#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "geometria.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double calcula_distancia_pontos(double x1, double y1, double x2, double y2){
    double dist = sqrt(pow((x1-x2),2)+pow((y1-y2),2));
    return dist;
}

double max(double a, double b){
    return (a>b) ? a:b;
}

double min(double a, double b){
    return (b<a) ? b:a;
}

double calcula_angulo(double cx, double cy, double x, double y){
    double dy = y - cy;
    double dx = x - cx; 

    double angulo = atan2(dy, dx);

    if(angulo<0){
        angulo += 2 * M_PI;
    }

    return angulo;
}