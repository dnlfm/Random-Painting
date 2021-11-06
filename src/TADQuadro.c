/*
 * File:   TADQuadro.c
 * Author: Daniel Freitas Martins - 2304
 *
 * Created on August 16, 2018, 8:31 PM
 */


#include "TADQuadro.h"

/**
 * Método responsável por "limpar" a tela do quadro para que uma nova obra de arte seja grafada
 * @param quadro - Endereço de um objeto do tipo TQuadro.
 */
void prepararQuadroVazio(TQuadro *quadro){
    int i, j;
    for(j = 0; j < QUADRO_QTD_COLUNAS; j++){
        quadro->tela[0][j] = '-';
        quadro->tela[QUADRO_QTD_LINHAS-1][j] = '-';
    }
    for(i = 1; i < QUADRO_QTD_LINHAS-1; i++){
        quadro->tela[i][0] = '|';
        quadro->tela[i][QUADRO_QTD_COLUNAS-1] = '|';
    }
    for(i = 1;i < QUADRO_QTD_LINHAS-1; i++){
        for(j = 1; j < QUADRO_QTD_COLUNAS-1; j++){
            quadro->tela[i][j] = ' ';
        }
    }
}

/**
 * Função responsável por iterar entre a quantidade de figuras e construir a obra de arte pelas chamadas da função desenhaFigura(...).
 * @param quadro - Endereço para um objeto do tipo TQuadro.
 * @param flag_tamanho_variavel - Flag que indica se o tamanho das figuras devem variar. 1 - Tamanho variável (exceto PONTUAL); 0 - Tamanho fixo padrão (PEQUENO).
 * @return A quantidade de figuras desenhadas. Se esta quantidade for diferente da quantidade pedida, significa que um limite de tentativas para encontrar a posição de alguma figura não foi suficiente para tal.
 */
int gerarTela(TQuadro *quadro, short flag_tamanho_variavel){
    enum Tamanhos tamanho;
    TFigura figura;
    int qtd_figuras;
    enum Tipos_Figuras figura_basica;

    for(qtd_figuras = 0; qtd_figuras < quadro->qtd_figuras; qtd_figuras++){
        if(quadro->tipo_figura == FIG_ALEATORIAS){
            figura_basica = (rand() % 3);
        } else{
            if(quadro->tipo_figura == FIG_ALEATORIAS_2){ // considera também a figura criada pelo aluno.
                figura_basica = (rand() % 4);
            } else{
                figura_basica = quadro->tipo_figura;
            }
        }
        prepararFiguraEmBranco(&figura);
        switch(figura_basica){
            case FIG_ASTERISCO_SIMPLES:
                tamanho = PONTUAL;
                setFiguraAsteriscoSimples(&figura);
                break;
            case FIG_SINAL_SOMA:
                tamanho = (flag_tamanho_variavel == VERDADEIRO) ? (rand() % 3 + 1) : PEQUENO;
                setFiguraSinalSoma(&figura, tamanho);
                break;
            case FIG_X:
                tamanho = (flag_tamanho_variavel == VERDADEIRO) ? (rand() % 3 + 1) : PEQUENO;
                setFiguraX(&figura, tamanho);
                break;
            case FIG_ESPECIAL: case FIG_ALEATORIAS: // Atenção: FIG_ALEATORIAS está sendo usado aqui apenas para servir de valor aleatório para FIG_ESPECIAL
                                                                                        // O motivo de estar desta forma é evitar o remapeamento da definição do enum Tipos_Figuras, simplificando o problema.
                tamanho = (flag_tamanho_variavel == VERDADEIRO) ? (rand() % 3 + 1) : PEQUENO;
                setFiguraEspecial(&figura, tamanho, ALEATORIO);
                break;
        }
        if(!desenharFigura(quadro, &figura, tamanho)){
            break;
        }
    }
    return qtd_figuras;
}

/**
 * Função responsável por desenhar uma das figuras na tela de um quadro.
 * @param quadro - Endereço para um objeto do tipo TQuadro.
 * @param figura - Endereço de um objeto TFigura representando a figura a ser desenhada.
 * @param tamanho - Tamanho que indica a distância do centro até seus limites laterais (simetria). Isso serve para atribuir tamanho variável, dependendo do valor passado.
 * @return 1 se a operação ocorreu com sucesso; 0 caso contrário, representando que um limite de tentativas foi alcançado e uma imagem não pode ser desenhada.
 */
int desenharFigura(TQuadro *quadro, TFigura *figura, enum Tamanhos tamanho){
    Coordenadas coordenadas_centro;
    int tentativas;
    short flag_conflito;

    tentativas = 0;
    do{
        // Encontrando nova posição considerando a limitação das bordas do quadro
        setCoordenadas(&coordenadas_centro, inteiroAleatorio(tamanho + 1, 18 - tamanho), inteiroAleatorio(tamanho + 1, 78 - tamanho));

        flag_conflito = checarConflitos(quadro, figura, &coordenadas_centro);
        if(tentativas >= MAX_TENTATIVAS){
            return 0;
        }
        tentativas++; // Contabiliza a quantidade de tentativas para encontrar uma posição válida.
    } while(flag_conflito == CONFLITO_IMAGENS);

    inserirFigura(quadro, figura, &coordenadas_centro);

    return 1;
}

/**
 * Método responsável por desenhar uma das figuras na tela de um quadro, dadas suas coordenadas x e y. Atenção: Neste método não há checagem de conflitos, é uma operação direta.
 * @param quadro - Endereço para um objeto do tipo TQuadro.
 * @param figura - Endereço de um objeto TFigura representando a figura a ser desenhada.
 * @param coordenadas_centro - Endereço de um elemento que possui as coordenadas x e y do centro da figura.
 */
void inserirFigura(TQuadro *quadro, TFigura *figura, Coordenadas *coordenadas_centro){
    int i, j, x_posicao, y_posicao;

    x_posicao = getCoordenadaX(coordenadas_centro);
    y_posicao = getCoordenadaY(coordenadas_centro);

    for(i = 0; i < FIGURA_QTD_LINHAS_MAX; i++){
        for(j = 0; j < FIGURA_QTD_COLUNAS_MAX; j++){
            if(figura->imagem[i][j] != ' '){
                quadro->tela[x_posicao - (X_CENTRO_FIGURA - i)][y_posicao - (Y_CENTRO_FIGURA - j)] = figura->imagem[i][j];
            }
        }
    }
}

/**
 * Função responsável por checar conflitos, dadas as coordenadas e o tipo da figura a ser desenhada no quadro.
 * @param quadro - Endereço para um objeto do tipo TQuadro.
 * @param figura - Endereço de um objeto TFigura representando a figura a ser avaliada.
 * @param coordenadas_centro - Endereço de um elemento que possui as coordenadas x e y do centro da figura.
 * @return SEM_CONFLITOS caso não haja conflitos entre imagens; CONFLITO_IMAGENS caso contrário.
 */
short checarConflitos(TQuadro *quadro, TFigura *figura, Coordenadas *coordenadas_centro){
    int x_posicao, y_posicao, x_fig, y_fig, i, j;

    x_posicao = getCoordenadaX(coordenadas_centro);
    y_posicao = getCoordenadaY(coordenadas_centro);

    for(i = 0; i < FIGURA_QTD_LINHAS_MAX; i++){
        for(j = 0; j < FIGURA_QTD_COLUNAS_MAX; j++){
            if(figura->imagem[i][j] != ' '){
                if(quadro->tela[x_posicao - (X_CENTRO_FIGURA - i)][y_posicao - (Y_CENTRO_FIGURA - j)] != ' '){
                    return CONFLITO_IMAGENS;
                }
            }
        }
    }

    return SEM_CONFLITOS;
}

/**
 * Método responsável pela impressão do quadro.
 * @param quadro - Endereço para um objeto do tipo TQuadro.
 */
void imprimirTela(TQuadro *quadro){
    int i, j;
    printf("Eis a obra de arte...\n");
    for(i = 0; i < QUADRO_QTD_LINHAS; i++){
        for(j = 0; j < QUADRO_QTD_COLUNAS; j++){
            printf("%c", quadro->tela[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Método responsável por mostrar uma das figuras disponíveis para desenhar no quadro.
 * @param tamanho - Tamanho que indica a distância do centro até seus limites laterais (simetria). Isso serve para atribuir tamanho variável, dependendo do valor passado.
 */
void imprimirImagensDisponiveis(enum Tamanhos tamanho){
    TFigura figura;
    prepararFiguraEmBranco(&figura);
    printf("--- (1) ---\n");
    setFiguraAsteriscoSimples(&figura);
    imprimirFIgura(&figura);
    pausarTemporariamente();
    prepararFiguraEmBranco(&figura);
    printf("--- (2) --- (3 tamanhos disponiveis)\n");
    setFiguraSinalSoma(&figura, tamanho);
    imprimirFIgura(&figura);
    pausarTemporariamente();
    prepararFiguraEmBranco(&figura);
    printf("--- (3) --- (3 tamanhos disponiveis)\n");
    setFiguraX(&figura, tamanho);
    imprimirFIgura(&figura);
    pausarTemporariamente();
    prepararFiguraEmBranco(&figura);
    printf("--- (4) ---\n");
    setFiguraEspecial(&figura, tamanho, BONECO1);
    imprimirFIgura(&figura);
    pausarTemporariamente();
    prepararFiguraEmBranco(&figura);
    printf("--- (5) ---\n");
    setFiguraEspecial(&figura, tamanho, BONECO2);
    imprimirFIgura(&figura);
    pausarTemporariamente();
    prepararFiguraEmBranco(&figura);
    printf("--- (6) --- (3 tamanhos disponiveis)\n");
    setFiguraEspecial(&figura, tamanho, GRAMA);
    imprimirFIgura(&figura);
    pausarTemporariamente();
    prepararFiguraEmBranco(&figura);
    printf("--- (7) ---\n");
    setFiguraEspecial(&figura, tamanho, ARVORE1);
    imprimirFIgura(&figura);
    pausarTemporariamente();
    prepararFiguraEmBranco(&figura);
    printf("--- (8) ---\n");
    setFiguraEspecial(&figura, tamanho, CASA);
    imprimirFIgura(&figura);
    pausarTemporariamente();
    prepararFiguraEmBranco(&figura);
    printf("--- (9) ---\n");
    setFiguraEspecial(&figura, tamanho, ARVORE2);
    imprimirFIgura(&figura);
    pausarTemporariamente();
    printf("-------------\n\n");

}

/**
 * Método responsável por inserir o tipo de figura básica a ser desenhada.
 * @param quadro - Endereço para um objeto do tipo TQuadro.
 * @param figura_basica - O tipo de figura báscia a ser desenhada.
 */
void setTipoFigura(TQuadro *quadro, enum Tipos_Figuras figura_basica){
    quadro->tipo_figura = figura_basica;
}

/**
 * Método responsável por inserir a quantidade de figuras a serem desenhadas.
 * @param quadro - Endereço para um objeto do tipo TQuadro.
 * @param qtd_figuras - A quantidade de figuras a serem desenhadas.
 */
void setQtdFiguras(TQuadro *quadro, int qtd_figuras){
    quadro->qtd_figuras = qtd_figuras;
}

/**
 * Função responsável por retornar o tipo de figura informado.
 * @param quadro - Endereço para um objeto do tipo TQuadro.
 * @return O tipo de figura básica a ser desenhada.
 */
enum Tipos_Figuras getTipoFigura(TQuadro *quadro){
    return quadro->tipo_figura;
}

/**
 * Função responsável por retornar a quantidade de figuras pedida para serem desenhadas.
 * @param quadro - Endereço para um objeto do tipo TQuadro.
 * @return A quantidade de figuras a serem desenhadas.
 */
int getQtdFiguras(TQuadro *quadro){
    return quadro->qtd_figuras;
}

/**
 * Método responsável por pausar temporariamente (substitui o equivalente a system("pause") no windows).
 */
void pausarTemporariamente(){
    printf("(*) Pressione ENTER para continuar...\n");
    getchar();
}
