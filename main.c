#include <stdio.h>
#include <stdlib.h>

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

void printaMatriz(int linhas, int colunas, double matriz[linhas][colunas]){
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            printf("%f ", matriz[i][j]);
        }
        printf("\n");
    }
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
    if(linhas == 1 && colunas == 1){
        double det = matriz[0][0];
        determinaSeEhBase(linhas, colunas, det, matriz);
    } else if (linhas == 2 && colunas == 2){
        double partePositiva, parteNegativa, det;
        partePositiva = matriz[0][0] * matriz[1][1];
        parteNegativa = matriz[0][1] * matriz[1][0];
        det = partePositiva - parteNegativa;
        determinaSeEhBase(linhas, colunas, det, matriz);
    } else if (linhas == 3 && colunas == 3){
        double partePositiva, parteNegativa, det;
        partePositiva = (matriz[0][0] * matriz[1][1] * matriz[2][2]) + (matriz[0][1] * matriz[1][2] * matriz[2][0]) + (matriz[0][2] * matriz[1][0] * matriz[2][1]);
        parteNegativa = (matriz[0][2] * matriz[1][1] * matriz[2][0]) + (matriz[0][0] * matriz[1][2] * matriz[2][1]) + (matriz[0][1] * matriz[1][0] * matriz[2][2]);
        det = partePositiva - parteNegativa;
        determinaSeEhBase(linhas, colunas, det, matriz);
    } else {
        printf("Ainda não conseguimos resolver matrizes maiores do que 3x3.\nNos desculpe... =(\n");
    }
}

int main() {
    double matriz[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    // escalonaPorGauss(3, 4, matriz);
    // printf("\n");

    // printaMatriz(3, 4, matriz);
    // printf("\n");

    // double* sistemaResolvido = resolveSistemaLinear(3, 4, matriz);
    // printaResolucaoSistema(3, sistemaResolvido);
    // free(sistemaResolvido);
    
    calculaDeterminante(3, 3, matriz);

    return 0;
}
