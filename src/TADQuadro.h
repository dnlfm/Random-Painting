/* 
 * File:   TADQuadro.h
 * Author: Daniel Freitas Martins - 2304
 *
 * Created on August 16, 2018, 8:30 PM
 */

#ifndef TADQUADRO_H
#define	TADQUADRO_H

#include "TADFigura.h"

#define QUADRO_QTD_LINHAS 20
#define QUADRO_QTD_COLUNAS 80
#define MAX_TENTATIVAS 100000

#define SEM_CONFLITOS 0
#define CONFLITO_IMAGENS 1

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef struct TADQuadro{
        char tela[QUADRO_QTD_LINHAS][QUADRO_QTD_COLUNAS];
        enum Tipos_Figuras tipo_figura;
        int qtd_figuras;
    } TQuadro;    
    

    void prepararQuadroVazio(TQuadro *quadro);    
    int gerarTela(TQuadro *quadro, short flag_tamanho_variavel);
    void imprimirTela(TQuadro *quadro);    
    void imprimirImagensDisponiveis(enum Tamanhos tamanho);
    int desenharFigura(TQuadro *quadro, TFigura *figura, enum Tamanhos tamanho);
    void inserirFigura(TQuadro *quadro, TFigura *figura, Coordenadas *coordenadas_centro);
    short checarConflitos(TQuadro *quadro, TFigura *figura, Coordenadas *coordenadas_centro);
    
    
    void setTipoFigura(TQuadro *quadro, enum Tipos_Figuras figura_basica);
    void setQtdFiguras(TQuadro *quadro, int qtd_figuras);        
    
    enum Tipos_Figuras getTipoFigura(TQuadro *quadro);
    int getQtdFiguras(TQuadro *quadro);
    
    void pausarTemporariamente();
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* TADQUADRO_H */

