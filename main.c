#include <stdio.h>
#include <stdlib.h>

int printaMenu(){
    printf("- - - - - - - - - - - - - - - - - - - - -\n");
    printf(">\tCALCULADORA ALGEBRA LINEAR\t<\n");
    printf("- - - - - - - - - - - - - - - - - - - - -\n");
    printf("1. Resolução de Sistemas Lineares\n");
    printf("2. Verificação de Injetividade, Sobrejetividade e Bijetividade\n");
    printf("3. Determinação de Bases\n");
    printf("4. Cálculo de Autovalores e Autovetores\n");
    printf("5. Diagonalização de Matrizes\n");
    printf("6. Sair\n");
    printf("- - - - - - - - - - - - - - - - - - - - -\n");
    printf("> O que deseja fazer? ");
    
    int entrada;
    scanf("%d", &entrada);
    return entrada;
}

void printaMatriz(int linhas, int colunas, double matriz[linhas][colunas]){
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            printf("%f ", matriz[i][j]);
        }
        printf("\n");
    }
}

void printaConjuntoDeVetores(int linhas, int colunas, double matriz[linhas][colunas]){
    for(int i = 0; i < linhas; i++){
        printf("v%d = (", i+1);
        for(int j = 0; j < colunas; j++){
            if(j == colunas-1){
                printf("%f)", matriz[i][j]);
            } else {
                printf("%f, ", matriz[i][j]);
            }
        }
        printf("\n");
    }
}

void printaResolucaoSistema(int dimensao, double* sistemaResolvido){
    char letrasDimensoes[3] = {'x', 'y', 'z'};
    for(int i = 0; i < dimensao; i++){
        printf("%c = %f\t", letrasDimensoes[i], sistemaResolvido[i]);
    }
    printf("\n");
}

void lerMatriz(int linhas, int colunas, double matriz[linhas][colunas]){
    printf("> Insira os elementos da matriz: (informe apenas os coeficientes e a constante)\n");
    printf("Ex.: 2x+3y-z=5 -> 2 3 -1 5\n");
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            scanf("%lf", &matriz[i][j]);
        }
    }
}

void lerConjuntoDeVetores(int linhas, int colunas, double matriz[linhas][colunas]){
    for(int i = 0; i < linhas; i++){
        printf("> Insira os elementos do %d° conjunto de vetores: (informe apenas números)\n", i+1);
        printf("Ex.: (2, 3, 4) -> 2 3 4\n");
        for(int j = 0; j < colunas; j++){
            scanf("%lf", &matriz[i][j]);
        }
        printf("\n");
    }
}

void escalonaPorGauss(int linhas, int colunas, double matriz[linhas][colunas]){
    for(int j = 0; j < colunas-2; j++){
        for(int i = j; i < linhas; i++){
            if(matriz[i][j] != 0){
                if(i != j){
                    for(int k = 0; k < colunas; k++){
                        double temp = matriz[i][k];
                        matriz[i][k] = matriz[j][k];
                        matriz[j][k] = temp;
                    }
                }
                for(int m = j + 1; m < linhas; m++){
                    double fatorEliminacao = -matriz[m][j] / matriz[j][j];
                    for(int n = j; n < colunas; n++){
                        matriz[m][n] = (fatorEliminacao * matriz[j][n]) + matriz[m][n] ;
                    }
                }
                break;
            }
        }
    }
}

double* resolveSistemaLinear(int linhas, int colunas, double matriz[linhas][colunas]){
    double* variaveis = (double*)calloc(linhas, sizeof(double));
    if (variaveis == NULL) {
        printf("Houve um erro ao tentar alocar memória para espaço das variáveis :: CODIGO ERRO {00x}\n");
        exit(1);
    }
    for(int i = linhas-1; i >= 0; i--){
        variaveis[i] = matriz[i][colunas-1];
        if(i < linhas - 1){
            for(int j = linhas; j > i; j--){
                variaveis[i] -= matriz[i][j] * variaveis[j];
            }
        }
        variaveis[i]/=matriz[i][i];
    }
    return variaveis;
}

void determinaSeEhBase(int linhas, int colunas, double determinante, double matriz[linhas][colunas]){
    printf("Os conjuntos:\n");
    printaConjuntoDeVetores(linhas, colunas, matriz);
    if(determinante != 0){
        printf("Formam base de R%d.\n", linhas);
    } else {
        printf("Não formam uma base de R%d.\n", linhas);
    }
}

double calculaDeterminante(int linhas, int colunas, double matriz[linhas][colunas]){
    double det;
    if(linhas == 1){
        det = matriz[0][0];
    } else if (linhas == 2){
        double partePositiva, parteNegativa;
        partePositiva = matriz[0][0] * matriz[1][1];
        parteNegativa = matriz[0][1] * matriz[1][0];
        det = partePositiva - parteNegativa;
    } else if (linhas == 3){
        double partePositiva, parteNegativa;
        partePositiva = (matriz[0][0] * matriz[1][1] * matriz[2][2]) + (matriz[0][1] * matriz[1][2] * matriz[2][0]) + (matriz[0][2] * matriz[1][0] * matriz[2][1]);
        parteNegativa = (matriz[0][2] * matriz[1][1] * matriz[2][0]) + (matriz[0][0] * matriz[1][2] * matriz[2][1]) + (matriz[0][1] * matriz[1][0] * matriz[2][2]);
        det = partePositiva - parteNegativa;
    } else {
        printf("Ainda não conseguimos resolver matrizes maiores do que 3x3.\nNos desculpe... =(\n");
    }
    return det;
}

int main() {  
    while(1){
        int entrada;
        entrada = printaMenu();
        switch (entrada){
            case 1:
                printf("Deseja operar com matriz 2x2 ou 3x3?\n1. 2x2\n2. 3x3\n> Escolha uma das opções: ");
                int tamanhoMatriz;
                scanf("%d", &tamanhoMatriz);
                if(tamanhoMatriz == 1){
                    double matriz[2][3];
                    system("cls");
                    lerMatriz(2, 3, matriz);
                    system("cls");
                    double det = calculaDeterminante(2, 3, matriz);
                    if(det == 0){
                        printf("Está matriz não pode ser escalonada.\n");
                        printf("Motivo: dependência linear.\n");
                        break;
                    }

                    printf("Matriz original:\n");
                    printaMatriz(2, 3, matriz);
                    
                    printf("\nMatriz escalonada:\n");
                    escalonaPorGauss(2, 3, matriz);
                    printaMatriz(2, 3, matriz);

                    printf("\nResolução do sistema:\n");
                    double *variaveis = resolveSistemaLinear(2, 3, matriz);
                    printaResolucaoSistema(2, variaveis);
                    free(variaveis);
                } else if (tamanhoMatriz == 2){
                    double matriz[3][4];
                    system("cls");
                    lerMatriz(3, 4, matriz);
                    system("cls");
                    double det = calculaDeterminante(3, 4, matriz);
                    printf("%lf\n\n", det);
                    if(det == 0){
                        printf("Está matriz não pode ser escalonada.\n");
                        printf("Motivo: dependência linear.\n");
                        break;
                    }

                    printf("Matriz original:\n");
                    printaMatriz(3, 4, matriz);

                    printf("\nMatriz escalonada:\n");
                    escalonaPorGauss(3, 4, matriz);
                    printaMatriz(3, 4, matriz);

                    printf("\nResolução do sistema:\n");
                    double *variaveis = resolveSistemaLinear(3, 4, matriz);
                    printaResolucaoSistema(3, variaveis);
                    free(variaveis);
                } else {
                    system("cls");
                    printf("Opção Inválida.\n");
                }
                break;
            case 2:
                printf("Deseja verificar uma matriz 2x2 ou 3x3?\n1. 2x2\n2. 3x3\n> Escolha uma das opções: ");
                int dimensaoMatrizQuadrada;
                scanf("%d", &dimensaoMatrizQuadrada);
                if(dimensaoMatrizQuadrada == 1){
                    double matriz[2][2];
                    system("cls");
                    lerMatriz(2, 2, matriz);
                    system("cls");

                    double det = calculaDeterminante(2, 2, matriz);
                    printf("A matriz: \n");
                    printaMatriz(2, 2, matriz);
                    printf("\n");
                    if(det != 0){
                        printf("É injetora;\n");
                        printf("É sobrejetora;\n");
                        printf("É bijetora.\n");
                    } else {
                        printf("Não é injetora;\n");
                        printf("Não é sobrejetora;\n");
                        printf("Não é bijetora.\n");
                    }
                } else if (dimensaoMatrizQuadrada == 2){
                    double matriz[3][3];
                    system("cls");
                    lerMatriz(3, 3, matriz);
                    system("cls");

                    double det = calculaDeterminante(3, 3, matriz);
                    printf("A matriz: \n");
                    printaMatriz(3, 3, matriz);
                    printf("\n");
                    if(det != 0){
                        printf("É injetora;\n");
                        printf("É sobrejetora;\n");
                        printf("É bijetora.\n");
                    } else {
                        printf("Não é injetora;\n");
                        printf("Não é sobrejetora;\n");
                        printf("Não é bijetora.\n");
                    }
                } else {
                    system("cls");
                    printf("Opção Inválida.\n");
                }
                break;
            case 3:
                printf("Irá determinar uma base em R2 ou R3?\n1. R2\n2. R3\n> Escolha uma das opções: ");
                int dimensao;
                scanf("%d", &dimensao);
                if(dimensao == 1){
                    double matriz[2][2];
                    system("cls");
                    lerConjuntoDeVetores(2, 2, matriz);
                    system("cls");
                    double det = calculaDeterminante(2, 2, matriz);
                    determinaSeEhBase(2, 2, det, matriz);
                } else if (dimensao == 2){
                    double matriz[3][3];
                    system("cls");
                    lerConjuntoDeVetores(3, 3, matriz);
                    system("cls");
                    double det = calculaDeterminante(3, 3, matriz);
                    determinaSeEhBase(3, 3, det, matriz);
                } else {
                    system("cls");
                    printf("Opção Inválida.\n");
                }
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                system("cls");
                printf("Muito obrigado por usar nosso programa! =D\n"); 
                printf("Encerrando...");
                exit(1);
                break;
            default:
                system("cls");
                printf("Você selecionou uma opção inválida.\n");
                break;
        }
        getchar();
    }
    return 0;
}

