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
double* calcularAutovalorAutovetorMatriz2x2(FILE *arquivo, double matriz[2][2]);
void printaAutovaloresAutovetores(FILE *arquivo, double lambda1, double lambda2, double v1_x, double v1_y, double v2_x, double v2_y);
void multiplicaMatrizes2x2(double matrizResultante[2][2], double matriz1[2][2], double matriz2[2][2]);
int verificaDiagonalizacao(double matrizEntrada[2][2], double matrizMudanca[2][2], double matrizDiagonal[2][2]);

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
                printf("ATENÇÃO: Calculamos autovalores e autovetores apenas de matrizes 2x2.\n");

                if(1){
                    double matriz[2][2];
                    lerMatriz(2, 2, matriz);
                    system("cls");
                    
                    printf("Matriz de entrada:\n");
                    fprintf(arquivotxt, "Matriz de entrada:\n");
                    printaMatriz(arquivotxt, 2, 2, matriz);
                    printf("\n");
                    fprintf(arquivotxt, "\n");

                    double* valores = calcularAutovalorAutovetorMatriz2x2(arquivotxt, matriz);
                    if(valores == NULL){
                        free(valores);
                        break;
                    }
                    printaAutovaloresAutovetores(arquivotxt, valores[0], valores[1], valores[2], valores[3], valores[4], valores[5]);
                    free(valores);
                }
                fclose(arquivotxt);        
                break;
            case 5:
                arquivotxt = fopen(nomearquivotxt, "a");

                fprintf(arquivotxt, "\n===========================================================\n");
                fprintf(arquivotxt, "\n> Opção escolhida:\n\t5. Diagonalização de Matrizes\n\n");
                printf("ATENÇÃO: Diagonalizamos apenas matrizes 2x2.\n");

                if(1){
                    double matriz[2][2];
                    lerMatriz(2, 2, matriz);
                    system("cls");
                    
                    printf("Matriz de entrada:\n");
                    fprintf(arquivotxt, "Matriz de entrada:\n");
                    printaMatriz(arquivotxt, 2, 2, matriz);
                    printf("\n");
                    fprintf(arquivotxt, "\n");

                    double* valores = calcularAutovalorAutovetorMatriz2x2(arquivotxt, matriz);
                    if(valores == NULL){
                        free(valores);
                        break;
                    }

                    double matrizMudanca[2][2] = {
                        {valores[2], valores[4]},
                        {valores[3], valores[5]}
                    };

                    double matrizDiagonal[2][2] = {
                        {valores[0], 0},
                        {0, valores[1]}
                    };

                    int saoIguais = verificaDiagonalizacao(matriz, matrizMudanca, matrizDiagonal);
                    if(saoIguais == 1){
                        printf("Matriz é diagonalizavel!\n\n");
                        fprintf(arquivotxt, "Matriz é diagonalizavel!\n\n");
                        printf("Matriz diagonalizada:\n");
                        fprintf(arquivotxt, "Matriz diagonalizada:\n");
                        printaMatriz(arquivotxt, 2, 2, matrizDiagonal);
                        printf("\n");
                        fprintf(arquivotxt, "\n");
                        printf("Matriz de mudança de base:\n");
                        fprintf(arquivotxt, "Matriz de mudança de base:\n");
                        printf("\n");
                        fprintf(arquivotxt, "\n");
                        printaMatriz(arquivotxt, 2, 2, matrizMudanca);
                    } else {
                        printf("A matriz de entrada não é diagonalizavel!\n");
                        fprintf(arquivotxt, "A matriz de entrada não é diagonalizavel!\n");
                    }
                    printf("\n");
                    fprintf(arquivotxt, "\n");
                    free(valores);
                }
                fclose(arquivotxt);   
                break;
            case 6:
                printf("Deseja visualizar o histórico ou apagá-lo?\n1. Visualizar\n2. Apagar\n> Escolha uma das opções: ");
                int opcoes;
                scanf("%d", &opcoes);
                system("cls");
                if(opcoes == 1){
                    arquivotxt = fopen(nomearquivotxt, "r");
                    if(arquivotxt == NULL){
                        printf("Houve um erro ao abrir o arquivo.\n");
                    } else {
                        char line[500];
                        while (fgets(line, sizeof(line), arquivotxt) != NULL) {
                            printf("%s", line);
                        }
                    }
                    fclose(arquivotxt);
                } else if (opcoes == 2){
                    arquivotxt = fopen(nomearquivotxt, "w");
                    if(arquivotxt == NULL){
                        printf("Houve um erro ao abrir o arquivo.\n");
                    }
                    fclose(arquivotxt);
                } else {
                    system("cls");
                    printf("Opção Inválida.\n");
                }
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
    /*
        Funcao:
            Calcular determinante da matriz de entrada

        Entrada: 
            int linhas: quantidade de linhas da matriz a ser calculado determinante.
            int colunas: quantidade de colunas da matriz a ser calculado determinante.
            double matriz[linhas][colunas]: matriz com os respectivos tamanhos de entrada.

        Saida:
            double det: determinante da matriz em formato double.
    */
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
    /*
        Funçao: 
            Escreve uma matriz de números reais no arquivo e no terminal.

        Entrada: 
            FILE *arquivo: nome do arquivo (aberto) em que será escrito a matriz.
            int linhas: quantidade de linhas da matriz a ser escrita.
            int colunas: quantidade de colunas da matriz a ser escrita.
            double matriz[linhas][colunas]: matriz com os respectivos tamanhos.

        Saida:
            Void: Não retorna valor algum.
    */
    fprintf(arquivo, "\n");
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            printf("%.2f ", matriz[i][j]);
            fprintf(arquivo, "%.2f ", matriz[i][j]);
        }
        printf("\n");
        fprintf(arquivo, "\n");
    }
}

void printaConjuntoDeVetores(FILE *arquivo, int linhas, int colunas, double matriz[linhas][colunas]){
    /*
        Funçao: 
            Escreve conjunto de vetores armazenado em uma matriz de tamanho linhas x colunas no arquivo e no terminal.

        Entrada: 
            FILE *arquivo: nome do arquivo (aberto) em que será escrito a matriz.
            int linhas: quantidade de linhas da matriz a ser escrita.
            int colunas: quantidade de colunas da matriz a ser escrita.
            double matriz[linhas][colunas]: matriz com os respectivos tamanhos.

        Saida:
            Void: Não retorna valor algum.
    */
    for(int i = 0; i < linhas; i++){
        printf("v%d = (", i+1);
        fprintf(arquivo, "v%d = (", i+1);
        for(int j = 0; j < colunas; j++){
            if(j == colunas-1){
                printf("%.2f)", matriz[i][j]);
                fprintf(arquivo, "%.2f)", matriz[i][j]);
            } else {
                printf("%f, ", matriz[i][j]);
                fprintf(arquivo, "%.2f, ", matriz[i][j]);
            }
        }
        printf("\n");
        fprintf(arquivo, "\n");
    }
}

void printaResolucaoSistema(FILE *arquivo, int dimensao, double* sistemaResolvido){
    /*
        Funçao: 
            Escreve resolução do sistema em forma "x = _valor_ \t y = _valor_" para a quantidade de variaveis que forem recebidas.
            Tamanho máximo de variáveis aceitas = 3.

        Entrada: 
            FILE *arquivo: nome do arquivo (aberto) em que será a resolução do sistema.
            int dimensao: dimensão da matriz original do problema.
            double* sistemaResolvido: váriveis que solucionam o sistema original do problema.
    
        Saida:
            Void: Não retorna valor algum.
    */
    char letrasDimensoes[3] = {'x', 'y', 'z'};
    fprintf(arquivo, "\n");
    for(int i = 0; i < dimensao; i++){
        printf("%c = %.2f\t", letrasDimensoes[i], sistemaResolvido[i]);
        fprintf(arquivo, "%c = %.2f\t", letrasDimensoes[i], sistemaResolvido[i]);
    }
    fprintf(arquivo, "\n");
    printf("\n");
}

void lerMatriz(int linhas, int colunas, double matriz[linhas][colunas]){
    /*
        Funçao: 
            Ler e armazenar na variável matriz, valores para uma matriz de tamanho linhas x colunas.

        Entrada: 
            int linhas: quantidade de linhas da matriz a ser lida.
            int colunas: quantidade de colunas da matriz a ser lida.
            double matriz[linhas][colunas]: matriz com os respectivos tamanhos.
    
        Saida:
            Void: Não retorna valor algum.
            Escrevemos valores lidos na variável matriz.
    */
    printf("> Insira os elementos da matriz: (informe apenas os coeficientes e a constante)\n");
    printf("Ex.: 2x+3y-z=5 -> 2 3 -1 5\n");
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            scanf("%lf", &matriz[i][j]);
        }
    }
}

void lerConjuntoDeVetores(int linhas, int colunas, double matriz[linhas][colunas]){
    /*
        Funçao: 
            Ler e armazenar na variável matriz, valores para uma matriz de tamanho linhas x colunas.
            Diferença entre função lerMatriz: prints indicando ao usuário forma de entrada.

        Entrada: 
            int linhas: quantidade de linhas da matriz a ser lida.
            int colunas: quantidade de colunas da matriz a ser lida.
            double matriz[linhas][colunas]: matriz com os respectivos tamanhos.
    
        Saida:
            Void: Não retorna valor algum.
    */
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
    /*
        Funçao: 
            Escalona por método de Gauss-Jordan, uma matiz do tamanho linhas x colunas.

        Entrada: 
            int linhas: quantidade de linhas da matriz a ser escalonada.
            int colunas: quantidade de colunas da matriz a ser escalonada.
            double matriz[linhas][colunas]: matriz com os respectivos tamanhos.
    
        Saida:
            Void: Não retorna valor algum.
            Sobrescrevemos a variável matriz com o resultado do escalonamento.
    */
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
    /*
        Funçao: 
            Resolve sistema linear após a matriz de entrada ter sido escalonada, retornando valores em um array double. 

        Entrada: 
            int linhas: quantidade de linhas da matriz que resolveremos.
            int colunas: quantidade de colunas da matriz que resolveremos.
            double matriz[linhas][colunas]: matriz com os respectivos tamanhos.
    
        Saida:
            double* variaveis: array alocado dinamicamente do tamanho da variável de entrada `linhas`,
                               contendo os valores que resolvem o sistema linear.
    */
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
    /*
        Funçao: 
            Resolve sistema que apresente dependencia linear, printando tanto no arquivo de entrada
            quanto no próprio terminal, o valor de x no sistema.

        Entrada: 
            FILE *arquivo: nome do arquivo (aberto) em que será escrito a soluçao.
            int linhas: quantidade de linhas da matriz a ser resolvida.
            int colunas: quantidade de colunas da matriz a ser resolvida.
            double matriz[linhas][colunas]: matriz com os respectivos tamanhos.
    
        Saida:
            Void: Não retorna valor algum.
    */
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

double* calcularAutovalorAutovetorMatriz2x2(FILE *arquivo, double matriz[2][2]){
    /*
        Funçao: 
            Calcula autovalor e autovetor para uma matriz de tamanho 2x2.
            Valores retornados em um array double de tamanho 6.
        Entrada: 
            FILE *arquivo: nome do arquivo (aberto) em que escreveremos caso os autovalores forem complexos.
            double matriz[2][2]: matriz de tamanho 2x2 a ser calculado autovalor e autovetor.
    
        Saida:
            double* valores, sendo:
            valores[0] -> lambda1;
            valores[1] -> lambda2;
            valores[2] -> x em v1;
            valores[3] -> y em v1;
            valores[4] -> x em v2;
            valores[5] -> y em v2;            
    */
    double a = matriz[0][0];
    double b = matriz[0][1];
    double c = matriz[1][0];
    double d = matriz[1][1];

    double traco = a + d;
    double det = a * d - b * c;

    double discriminante = traco * traco - 4 * det;

    if (discriminante < 0) {
        printf("Infelizmente não suportamos autovalores complexos...\n");
        fprintf(arquivo, "Infelizmente não suportamos autovalores complexos...\n");
        return NULL;
    }

    discriminante = sqrt(discriminante);

    double lambda1 = (traco + discriminante) / 2;
    double lambda2 = (traco - discriminante) / 2;

    double v1_x, v1_y, v2_x, v2_y;

    if (b != 0) {
        v1_x = 1;
        v1_y = (lambda1 - a) / b;
    } else if (c != 0) {
        v1_y = 1;
        v1_x = (lambda1 - d) / c;
    } else {
        v1_x = 1;
        v1_y = 0;
    }

    if (b != 0) {
        v2_x = 1;
        v2_y = (lambda2 - a) / b;
    } else if (c != 0) {
        v2_y = 1;
        v2_x = (lambda2 - d) / c;
    } else {
        v2_x = 0;
        v2_y = 1;
    }

    double* valores = (double*)calloc(6, sizeof(double));
    valores[0] = lambda1;
    valores[1] = lambda2;
    valores[2] = v1_x;
    valores[3] = v1_y;
    valores[4] = v2_x;
    valores[5] = v2_y;

    return valores;
}


void printaAutovaloresAutovetores(FILE *arquivo, double lambda1, double lambda2, double v1_x, double v1_y, double v2_x, double v2_y){
    /*
        Funçao: 
            Escrever na tela e no arquivo os valores de ambos lambdas, x e y para v1 e v2.

        Entrada: 
            FILE *arquivo: nome do arquivo (aberto) em que escreveremos caso os autovalores e autovetores.

            double lambda1: lambda1 do autovalor recentemente calculado
            double lambda2: lambda2 do autovalor recentemente calculado
            double v1_x: x em v1 ] 
            double v1_y: y em v1 ]
            double v2_x: x em v2 ]
            double v2_y: y em v2 ] - > dos autovetores recentemente calculados
    
        Saida:
            Void: Não retorna valor algum.  
    */
    //print lambdas
    printf("Autovalores:\nλ1 = %lf\nλ2 = %lf\n\n", lambda1, lambda2);
    fprintf(arquivo, "Autovalores:\nλ1 = %lf\nλ2 = %lf\n\n", lambda1, lambda2);
    //printando autovetor para lambda1
    printf("Autovetor correspondente a λ1 = %.2f: ", lambda1);
    printf("(%.2f, %.2f)\n", v1_x, v1_y);
    fprintf(arquivo, "Autovetor correspondente a λ1 = %.2f: ", lambda1);
    fprintf(arquivo, "(%.2f, %.2f)\n", v1_x, v1_y);
    //printando autovetor para lambda2
    printf("Autovetor correspondente a λ2 = %.2f: ", lambda2);
    printf("(%.2f, %.2f)\n", v2_x, v2_y);
    fprintf(arquivo, "Autovetor correspondente a λ2 = %.2f: ", lambda2);
    fprintf(arquivo, "(%.2f, %.2f)\n", v2_x, v2_y);
}

void multiplicaMatrizes2x2(double matrizResultante[2][2], double matriz1[2][2], double matriz2[2][2]){
    /*
        Funçao: 
            Multiplicar duas matriz de tamanho 2x2.

        Entrada: 
            double matrizResultante[2][2]: matriz que guardará valores pós multiplicação
            double matriz1[2][2]: matriz a ser multiplicada por matriz2.
            double matriz2[2][2]: matriz que multiplicará a matriz1.
    
        Saida:
            Void: Não retorna valor algum.  
            Escreve o resultado da multiplicação em matrizResultante.
    */
    double c10 = (matriz1[0][0] * matriz2[0][0]) + (matriz1[0][1] * matriz2[1][0]);
    double c11 = (matriz1[0][0] * matriz2[0][1]) + (matriz1[0][1] * matriz2[1][1]);
    double c20 = (matriz1[1][0] * matriz2[0][0]) + (matriz1[1][1] * matriz2[1][0]);
    double c21 = (matriz1[1][0] * matriz2[0][1]) + (matriz1[1][1] * matriz2[1][1]);
    
    matrizResultante[0][0] = c10;
    matrizResultante[0][1] = c11;
    matrizResultante[1][0] = c20;
    matrizResultante[1][1] = c21;
}

int verificaDiagonalizacao(double matrizEntrada[2][2], double matrizMudanca[2][2], double matrizDiagonal[2][2]){
    /*
        Funçao: 
            Verifica se é possivel fazer a diagonalização de uma matriz 2x2, calculando PDP^-1 e comparando
            resultado à matriz de entrada.

        Entrada: 
            double matrizEntrada[2][2]: matriz original, que verificaremos se é possivel diagonalizar ou nao.
            double matriz1[2][2]: matriz de mudança da matriz original.
            double matriz2[2][2]: matriz diagonal da matriz original.
    
        Saida:
            Void: Não retorna valor algum.  
            Escreve o resultado da multiplicação em matrizResultante.
    */
    double det = calculaDeterminante(2, 2, matrizMudanca);
    double matrizMudancaInversa[2][2] = {
        {matrizMudanca[1][1], -matrizMudanca[0][1]},
        {-matrizMudanca[1][0], matrizMudanca[0][0]}
    };

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            matrizMudancaInversa[i][j]*=(1/det);    
        }
    }

    double matrizArmazenamento[2][2];
    multiplicaMatrizes2x2(matrizArmazenamento, matrizMudanca, matrizDiagonal);
    multiplicaMatrizes2x2(matrizArmazenamento, matrizArmazenamento, matrizMudancaInversa);
    
    int matrizesSaoIguais = 1;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            if(matrizArmazenamento[i][j] != matrizEntrada[i][j]){
                matrizesSaoIguais = 0;
                break;
            }
        }
        if(matrizesSaoIguais == 0){
            break;
        }
    }

    if(matrizEntrada[0][1] == 0.0 && matrizEntrada[1][0] == 0){
        if((matrizEntrada[0][0] == matrizArmazenamento[0][0] || matrizEntrada[0][0] == matrizArmazenamento[1][1]) && (matrizEntrada[1][1] == matrizArmazenamento[1][1] || matrizEntrada[1][1] == matrizArmazenamento[0][0])){
            matrizesSaoIguais = 1;
        } else {
            matrizesSaoIguais = 0;
        }
    }

    return matrizesSaoIguais;
}