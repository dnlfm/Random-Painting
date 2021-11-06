/* 
 * File:   Coordenadas.h
 * Author: Daniel Freitas Martins - 2304
 *
 * Created on August 18, 2018, 7:13 AM
 */

#include "Coordenadas.h"

void setCoordenadas(Coordenadas *coordenadas, int x, int y){
    coordenadas->x = x;
    coordenadas->y = y;
}

void setCoordenadaX(Coordenadas *coordenadas, int x){
    coordenadas->x = x;
}

void setCoordenadaY(Coordenadas *coordenadas, int y){
    coordenadas->y = y;
}

int getCoordenadaX(Coordenadas *coordenadas){
    return coordenadas->x;
}

int getCoordenadaY(Coordenadas *coordenadas){
    return coordenadas->y;
}

int inteiroAleatorio(int min, int max){
    return (min + rand() % (max + 1 - min));
}
