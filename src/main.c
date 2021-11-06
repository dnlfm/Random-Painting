/* 
 * File:   main.c
 * Author: Daniel Freitas Martins - 2304
 *
 * Created on August 14, 2018, 5:42 PM
 */

#include "TADQuadro.h"

/*
 * 
 */
int main(int argc, char** argv) {

    int opcao, opcao_menu2, opcao_menu3, qtd_figuras_desenhadas, flag_tamanho_variavel;
    enum Tamanhos tamanho;
    TFigura figura;
    TQuadro quadro;
    
    srand(time(NULL));
    prepararQuadroVazio(&quadro);
    prepararFiguraEmBranco(&figura);
    do{
        flag_tamanho_variavel = FALSO;
        printf("PROGRAMA GERADOR DE OBRA DE ARTE:\n"
                "==================================\n"
                "Escolha o tipo de figura basica a ser usada para criar a obra:\n"
                "1 - Asterisco simples;\n"
                "2 - Simbolo de soma com asteriscos;\n"
                "3 - Letra X com asteriscos;\n"
                "4 - Figuras aleatorias;\n"
                "5 - Opcao de obra de arte criada pelo aluno (The Village);\n"
                "6 - Figuras aleatorias 2 (inclui itens da obra The Village);\n"
                "7 - Mais opcoes...\n\n"
                "0 - Sair.\n\n"
                "(*) Digite o tipo de figura basica desejada: ");
        scanf("%d", &opcao);
        getchar();
        switch(opcao){
            case 1: case 2: case 3: case 4: case 5: case 6:
                prepararQuadroVazio(&quadro);
                setTipoFigura(&quadro, (opcao-1));
                printf("(*) Digite a quantidade de figuras (menor ou igual a zero para aleatorio): ");
                scanf("%d", &opcao);
                getchar();

                if(opcao > 100){
                    opcao = 100;
                } else{
                    if(opcao <= 0){
                        opcao = inteiroAleatorio(1, 100);
                    }
                }
                setQtdFiguras(&quadro, opcao);
                if(getTipoFigura(&quadro) != FIG_ASTERISCO_SIMPLES){
                    do{
                        printf("(*) Voce deseja que as figuras tenham tamanho variavel? (1 - Sim / 2 - Nao)\n-> ");
                        scanf("%d", &flag_tamanho_variavel);
                        getchar();                
                    } while(flag_tamanho_variavel != FALSO && flag_tamanho_variavel != VERDADEIRO);
                }
                do{
                    prepararQuadroVazio(&quadro);
                    qtd_figuras_desenhadas = gerarTela(&quadro, flag_tamanho_variavel);
                    if(qtd_figuras_desenhadas != getQtdFiguras(&quadro)){
                        printf("\n-> %d tentativas para encontrar uma posicao valida para uma das figuras nao foram suficientes...\n", MAX_TENTATIVAS);
                        printf("-> %d figuras foram desenhadas no quadro.\n", qtd_figuras_desenhadas);
                        printf("-> Interrompendo o desenho...\n\n");
                        pausarTemporariamente();
                    }
                    imprimirTela(&quadro);
                    do{
                        printf("(*) Voce deseja gerar um novo quadro com os mesmos parametros informados? (1 - Sim / 2 - Nao)\n-> ");
                        scanf("%d", &opcao);
                        getchar();
                        if(opcao != 1 && opcao != 2){
                            printf("\n-> Opcao invalida!\n\n");
                        }
                    } while(opcao != 1 && opcao != 2);
                } while(opcao != 2);
                
                break;
            case 7:
                do{
                    printf("PROGRAMA GERADOR DE OBRA DE ARTE: Menu 2\n"
                            "==================================\n"
                            "Escolha uma operacao:\n"
                            "1 - Mostrar figuras disponiveis;\n"
                            "2 - Mostrar quadro atual;\n"
                            "3 - Limpar quadro;\n"
                            "4 - Inserir figura no quadro;\n\n"
                            "0 - Voltar ao menu principal.\n\n"
                            "(*) Digite o numero da operacao a ser realizada: ");
                    scanf("%d", &opcao_menu2);
                    getchar();
                    switch(opcao_menu2){
                        case 1:
                            do{
                                printf("(*) Qual o tamanho padrao (apenas para figuras que suportam tamanho variavel):\n1 - Pequeno;\n2 - Medio;\n3 - Grande.\n-> ");
                                scanf("%d", &opcao_menu2);
                                getchar();
                            } while(opcao_menu2 != 1 && opcao_menu2 != 2 && opcao_menu2 != 3);
                            imprimirImagensDisponiveis(opcao_menu2);
                            break;
                        case 2:
                            imprimirTela(&quadro);
                            break;
                        case 3:
                            prepararQuadroVazio(&quadro);
                            break;
                        case 4:
                            
                            do{
                                printf("(*) Qual o tamanho padrao (apenas para figuras que suportam tamanho variavel):\n1 - Pequeno;\n2 - Medio;\n3 - Grande.\n-> ");
                                scanf("%d", &opcao_menu2);
                                getchar();
                            } while(opcao_menu2 != 1 && opcao_menu2 != 2 && opcao_menu2 != 3);
                            tamanho = opcao_menu2;
                            do{
                                prepararFiguraEmBranco(&figura);
                                printf("\n(*) Informe o numero da figura que voce deseja inserir:\n"
                                        "1 - Asterisco simples;\n"
                                        "2 - Simbolo de soma com asteriscos;\n"
                                        "3 - Letra X com asteriscos;\n"
                                        "4 - Figura aleatoria;\n"
                                        "5 - Boneco de ombreiras;\n"
                                        "6 - Boneco simples;\n"
                                        "7 - Grama;\n"
                                        "8 - Arvore (pinheiro);\n"
                                        "9 - Arvore (comum);\n"
                                        "10 - Casa;\n\n"
                                        "0 - Voltar.\n\n-> ");
                                scanf("%d", &opcao_menu3);
                                getchar();
                                if(opcao_menu3 == 4){
                                    opcao_menu3 = inteiroAleatorio(1, 10);
                                }
                                if(opcao_menu3 == 4){
                                    opcao_menu3 = 7;
                                }
                                switch(opcao_menu3){
                                    case 1: 
                                        setFiguraAsteriscoSimples(&figura);
                                        break;
                                    case 2: 
                                        setFiguraSinalSoma(&figura, tamanho);
                                        break;
                                    case 3:  
                                        setFiguraX(&figura, tamanho);
                                        break;
                                    case 4:
                                        // observe que neste ponto opcao_menu3 jamais será igual a 4...
                                        break;
                                    case 5:
                                        setFiguraEspecial(&figura, tamanho, BONECO1);
                                        break;
                                    case 6:
                                        setFiguraEspecial(&figura, tamanho, BONECO2);
                                        break;
                                    case 7:                                        
                                        setFiguraEspecial(&figura, tamanho, GRAMA);
                                        break;
                                    case 8:
                                        setFiguraEspecial(&figura, tamanho, ARVORE1);
                                        break;
                                    case 9:
                                        setFiguraEspecial(&figura, tamanho, ARVORE2);
                                        break;
                                    case 10:
                                        setFiguraEspecial(&figura, tamanho, CASA);
                                        break;
                                    case 0:
                                        break;
                                    default:
                                        printf("\n-> Opcao invalida!\n\n");
                                        continue;
                                }
                                if(opcao_menu3 != 0){
                                    if(!desenharFigura(&quadro, &figura, tamanho)){
                                        printf("\n-> %d tentativas para encontrar uma posicao valida para uma das figuras nao foram suficientes...\n", MAX_TENTATIVAS);
                                        printf("-> Nenhuma figura foi desenhada no quadro.\n");
                                        printf("-> Interrompendo o desenho...\n\n");
                                    } else{
                                        imprimirTela(&quadro);
                                    }
                                    pausarTemporariamente();
                                }
                                
                            } while(opcao_menu3 != 0);
                            
                            
                            break;
                        default:
                            printf("\n-> Opcao invalida!\n\n");
                    }                
                } while(opcao_menu2 != 0);
                break;
            case 0: 
                printf("\n-> Volte sempre!\n");
                pausarTemporariamente();
                break;
            default:
                printf("\n-> Opcao invalida!\n\n");
        }    
    } while(opcao != 0);
    
    
    
    return (EXIT_SUCCESS);
}