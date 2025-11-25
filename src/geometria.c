#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "geometria.h"

#define PI 3.14159265358979323846

#define epsilon 1e-9 

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
        angulo += 2 * PI;
    }

    return angulo;
}

double calcula_orientacao(double ax, double ay, double bx, double by, double px, double py){
    return  (bx-ax) * (py - ay) - (by - ay) * (px - ax);
}

bool interseccao_segmentos(double ax, double ay, double bx, double by, double cx, double cy, double ex, double ey, double* ix, double* iy){
    double r_x = bx - ax;
    double r_y = by - ay;
    double s_x = ex - cx;
    double s_y = ey - cy;

    double det = (r_x * s_y) - (r_y * s_x);
    if(fabs(det)<epsilon){
        return false;
    }

    double val_comum_x = cx- ax;
    double val_comum_y = cy - ay;
    double num_t = (val_comum_x * s_y) - (val_comum_y * s_x);
    double num_u = (val_comum_x * r_y) - (val_comum_y * r_x);
    double t = num_t / det;
    double u = num_u / det;

    if(t>=0.0 && t<=1.0 && u>=0.0 && u<=1.0){
        if(ix != NULL){
            *ix = ax + (t * r_x);
        }
        if(iy!=NULL){
            *iy = ay + (t * r_y);
        }
        return true;
    }
    return false;
}

double distancia_raio(double bx, double by, double vx, double vy, double p1x, double p1y, double p2x, double p2y){
    double r_x = vx - bx;
    double r_y = vy - by;
    double s_x = p2x - p1x;
    double s_y = p2y - p1y;
    double det = (r_x * s_y) - (r_y * s_x);

    if(fabs(det)<epsilon){
        return HUGE_VAL;
    }

    double val_x = p1x - bx;
    double val_y = p1y - by;
    double num_u = (val_x * s_y) -  (val_y * s_x);
    double u = num_u / det;

    return u;
}