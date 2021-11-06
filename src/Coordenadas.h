/* 
 * File:   Coordenadas.h
 * Author: Daniel Freitas Martins - 2304
 *
 * Created on August 18, 2018, 7:13 AM
 */

#ifndef COORDENADAS_H
#define	COORDENADAS_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define VERDADEIRO 1
#define FALSO 2

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct {
        int x;
        int y;
    } Coordenadas;

    void setCoordenadas(Coordenadas *coordenadas, int x, int y);
    void setCoordenadaX(Coordenadas *coordenadas, int x);
    void setCoordenadaY(Coordenadas *coordenadas, int y);
    
    int getCoordenadaX(Coordenadas *coordenadas);
    int getCoordenadaY(Coordenadas *coordenadas);
    
    int inteiroAleatorio(int min, int max);

#ifdef	__cplusplus
}
#endif

#endif	/* COORDENADAS_H */

