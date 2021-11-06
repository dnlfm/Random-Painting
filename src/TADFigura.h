/* 
 * File:   TADFigura.h
 * Author: Daniel Freitas Martins - 2304
 *
 * Created on August 18, 2018, 8:22 AM
 */

#ifndef TADFIGURA_H
#define	TADFIGURA_H

#include "Coordenadas.h"

#define FIGURA_QTD_LINHAS_MAX 7
#define FIGURA_QTD_COLUNAS_MAX 7
#define X_CENTRO_FIGURA ((int)FIGURA_QTD_COLUNAS_MAX/2)
#define Y_CENTRO_FIGURA ((int)FIGURA_QTD_LINHAS_MAX/2)

#ifdef	__cplusplus
extern "C" {
#endif

    enum Tipos_Figuras {FIG_ASTERISCO_SIMPLES, FIG_SINAL_SOMA, FIG_X, FIG_ALEATORIAS, FIG_ESPECIAL, FIG_ALEATORIAS_2};
    enum Tamanhos {PONTUAL, PEQUENO, MEDIO, GRANDE};
    enum Sub_Figuras_Especiais {BONECO1, BONECO2, GRAMA, ARVORE1, CASA, ARVORE2, ALEATORIO};
    
    typedef struct TADFigura{
        char imagem[FIGURA_QTD_LINHAS_MAX][FIGURA_QTD_COLUNAS_MAX];
    } TFigura;
    
    void prepararFiguraEmBranco(TFigura *figura);
    void setFiguraAsteriscoSimples(TFigura *figura);
    void setFiguraSinalSoma(TFigura *figura, enum Tamanhos tamanho);
    void setFiguraX(TFigura *figura, enum Tamanhos tamanho);
    void setFiguraEspecial(TFigura *figura, enum Tamanhos tamanho, enum Sub_Figuras_Especiais variacao);
    void imprimirFIgura(TFigura *figura);
    short setCharEmPosicao(TFigura *figura, char item, Coordenadas *coordenadas);    
    


#ifdef	__cplusplus
}
#endif

#endif	/* TADFIGURA_H */

