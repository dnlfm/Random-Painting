/* 
 * File:   TADFigura.c
 * Author: Daniel Freitas Martins - 2304
 *
 * Created on August 18, 2018, 8:22 AM
 */

#include "TADFigura.h"

/**
 * Atribui espaços em branco para os campos de uma figura, preparando-a para um novo desenho.
 * @param figura - Endereço para um objeto do tipo TFigura.
 */
void prepararFiguraEmBranco(TFigura *figura){
    int i, j;
    for(i = 0; i < FIGURA_QTD_LINHAS_MAX; i++){
        for(j = 0; j < FIGURA_QTD_COLUNAS_MAX; j++){
            figura->imagem[i][j] = ' ';
        }
    }
}

/**
 * Método responsável por preparar o desenho de uma figura Asterísco Simples.
 * @param figura - Endereço para um objeto do tipo TFigura.
 */
void setFiguraAsteriscoSimples(TFigura *figura){
    figura->imagem[X_CENTRO_FIGURA][Y_CENTRO_FIGURA] = '*';
}

/**
 * Método responsável por preparar o desenho de uma figura Sinal de Soma.
 * @param figura - Endereço para um objeto do tipo TFigura.
 * @param tamanho - Tamanho que indica a distância do centro até seus limites laterais (simetria). Isso serve para atribuir tamanho variável, dependendo do valor passado.
 */
void setFiguraSinalSoma(TFigura *figura, enum Tamanhos tamanho){
    int i, j, i_max, j_max;
    
    i_max = Y_CENTRO_FIGURA + tamanho;
    j_max = X_CENTRO_FIGURA + tamanho;
    
    for(i = (Y_CENTRO_FIGURA - tamanho); i <= i_max; i++){
        figura->imagem[i][X_CENTRO_FIGURA] = '*';
    }
    for(j = (X_CENTRO_FIGURA - tamanho); j <= j_max; j++){
        figura->imagem[Y_CENTRO_FIGURA][j] = '*';
    }
}

/**
 * Método responsável por preparar o desenho de uma figura X.
 * @param figura - Endereço para um objeto do tipo TFigura.
 * @param tamanho - Tamanho que indica a distância do centro até seus limites laterais (simetria). Isso serve para atribuir tamanho variável, dependendo do valor passado.
 */
void setFiguraX(TFigura *figura, enum Tamanhos tamanho){
    int i, j, i_max, i_min, j_max, j_min;
    
    i_max = Y_CENTRO_FIGURA + tamanho;
    i_min = Y_CENTRO_FIGURA - tamanho;
    j_max = X_CENTRO_FIGURA + tamanho;
    j_min = X_CENTRO_FIGURA - tamanho;
    
    j = j_min;
    for(i = i_min; i <= i_max; i++){
        figura->imagem[i][j] = '*';
        j++;
        if(j > j_max)
            break;
    }
    i = i_max;
    for(j = j_min; j <= j_max; j++){
        figura->imagem[i][j] = '*';
        i--;
        if(i < i_min)
            break;
    }
}

/**
 * Método responsável por preparar o desenho de uma figura Especial (possui variações).
 * @param figura - Endereço para um objeto do tipo TFigura.
 * @param tamanho - Tamanho que indica a distância do centro até seus limites laterais (simetria). Isso serve para atribuir tamanho variável, dependendo do valor passado.
 * @param variacao - Indica qual figura deverá ser desenhada dentre as disponíveis para a figura especial.
 */
void setFiguraEspecial(TFigura *figura, enum Tamanhos tamanho, enum Sub_Figuras_Especiais variacao){
    int i, j, i_max, i_min, j_max, j_min, inicio_i, inicio_j;
    
    if(variacao == ALEATORIO){
        if(tamanho == GRANDE)
            variacao = inteiroAleatorio(0, 5);
        else
            variacao = inteiroAleatorio(0, 2);
    }
    if(variacao >= ARVORE1 && variacao != ALEATORIO){
        tamanho = GRANDE;
    }
    i_max = Y_CENTRO_FIGURA + tamanho;
    i_min = Y_CENTRO_FIGURA - tamanho;
    j_max = X_CENTRO_FIGURA + tamanho;
    j_min = X_CENTRO_FIGURA - tamanho;
    switch(variacao){        
        case BONECO1:
            figura->imagem[Y_CENTRO_FIGURA-1][X_CENTRO_FIGURA] = 'O';
            figura->imagem[Y_CENTRO_FIGURA][X_CENTRO_FIGURA] = 'I';
            figura->imagem[Y_CENTRO_FIGURA][X_CENTRO_FIGURA+1] = '|';
            figura->imagem[Y_CENTRO_FIGURA-1][X_CENTRO_FIGURA+1] = '_';
            figura->imagem[Y_CENTRO_FIGURA][X_CENTRO_FIGURA-1] = '|';
            figura->imagem[Y_CENTRO_FIGURA-1][X_CENTRO_FIGURA-1] = '_';
            figura->imagem[Y_CENTRO_FIGURA+1][X_CENTRO_FIGURA+1] = '\\';
            figura->imagem[Y_CENTRO_FIGURA+1][X_CENTRO_FIGURA-1] = '/';
            break;
        case BONECO2:
            figura->imagem[Y_CENTRO_FIGURA-1][X_CENTRO_FIGURA] = 'o';
            figura->imagem[Y_CENTRO_FIGURA][X_CENTRO_FIGURA] = 'I';
            figura->imagem[Y_CENTRO_FIGURA][X_CENTRO_FIGURA+1] = '\\';
            figura->imagem[Y_CENTRO_FIGURA][X_CENTRO_FIGURA-1] = '/';
            figura->imagem[Y_CENTRO_FIGURA+1][X_CENTRO_FIGURA+1] = '\\';
            figura->imagem[Y_CENTRO_FIGURA+1][X_CENTRO_FIGURA-1] = '/';
            break;
        case GRAMA:
            for(j = j_min; j <= j_max; j++){
                figura->imagem[Y_CENTRO_FIGURA][j] = (j % 3 == 0) ? 'v' : 'w';
            }
            break;
        case ARVORE1:
            for(j = j_min; j <= j_max; j++){
                figura->imagem[Y_CENTRO_FIGURA+3][j] = (j % 3 == 0) ? 'v' : 'w';
            }            
            figura->imagem[Y_CENTRO_FIGURA+2][X_CENTRO_FIGURA-1] = '|';
            figura->imagem[Y_CENTRO_FIGURA+2][X_CENTRO_FIGURA+1] = '|';
            figura->imagem[Y_CENTRO_FIGURA+1][X_CENTRO_FIGURA-3] = '/';
            figura->imagem[Y_CENTRO_FIGURA+1][X_CENTRO_FIGURA-2] = '|';
            figura->imagem[Y_CENTRO_FIGURA+1][X_CENTRO_FIGURA-1] = 'o';
            figura->imagem[Y_CENTRO_FIGURA+1][X_CENTRO_FIGURA] = '|';
            figura->imagem[Y_CENTRO_FIGURA+1][X_CENTRO_FIGURA+1] = '|';
            figura->imagem[Y_CENTRO_FIGURA+1][X_CENTRO_FIGURA+2] = '|';
            figura->imagem[Y_CENTRO_FIGURA+1][X_CENTRO_FIGURA+3] = '\\';
            figura->imagem[Y_CENTRO_FIGURA][X_CENTRO_FIGURA-2] = '/';
            figura->imagem[Y_CENTRO_FIGURA][X_CENTRO_FIGURA-1] = '|';
            figura->imagem[Y_CENTRO_FIGURA][X_CENTRO_FIGURA] = '|';
            figura->imagem[Y_CENTRO_FIGURA][X_CENTRO_FIGURA+1] = 'o';
            figura->imagem[Y_CENTRO_FIGURA][X_CENTRO_FIGURA+2] = '\\';
            figura->imagem[Y_CENTRO_FIGURA-1][X_CENTRO_FIGURA] = '|';
            figura->imagem[Y_CENTRO_FIGURA-1][X_CENTRO_FIGURA-1] = '/';
            figura->imagem[Y_CENTRO_FIGURA-1][X_CENTRO_FIGURA+1] = '\\';
            figura->imagem[Y_CENTRO_FIGURA-2][X_CENTRO_FIGURA] = '*';
            break;
        case CASA:
            i_max = Y_CENTRO_FIGURA + 3;
            i_min = Y_CENTRO_FIGURA - 3;
            j_max = X_CENTRO_FIGURA + 3;
            j_min = X_CENTRO_FIGURA - 3;
            for(i = i_min+2; i <= i_max; i++){
                figura->imagem[i][j_min] = '|';
                figura->imagem[i][j_max] = '|';
            }
            figura->imagem[i_min+1][j_min] = '_';
            figura->imagem[i_min+1][j_max] = '_';
            figura->imagem[i_min+1][j_min+1] = '/';
            figura->imagem[i_min+1][j_max-1] = '\\';
            for(j = j_min; j <= j_max; j++){
                if(j > j_min+1 && j < j_max-1){
                    figura->imagem[i_min][j] = '_';
                }
                figura->imagem[i_max][j] = '-';
            }
            figura->imagem[i_min+3][j_min+1] = '[';
            figura->imagem[i_min+3][j_min+2] = ']';
            figura->imagem[i_min+3][j_max-1] = ']';
            figura->imagem[i_min+3][j_max-2] = '[';
            figura->imagem[i_max-1][j_max-1] = ']';
            figura->imagem[i_max-1][j_max-2] = '[';
            figura->imagem[i_max-1][X_CENTRO_FIGURA-1] = '|';
            figura->imagem[i_max-2][X_CENTRO_FIGURA-1] = '\\';
            figura->imagem[i_max-1][X_CENTRO_FIGURA-2] = '|';
            figura->imagem[i_max-2][X_CENTRO_FIGURA-2] = '/';
            break;
        case ARVORE2:
            figura->imagem[Y_CENTRO_FIGURA+3][X_CENTRO_FIGURA-3] = '_';
            figura->imagem[Y_CENTRO_FIGURA+3][X_CENTRO_FIGURA-2] = '/';
            figura->imagem[Y_CENTRO_FIGURA+3][X_CENTRO_FIGURA-1] = '|';
            figura->imagem[Y_CENTRO_FIGURA+3][X_CENTRO_FIGURA] = '|';
            figura->imagem[Y_CENTRO_FIGURA+3][X_CENTRO_FIGURA+1] = '|';
            figura->imagem[Y_CENTRO_FIGURA+3][X_CENTRO_FIGURA+2] = '\\';
            figura->imagem[Y_CENTRO_FIGURA+3][X_CENTRO_FIGURA+3] = '_';
            figura->imagem[Y_CENTRO_FIGURA+2][X_CENTRO_FIGURA-1] = '|';
            figura->imagem[Y_CENTRO_FIGURA+2][X_CENTRO_FIGURA] = '@';
            figura->imagem[Y_CENTRO_FIGURA+2][X_CENTRO_FIGURA+1] = '|';
            figura->imagem[Y_CENTRO_FIGURA+1][X_CENTRO_FIGURA-1] = '*';
            figura->imagem[Y_CENTRO_FIGURA+1][X_CENTRO_FIGURA] = '*';
            figura->imagem[Y_CENTRO_FIGURA+1][X_CENTRO_FIGURA+1] = '*';
            figura->imagem[Y_CENTRO_FIGURA][X_CENTRO_FIGURA-2] = '*';
            figura->imagem[Y_CENTRO_FIGURA][X_CENTRO_FIGURA-1] = '*';
            figura->imagem[Y_CENTRO_FIGURA][X_CENTRO_FIGURA] = '*';
            figura->imagem[Y_CENTRO_FIGURA][X_CENTRO_FIGURA+1] = '*';
            figura->imagem[Y_CENTRO_FIGURA][X_CENTRO_FIGURA+2] = '*';
            figura->imagem[Y_CENTRO_FIGURA-1][X_CENTRO_FIGURA] = '*';
            figura->imagem[Y_CENTRO_FIGURA-1][X_CENTRO_FIGURA-1] = '*';
            figura->imagem[Y_CENTRO_FIGURA-1][X_CENTRO_FIGURA+1] = '*';
            figura->imagem[Y_CENTRO_FIGURA-2][X_CENTRO_FIGURA] = '*';
    }
    
    
}

/**
 * Método responsável por imprimir a figura.
 * @param figura - Endereço para um objeto do tipo TFigura.
 */
void imprimirFIgura(TFigura *figura){
    int i, j;
    
    for(i = 0; i < FIGURA_QTD_LINHAS_MAX; i++){
        for(j = 0; j < FIGURA_QTD_COLUNAS_MAX; j++){
            printf("%c", figura->imagem[i][j]);
        }
        printf("\n");
    }
}

/**
 * Função responsável por desenhar um caractere na figura.
 * @param figura - Endereço para um objeto do tipo TFigura que irá ter seu conteúdo desenhado.
 * @param item - Item a ser desenhado.
 * @param coordenadas - Posição em que o item será desenhado.
 * @return 1 se a operação foi realizada com sucesso; 0 caso contrário, indicando que uma das coordenadas foi inválida.
 */
short setCharEmPosicao(TFigura *figura, char item, Coordenadas *coordenadas){
    int x, y; 
    x = getCoordenadaX(coordenadas);
    y = getCoordenadaY(coordenadas);
    
    if(x < 0 || y < 0 || x == FIGURA_QTD_LINHAS_MAX || y == FIGURA_QTD_COLUNAS_MAX){
        return 0;
    }
    figura->imagem[x][y] = item;
    return 1;
}
