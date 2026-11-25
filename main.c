
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-10

typedef struct {
    int linhas;
    int colunas;
    double **dados;
} Matriz;

// Prototipos das funcoes
Matriz criarMatriz(int linhas, int colunas);
void liberarMatriz(Matriz *m);
void lerMatriz(Matriz *m, int numero);
void exibirMatriz(Matriz m);
Matriz copiarMatriz(Matriz m);

int somarMatrizes(Matriz a, Matriz b, Matriz *resultado);
int subtrairMatrizes(Matriz a, Matriz b, Matriz *resultado);
int multiplicarMatrizes(Matriz a, Matriz b, Matriz *resultado);
int inverterMatriz(Matriz original, Matriz *inversa);
int dividirMatrizes(Matriz a, Matriz b, Matriz *resultado);

int lerInteiro(const char *mensagem);
double lerDouble(const char *mensagem);

// Cria uma matriz com alocacao dinamica
Matriz criarMatriz(int linhas, int colunas) {
    Matriz m;

    m.linhas = linhas;
    m.colunas = colunas;

    m.dados = malloc(linhas * sizeof(double *));

    if (m.dados == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    for (int i = 0; i < linhas; i++) {
        m.dados[i] = calloc(colunas, sizeof(double));

        if (m.dados[i] == NULL) {
            printf("Erro ao alocar memoria!\n");
            exit(1);
        }
    }

    return m;
}

// Libera a memoria de uma matriz
void liberarMatriz(Matriz *m) {
    if (m->dados != NULL) {
        for (int i = 0; i < m->linhas; i++) {
            free(m->dados[i]);
        }

        free(m->dados);
        m->dados = NULL;
    }

    m->linhas = 0;
    m->colunas = 0;
}

// Leitura de inteiro com validacao
int lerInteiro(const char *mensagem) {
    int valor;

    printf("%s", mensagem);

    while (scanf("%d", &valor) != 1) {
        printf("Entrada invalida! Digite um numero inteiro: ");

        while (getchar() != '\n');
    }

    return valor;
}

// Leitura de numero real com validacao
double lerDouble(const char *mensagem) {
    double valor;

    printf("%s", mensagem);

    while (scanf("%lf", &valor) != 1) {
        printf("Entrada invalida! Digite um numero: ");

        while (getchar() != '\n');
    }

    return valor;
}

// Recebe os elementos de uma matriz
void lerMatriz(Matriz *m, int numero) {
    printf("\nCadastro da matriz %d\n", numero);

    for (int i = 0; i < m->linhas; i++) {
        for (int j = 0; j < m->colunas; j++) {
            char mensagem[100];

            snprintf(mensagem, sizeof(mensagem),
                     "Elemento [%d][%d]: ", i + 1, j + 1);

            m->dados[i][j] = lerDouble(mensagem);
        }
    }
}

// Exibe uma matriz organizada
void exibirMatriz(Matriz m) {
    for (int i = 0; i < m.linhas; i++) {
        printf("| ");

        for (int j = 0; j < m.colunas; j++) {
            printf("%10.3lf ", m.dados[i][j]);
        }

        printf("|\n");
    }
}

// Cria uma copia independente da matriz
Matriz copiarMatriz(Matriz m) {
    Matriz copia = criarMatriz(m.linhas, m.colunas);

    for (int i = 0; i < m.linhas; i++) {
        for (int j = 0; j < m.colunas; j++) {
            copia.dados[i][j] = m.dados[i][j];
        }
    }

    return copia;
}

// Adicao de matrizes
int somarMatrizes(Matriz a, Matriz b, Matriz *resultado) {
    if (a.linhas != b.linhas || a.colunas != b.colunas) {
        printf("\nErro: as matrizes possuem dimensoes diferentes!\n");
        return 0;
    }

    *resultado = criarMatriz(a.linhas, a.colunas);

    for (int i = 0; i < a.linhas; i++) {
        for (int j = 0; j < a.colunas; j++) {
            resultado->dados[i][j] =
                a.dados[i][j] + b.dados[i][j];
        }
    }

    return 1;
}

// Subtracao de matrizes
int subtrairMatrizes(Matriz a, Matriz b, Matriz *resultado) {
    if (a.linhas != b.linhas || a.colunas != b.colunas) {
        printf("\nErro: as matrizes possuem dimensoes diferentes!\n");
        return 0;
    }

    *resultado = criarMatriz(a.linhas, a.colunas);

    for (int i = 0; i < a.linhas; i++) {
        for (int j = 0; j < a.colunas; j++) {
            resultado->dados[i][j] =
                a.dados[i][j] - b.dados[i][j];
        }
    }

    return 1;
}

// Multiplicacao de matrizes
int multiplicarMatrizes(Matriz a, Matriz b, Matriz *resultado) {
    if (a.colunas != b.linhas) {
        printf("\nErro: dimensoes incompatíveis para multiplicacao!\n");
        return 0;
    }

    *resultado = criarMatriz(a.linhas, b.colunas);

    for (int i = 0; i < a.linhas; i++) {
        for (int j = 0; j < b.colunas; j++) {
            for (int k = 0; k < a.colunas; k++) {
                resultado->dados[i][j] +=
                    a.dados[i][k] * b.dados[k][j];
            }
        }
    }

    return 1;
}

// Calcula a inversa utilizando Gauss-Jordan
// com pivoteamento parcial
int inverterMatriz(Matriz original, Matriz *inversa) {
    if (original.linhas != original.colunas) {
        printf("\nErro: a matriz divisora nao e quadrada!\n");
        return 0;
    }

    int n = original.linhas;

    Matriz aumentada = criarMatriz(n, 2 * n);

    // Monta [A | I]
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            aumentada.dados[i][j] = original.dados[i][j];
        }

        aumentada.dados[i][i + n] = 1.0;
    }

    // Eliminacao de Gauss-Jordan
    for (int i = 0; i < n; i++) {

        int pivo = i;

        // Procura o maior pivo em modulo
        for (int k = i + 1; k < n; k++) {
            if (fabs(aumentada.dados[k][i]) >
                fabs(aumentada.dados[pivo][i])) {
                pivo = k;
            }
        }

        // Verifica se a matriz e singular
        if (fabs(aumentada.dados[pivo][i]) < EPSILON) {
            printf("\nErro: matriz singular! Nao possui inversa.\n");
            liberarMatriz(&aumentada);
            return 0;
        }

        // Troca as linhas, se necessario
        if (pivo != i) {
            for (int j = 0; j < 2 * n; j++) {
                double temp = aumentada.dados[i][j];

                aumentada.dados[i][j] =
                    aumentada.dados[pivo][j];

                aumentada.dados[pivo][j] = temp;
            }
        }

        // Normaliza a linha do pivo
        double divisor = aumentada.dados[i][i];

        for (int j = 0; j < 2 * n; j++) {
            aumentada.dados[i][j] /= divisor;
        }

        // Zera os demais elementos da coluna
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double fator = aumentada.dados[k][i];

                for (int j = 0; j < 2 * n; j++) {
                    aumentada.dados[k][j] -=
                        fator * aumentada.dados[i][j];
                }
            }
        }
    }

    // Extrai a inversa da matriz aumentada
    *inversa = criarMatriz(n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inversa->dados[i][j] =
                aumentada.dados[i][j + n];
        }
    }

    liberarMatriz(&aumentada);

    return 1;
}

// Divisao matricial: A / B = A * inversa(B)
int dividirMatrizes(Matriz a, Matriz b, Matriz *resultado) {
    if (b.linhas != b.colunas) {
        printf("\nErro: a matriz divisora deve ser quadrada!\n");
        return 0;
    }

    if (a.colunas != b.linhas) {
        printf("\nErro: dimensoes incompativeis para divisao!\n");
        return 0;
    }

    Matriz inversa;

    if (!inverterMatriz(b, &inversa)) {
        return 0;
    }

    int sucesso = multiplicarMatrizes(a, inversa, resultado);

    liberarMatriz(&inversa);

    return sucesso;
}

// Funcao principal
int main() {
    int quantidade;
    int opcao;
    int sucesso;

    printf("====================================\n");
    printf("    CALCULADORA DE MATRIZES - C\n");
    printf("====================================\n");

    // Solicita a quantidade de matrizes
    do {
        quantidade = lerInteiro(
            "\nInforme a quantidade de matrizes (minimo 2): "
        );

        if (quantidade < 2) {
            printf("Erro: informe pelo menos duas matrizes!\n");
        }

    } while (quantidade < 2);

    // Alocacao do vetor de matrizes
    Matriz *matrizes = malloc(quantidade * sizeof(Matriz));

    if (matrizes == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Cadastro das matrizes
    for (int i = 0; i < quantidade; i++) {
        int linhas, colunas;

        printf("\n====================================\n");
        printf("CADASTRO DA MATRIZ %d\n", i + 1);
        printf("====================================\n");

        do {
            linhas = lerInteiro("Quantidade de linhas: ");
            colunas = lerInteiro("Quantidade de colunas: ");

            if (linhas <= 0 || colunas <= 0) {
                printf("As dimensoes devem ser positivas!\n");
            }

        } while (linhas <= 0 || colunas <= 0);

        matrizes[i] = criarMatriz(linhas, colunas);

        lerMatriz(&matrizes[i], i + 1);
    }

    // Exibe as matrizes cadastradas
    printf("\n====================================\n");
    printf("MATRIZES CADASTRADAS\n");
    printf("====================================\n");

    for (int i = 0; i < quantidade; i++) {
        printf("\nMatriz %d (%d x %d):\n",
               i + 1,
               matrizes[i].linhas,
               matrizes[i].colunas);

        exibirMatriz(matrizes[i]);
    }

    // Menu de operacoes
    do {
        printf("\n====================================\n");
        printf("         MENU DE OPERACOES\n");
        printf("====================================\n");
        printf("1 - Adicao\n");
        printf("2 - Subtracao\n");
        printf("3 - Multiplicacao\n");
        printf("4 - Divisao matricial\n");
        printf("0 - Encerrar programa\n");
        printf("====================================\n");

        opcao = lerInteiro("Escolha uma opcao: ");

        if (opcao == 0) {
            break;
        }

        if (opcao < 0 || opcao > 4) {
            printf("\nOpcao invalida! Tente novamente.\n");
            continue;
        }

        // Copia a primeira matriz para iniciar a operacao
        Matriz acumuladora = copiarMatriz(matrizes[0]);

        sucesso = 1;

        // Executa as operacoes da esquerda para a direita
        for (int i = 1; i < quantidade; i++) {
            Matriz resultado;

            printf("\nOperacao: resultado anterior com matriz %d\n",
                   i + 1);

            switch (opcao) {
                case 1:
                    sucesso = somarMatrizes(
                        acumuladora, matrizes[i], &resultado
                    );
                    break;

                case 2:
                    sucesso = subtrairMatrizes(
                        acumuladora, matrizes[i], &resultado
                    );
                    break;

                case 3:
                    sucesso = multiplicarMatrizes(
                        acumuladora, matrizes[i], &resultado
                    );
                    break;

                case 4:
                    sucesso = dividirMatrizes(
                        acumuladora, matrizes[i], &resultado
                    );
                    break;
            }

            if (!sucesso) {
                break;
            }

            liberarMatriz(&acumuladora);
            acumuladora = resultado;
        }

        // Exibe o resultado final
        if (sucesso) {
            printf("\n====================================\n");
            printf("RESULTADO DA OPERACAO\n");
            printf("====================================\n");

            printf("Dimensoes: %d x %d\n",
                   acumuladora.linhas,
                   acumuladora.colunas);

            exibirMatriz(acumuladora);
        } else {
            printf("\nNao foi possivel concluir a operacao.\n");
        }

        liberarMatriz(&acumuladora);

    } while (opcao != 0);

    // Libera todas as matrizes cadastradas
    for (int i = 0; i < quantidade; i++) {
        liberarMatriz(&matrizes[i]);
    }

    free(matrizes);

    printf("\nPrograma encerrado com sucesso!\n");

    return 0;
}
