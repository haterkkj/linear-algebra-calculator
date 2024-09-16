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

// void determinaBase(int linhas, int colunas, double matriz[linhas][colunas]){
//     int novasColunas = colunas;
//     if(colunas >= 3){
//         novasColunas = 5;
//     }

//     double novaMatriz[linhas][novasColunas];
//     for(int i = 0; i < linhas; i++){
//         int idx = 0;
//         for(int j = 0; j < novasColunas; j++){
//             novaMatriz[i][j] = matriz[i][idx];
//             idx++;
//             if(idx==colunas-1){
//                 idx = 0;
//             }
//         }
//     }

//     double partePositiva[linhas];
//     int idx = 0;
//     for(int i = 0; i < linhas; i++){
//         partePositiva[i] = 1;
//         for(int j = i; j < colunas; j++){
//             if(idx >= novasColunas-1){
//                 idx-=colunas;
//                 if(novasColunas==colunas){
//                     break;
//                 }
//             }
//             partePositiva[i]*=novaMatriz[i][idx];
//             idx++;
//         }
//         idx++;
//     }

//     double parteNegativa[linhas];
//     idx = novasColunas-1;
//     int posPn = 0;
//     for(int i = linhas-1; i >= 0; i--){
//         parteNegativa[posPn] = 1;
//         for(int j = i; j >= 0; j--){
//             if(idx < 0){
//                 idx+=colunas;
//                 if(novasColunas==colunas){
//                     parteNegativa[posPn]*=novaMatriz[i][idx];
//                     break;
//                 }
//             }
//             parteNegativa[posPn]*=novaMatriz[i][idx];
//             idx--;
//         }
//         //printf("%d\n\n", idx);
//         posPn++;
//         idx--;
//     }
//     double pos=0, neg=0;
//     for(int i = 0; i < linhas; i++){
//         pos+=partePositiva[i];
//         neg+=parteNegativa[i];
        
//     }

//     printf("%f\n%f\n%f\n", pos-neg, pos, neg);
//     if(pos-neg != 0){
//         printf("É BASE\n");
//     } else {
//         printf("NÃO É BASE\n");
//     }
// }

int main() {
    double matriz[3][3] = {
        {4, 5, -3},
        {2, 1, 0},
        {3, -1, 1}
    };

    // escalonaPorGauss(3, 4, matriz);
    // printf("\n");

    // printaMatriz(3, 4, matriz);
    // printf("\n");

    // double* sistemaResolvido = resolveSistemaLinear(3, 4, matriz);
    // printaResolucaoSistema(3, sistemaResolvido);
    // free(sistemaResolvido);
    
    determinaBase(3, 3, matriz);

    return 0;
}
