#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int printaMenu(){
    printf("- - - - - - - - - - - - - - - - - - - - -\n");
    printf(">\tCALCULADORA ALGEBRA LINEAR\t<\n");
    printf("- - - - - - - - - - - - - - - - - - - - -\n");
    printf("1. Resolução de Sistemas Lineares\n");
    printf("2. Verificação de Injetividade, Sobrejetividade e Bijetividade\n");
    printf("3. Determinação de Bases\n");
    printf("4. Cálculo de Autovalores e Autovetores\n");
    printf("5. Diagonalização de Matrizes\n");
    printf("6. Histórico\n");
    printf("7. Sair\n");
    printf("- - - - - - - - - - - - - - - - - - - - -\n");
    printf("> O que deseja fazer? ");
    
    int entrada;
    scanf("%d", &entrada);
    return entrada;
}

double calculaDeterminante(int linhas, int colunas, double matriz[linhas][colunas]);
void printaMatriz(FILE *arquivo, int linhas, int colunas, double matriz[linhas][colunas]);
void printaConjuntoDeVetores(FILE *arquivo, int linhas, int colunas, double matriz[linhas][colunas]);
void printaResolucaoSistema(FILE *arquivo, int dimensao, double* sistemaResolvido);
void lerMatriz(int linhas, int colunas, double matriz[linhas][colunas]);
void lerConjuntoDeVetores(int linhas, int colunas, double matriz[linhas][colunas]);
void escalonaPorGauss(int linhas, int colunas, double matriz[linhas][colunas]);
double* resolveSistemaLinear(int linhas, int colunas, double matriz[linhas][colunas]);
void resolveSistemaDependenciaLinear(FILE *arquivo, int linhas, int colunas, double matriz[linhas][colunas]);
void calcularAutovalorAutovetorMatriz2x2(FILE *arquivo, double matriz[2][2]);

int main() {    
    const char *nomearquivotxt = "../historico.txt";
    FILE *arquivotxt = fopen(nomearquivotxt, "a");
    if (arquivotxt == NULL){
        printf("Houve um erro ao abrir o arquivo de histórico, tente reabrir o programa.\n");
        printf("Encerrando...");
        return 0;
    }   
 
    while(1){
        int entrada;
        entrada = printaMenu();
        switch (entrada){
            case 1:
                printf("Deseja operar com matriz 2x2 ou 3x3?\n1. 2x2\n2. 3x3\n> Escolha uma das opções: ");
                int tamanhoMatriz;
                arquivotxt = fopen(nomearquivotxt, "a");
                scanf("%d", &tamanhoMatriz);

                fprintf(arquivotxt, "\n===========================================================\n");
                fprintf(arquivotxt, "\n> Opção escolhida:\n\t1. Resolução de Sistemas Lineares\n");

                if(tamanhoMatriz == 1){
                    double matriz[2][3];
                    system("cls");
                    lerMatriz(2, 3, matriz);
                    system("cls");
                    
                    printf("Matriz original:\n");
                    fprintf(arquivotxt, "\nMatriz original: \n");
                    printaMatriz(arquivotxt, 2, 3, matriz);
                    

                    printf("\nMatriz escalonada:\n");
                    fprintf(arquivotxt, "\nMatriz escalonada: \n");
                    escalonaPorGauss(2, 3, matriz);
                    printaMatriz(arquivotxt, 2, 3, matriz);

                    printf("\nResolução do sistema:\n");
                    fprintf(arquivotxt, "\nResolução do sistema:\n");
                    double det = calculaDeterminante(2, 3, matriz);
                    if(det == 0){
                        resolveSistemaDependenciaLinear(arquivotxt, 2, 3, matriz);
                    } else {
                        double *variaveis = resolveSistemaLinear(2, 3, matriz);
                        printaResolucaoSistema(arquivotxt, 2, variaveis);
                        free(variaveis);
                    }
                } else if (tamanhoMatriz == 2){
                    double matriz[3][4];
                    system("cls");
                    lerMatriz(3, 4, matriz);
                    system("cls");
                    
                    printf("Matriz original:\n");
                    fprintf(arquivotxt, "\nMatriz original: \n");
                    printaMatriz(arquivotxt, 3, 4, matriz);

                    printf("\nMatriz escalonada:\n");
                    fprintf(arquivotxt, "\nMatriz escalonada:\n");
                    escalonaPorGauss(3, 4, matriz);
                    printaMatriz(arquivotxt, 3, 4, matriz);

                    printf("\nResolução do sistema:\n");
                    fprintf(arquivotxt, "\nResolução do sistema:\n");
                    double det = calculaDeterminante(3, 4, matriz);
                    if(det == 0){
                        resolveSistemaDependenciaLinear(arquivotxt, 3, 4, matriz);
                    } else {
                        double *variaveis = resolveSistemaLinear(3, 4, matriz);
                        printaResolucaoSistema(arquivotxt, 3, variaveis);
                        free(variaveis);
                    }
                } else {
                    system("cls");
                    printf("Opção Inválida.\n");
                }
                fclose(arquivotxt);
                break;
            case 2:
                arquivotxt = fopen(nomearquivotxt, "a");
                fprintf(arquivotxt, "\n===========================================================\n");
                fprintf(arquivotxt, "\n> Opção escolhida:\n\t2. Verificação de Injetividade, Sobrejetividade e Bijetividade\n");
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
                    fprintf(arquivotxt, "\nA matriz:\n");
                    printaMatriz(arquivotxt, 2, 2, matriz);
                    printf("\n");
                    fprintf(arquivotxt, "\n");
                    if(det != 0){
                        printf("É injetora;\n");
                        printf("É sobrejetora;\n");
                        printf("É bijetora.\n");

                        fprintf(arquivotxt, "É injetora;\n");
                        fprintf(arquivotxt, "É sobrejetora;\n");
                        fprintf(arquivotxt, "É bijetora.\n");
                    } else {
                        printf("Não é injetora;\n");
                        printf("Não é sobrejetora;\n");
                        printf("Não é bijetora.\n");

                        fprintf(arquivotxt, "Não é injetora;\n");
                        fprintf(arquivotxt, "Não é sobrejetora;\n");
                        fprintf(arquivotxt, "Não é bijetora.\n");
                    }
                } else if (dimensaoMatrizQuadrada == 2){
                    double matriz[3][3];
                    system("cls");
                    lerMatriz(3, 3, matriz);
                    system("cls");

                    double det = calculaDeterminante(3, 3, matriz);

                    printf("A matriz: \n");
                    fprintf(arquivotxt, "\nA matriz:\n");
                    printaMatriz(arquivotxt, 3, 3, matriz);
                    printf("\n");
                    fprintf(arquivotxt, "\n");
                    if(det != 0){
                        printf("É injetora;\n");
                        printf("É sobrejetora;\n");
                        printf("É bijetora.\n");

                        fprintf(arquivotxt, "É injetora;\n");
                        fprintf(arquivotxt, "É sobrejetora;\n");
                        fprintf(arquivotxt, "É bijetora.\n");
                    } else {
                        printf("Não é injetora;\n");
                        printf("Não é sobrejetora;\n");
                        printf("Não é bijetora.\n");

                        fprintf(arquivotxt, "Não é injetora;\n");
                        fprintf(arquivotxt, "Não é sobrejetora;\n");
                        fprintf(arquivotxt, "Não é bijetora.\n");
                    }
                } else {
                    system("cls");
                    printf("Opção Inválida.\n");
                }
                fclose(arquivotxt);
                break;
            case 3:
                arquivotxt = fopen(nomearquivotxt, "a");
                fprintf(arquivotxt, "\n===========================================================\n");
                fprintf(arquivotxt, "\n> Opção escolhida:\n\t3. Determinação de Bases\n");

                printf("Irá determinar uma base em R2 ou R3?\n1. R2\n2. R3\n> Escolha uma das opções: ");
                int dimensao;
                scanf("%d", &dimensao);
                if(dimensao == 1){
                    double matriz[2][2];
                    system("cls");
                    lerConjuntoDeVetores(2, 2, matriz);
                    system("cls");

                    double det = calculaDeterminante(2, 2, matriz);
                    printaConjuntoDeVetores(arquivotxt, 2, 2, matriz);
                    if(det != 0){
                        printf("Formam base de R2.\n");
                        fprintf(arquivotxt, "Formam base de R2.\n");
                    } else {
                        printf("Não formam base de R2\n");
                        fprintf(arquivotxt, "Não formam base de R2\n");
                    }
                } else if (dimensao == 2){
                    double matriz[3][3];
                    system("cls");
                    lerConjuntoDeVetores(3, 3, matriz);
                    system("cls");
                    double det = calculaDeterminante(3, 3, matriz);
                    printaConjuntoDeVetores(arquivotxt, 3, 3, matriz);
                    if(det != 0){
                        printf("Formam base de R3.\n");
                        fprintf(arquivotxt, "Formam base de R3.\n");
                    } else {
                        printf("Não formam base de R3\n");
                        fprintf(arquivotxt, "Não formam base de R3\n");
                    }
                } else {
                    system("cls");
                    printf("Opção Inválida.\n");
                }
                fclose(arquivotxt);
                break;
            case 4:
                arquivotxt = fopen(nomearquivotxt, "a");

                fprintf(arquivotxt, "\n===========================================================\n");
                fprintf(arquivotxt, "\n> Opção escolhida:\n\t4. Cálculo de Autovalores e Autovetores\n\n");

                double matriz[2][2];
                lerMatriz(2, 2, matriz);
                
                printf("Matriz de entrada:\n");
                fprintf(arquivotxt, "Matriz de entrada:\n");
                printaMatriz(arquivotxt, 2, 2, matriz);
                printf("\n");
                fprintf(arquivotxt, "\n");

                calcularAutovalorAutovetorMatriz2x2(arquivotxt, matriz);

                fclose(arquivotxt);        
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
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

void printaMatriz(FILE *arquivo, int linhas, int colunas, double matriz[linhas][colunas]){
    fprintf(arquivo, "\n");
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            printf("%f ", matriz[i][j]);
            fprintf(arquivo, "%f ", matriz[i][j]);
        }
        printf("\n");
        fprintf(arquivo, "\n");
    }
}

void printaConjuntoDeVetores(FILE *arquivo, int linhas, int colunas, double matriz[linhas][colunas]){
    for(int i = 0; i < linhas; i++){
        printf("v%d = (", i+1);
        fprintf(arquivo, "v%d = (", i+1);
        for(int j = 0; j < colunas; j++){
            if(j == colunas-1){
                printf("%f)", matriz[i][j]);
                fprintf(arquivo, "%f)", matriz[i][j]);
            } else {
                printf("%f, ", matriz[i][j]);
                fprintf(arquivo, "%f, ", matriz[i][j]);
            }
        }
        printf("\n");
        fprintf(arquivo, "\n");
    }
}

void printaResolucaoSistema(FILE *arquivo, int dimensao, double* sistemaResolvido){
    char letrasDimensoes[3] = {'x', 'y', 'z'};
    fprintf(arquivo, "\n");
    for(int i = 0; i < dimensao; i++){
        printf("%c = %f\t", letrasDimensoes[i], sistemaResolvido[i]);
        fprintf(arquivo, "%c = %f\t", letrasDimensoes[i], sistemaResolvido[i]);
    }
    fprintf(arquivo, "\n");
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
        printf("> Insira os elementos do vetor n°%d: (informe apenas números)\n", i+1);
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
    double det = calculaDeterminante(linhas, colunas, matriz);
    if(det == 0){
        // resolveremos no print
    } else {
        for(int i = linhas-1; i >= 0; i--){
            variaveis[i] = matriz[i][colunas-1];
            if(i < linhas - 1){
                for(int j = linhas; j > i; j--){
                    variaveis[i] -= matriz[i][j] * variaveis[j];
                }
            }
            variaveis[i]/=matriz[i][i];
        }   
    }
    return variaveis;
}

void resolveSistemaDependenciaLinear(FILE *arquivo, int linhas, int colunas, double matriz[linhas][colunas]){
    char letras[2] = {'y', 'z'};
    int idx = 0;
    printf("x = (%.2f", matriz[0][colunas-1]);
    fprintf(arquivo, "x = (%.2f", matriz[0][colunas-1]);
    for(int i = 1; i < colunas-1; i++){
        if(matriz[0][i] > 0.0){
            printf(" - %.2f%c", matriz[0][i], letras[idx]);
            fprintf(arquivo, " - %.2f%c", matriz[0][i], letras[idx]);
        } else {
            printf(" + %.2f%c", matriz[0][i], letras[idx]);
            fprintf(arquivo, " + %.2f%c", matriz[0][i], letras[idx]);
        }
        idx++;
    }
    if(matriz[0][0] > 1){
        printf(") / %.2f", matriz[0][0]);
        fprintf(arquivo, ") / %.2f", matriz[0][0]);
    } else {
        printf(")");
        fprintf(arquivo, ")");
    }
    printf("\n");
    fprintf(arquivo, "\n");
}

void calcularAutovalorAutovetorMatriz2x2(FILE *arquivo, double matriz[2][2]){
    double a = matriz[0][0];
    double b = matriz[0][1];
    double c = matriz[1][0];
    double d = matriz[1][1];

    double traco = a + d;
    double det = a * d - b * c;

    double discriminante = traco * traco - 4 * det;
    if(discriminante < 0){
        printf("Infelizmente não suportamos autovalores complexos...\n");
        fprintf(arquivo, "Infelizmente não suportamos autovalores complexos...\n");
        return;
    }
    discriminante = sqrt(discriminante);

    double lambda1 = (traco + discriminante) / 2;
    double lambda2 = (traco - discriminante) / 2;

    printf("Autovalores:\nλ1 = %lf\nλ2 = %lf\n\n", lambda1, lambda2);
    fprintf(arquivo, "Autovalores:\nλ1 = %lf\nλ2 = %lf\n\n", lambda1, lambda2);

    if (b != 0) {
        printf("Autovetor correspondente a λ1 = %.2f: ", lambda1);
        fprintf(arquivo, "Autovetor correspondente a λ1 = %.2f: ", lambda1);
        float v1_x = 1; // Podemos escolher x = 1
        float v1_y = (lambda1 - a) / b; // Resolvendo para y
        printf("(%.2f, %.2f)\n", v1_x, v1_y);
        fprintf(arquivo, "(%.2f, %.2f)\n", v1_x, v1_y);
    } else if (a != lambda1) {
        printf("Autovetor correspondente a λ1 = %.2f: ", lambda1);
        fprintf(arquivo, "Autovetor correspondente a λ1 = %.2f: ", lambda1);
        float v1_x = 0; 
        float v1_y = 1; 
        printf("(%.2f, %.2f)\n", v1_x, v1_y);
        fprintf(arquivo, "(%.2f, %.2f)\n", v1_x, v1_y);
    }

    if (b != 0) {
        printf("Autovetor correspondente a λ2 = %.2f: ", lambda2);
        fprintf(arquivo, "Autovetor correspondente a λ2 = %.2f: ", lambda2);
        float v2_x = 1; // Podemos escolher x = 1
        float v2_y = (lambda2 - a) / b; // Resolvendo para y
        printf("(%.2f, %.2f)\n", v2_x, v2_y);
        fprintf(arquivo, "(%.2f, %.2f)\n", v2_x, v2_y);
    } else if (a != lambda2) {
        printf("Autovetor correspondente a λ2 = %.2f: ", lambda2);
        fprintf(arquivo, "Autovetor correspondente a λ2 = %.2f: ", lambda2);
        float v2_x = 0; 
        float v2_y = 1; 
        printf("(%.2f, %.2f)\n", v2_x, v2_y);
        fprintf(arquivo, "(%.2f, %.2f)\n", v2_x, v2_y);
    }
}