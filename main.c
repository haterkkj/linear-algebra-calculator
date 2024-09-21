#include <stdio.h>
#include <stdlib.h>

void printaMatriz(int linhas, int colunas, double matriz[linhas][colunas]){
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            printf("%f ", matriz[i][j]);
        }
        printf("\n");
    }
}

void escalonaPorGauss(int linhas, int colunas, double matriz[linhas][colunas]){
    for(int i = 0; i < linhas; i++){
        for(int j = i; j < colunas-2; j++){
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

void printaResolucaoSistema(int dimensao, double* sistemaResolvido){
    char letrasDimensoes[3] = {'x', 'y', 'z'};
    for(int i = 0; i < dimensao; i++){
        printf("%c = %f\t", letrasDimensoes[i], sistemaResolvido[i]);
    }
    printf("\n");
}

void determinaSeEhBase(int linhas, int colunas, double det, double matriz[linhas][colunas]){
    printf("A matriz:\n");
    printaMatriz(linhas, colunas, matriz);
    if(det != 0){
        printf("É base.");
    } else {
        printf("Não é base.");
    }
}

void calculaDeterminante(int linhas, int colunas, double matriz[linhas][colunas]){
    double det;
    if(linhas == 1 && colunas == 1){
        det = matriz[0][0];
    } else if (linhas == 2 && colunas == 2){
        double partePositiva, parteNegativa;
        partePositiva = matriz[0][0] * matriz[1][1];
        parteNegativa = matriz[0][1] * matriz[1][0];
        det = partePositiva - parteNegativa;
    } else if (linhas == 3 && colunas == 3){
        double partePositiva, parteNegativa;
        partePositiva = (matriz[0][0] * matriz[1][1] * matriz[2][2]) + (matriz[0][1] * matriz[1][2] * matriz[2][0]) + (matriz[0][2] * matriz[1][0] * matriz[2][1]);
        parteNegativa = (matriz[0][2] * matriz[1][1] * matriz[2][0]) + (matriz[0][0] * matriz[1][2] * matriz[2][1]) + (matriz[0][1] * matriz[1][0] * matriz[2][2]);
        det = partePositiva - parteNegativa;
    } else {
        printf("Ainda não conseguimos resolver matrizes maiores do que 3x3.\nNos desculpe... =(\n");
        return;
    }
    determinaSeEhBase(linhas, colunas, det, matriz);
}

void printaMenu(){
    printf(".....................................");
    printf(">\tCALCULADORA ALGEBRA LINEAR\t<\n\n");
    printf("1. Resolução de Sistemas Lineares\n");
    printf("2. Verificação de Injetividade, Sobrejetividade e Bijetividade\n");
    printf("3. Determinação de Bases\n");
    printf("4. Cálculo de Autovalores e Autovetores\n");
    printf("5. Diagonalização de Matrizes\n");
    printf("6. Sair\n\n");
    printf("> O que deseja fazer? ");
}

void printaPerguntaTamanhoMatriz(){
    printf("Qual é o tamanho da matriz que irá operar?\n");
    printf("1. Matriz 2x2\n");
    printf("2. Matriz 3x3\n");
}

void lerMatriz(int linhas, int colunas, double matriz[linhas][colunas]){
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; i++){
            scanf("%lf", &matriz[i][j]);
        }
    }
}

void filtraEntrada(int *entrada){
    int opcoesValidas[] = {1, 2, 3, 4, 5, 6};
    int entradaEhValida = 0;
    for(int i = 0; i < sizeof(opcoesValidas); i++){
        if(*entrada == opcoesValidas[i]){
            entradaEhValida = 1;
        }
    }
    while(entradaEhValida == 0){
        system("cls");
        printf("Infelizmente você escolheu uma opção inválida, tente novamente.");
        printaMenu();
        scanf("%d", &*entrada);
        for(int i = 0; i < sizeof(opcoesValidas); i++){
            if(*entrada == opcoesValidas[i]){
                entradaEhValida = 1;
            }
        }
    }
}

int main() {  
    while(1){
        int entrada;
        printaMenu();
        scanf("%d", &entrada);
        filtraEntrada(&entrada);
        if(entrada == 6){
            printf("Muito obrigado por usar nosso programa! =D\n");
            break;
        }
        printaPerguntaTamanhoMatriz();
        if(entrada == 1){
            entrada = 0;
            scanf("%d", &entrada);
            if(entrada == 2){
                double matriz[3][4] = {{1, 17, 4, 5},
                                       {2, 5, 7, 20},
                                       {0, 1, 3, 1}
                };
                //lerMatriz(3, 4, matriz);
                system("cls");
                printf("Matriz de entrada:\n\n");
                printaMatriz(3, 4, matriz);
                printf("\n");
            
                printf("Matriz escalonada:\n\n");
                escalonaPorGauss(3, 4, matriz);
                printaMatriz(3, 4, matriz);
                printf("\n");

                double* variaveis = resolveSistemaLinear(3, 4, matriz);
                printaResolucaoSistema(3, variaveis);
            }
        }
        
    }
    return 0;
}

