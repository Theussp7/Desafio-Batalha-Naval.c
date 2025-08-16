#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5
#define TAMANHO_HABILIDADE 5  // Matriz 5x5

// Função para inicializar o tabuleiro com água
void inicializa_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Verifica se há sobreposição ao posicionar navio
int verifica_sobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int delta_linha, int delta_coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int nova_linha = linha + i * delta_linha;
        int nova_coluna = coluna + i * delta_coluna;
        if (tabuleiro[nova_linha][nova_coluna] != AGUA) {
            return 1;
        }
    }
    return 0;
}

// Posiciona um navio no tabuleiro
void posiciona_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int delta_linha, int delta_coluna, const char* tipo) {
    int linha_final = linha + (TAMANHO_NAVIO - 1) * delta_linha;
    int coluna_final = coluna + (TAMANHO_NAVIO - 1) * delta_coluna;

    if (linha_final < 0 || linha_final >= TAMANHO_TABULEIRO || coluna_final < 0 || coluna_final >= TAMANHO_TABULEIRO) {
        printf("Erro: Navio %s fora do tabuleiro (%d, %d)\n", tipo, linha, coluna);
        return;
    }

    if (verifica_sobreposicao(tabuleiro, linha, coluna, delta_linha, delta_coluna)) {
        printf("Erro: Sobreposição de navio %s em (%d, %d)\n", tipo, linha, coluna);
        return;
    }

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int nova_linha = linha + i * delta_linha;
        int nova_coluna = coluna + i * delta_coluna;
        tabuleiro[nova_linha][nova_coluna] = NAVIO;
    }
}

// Cria matriz de habilidade em cone (forma pirâmide invertida)
void cria_habilidade_cone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Condição para formar cone: |j - centro| <= i
            if (abs(j - TAMANHO_HABILIDADE / 2) <= i) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Cria matriz de habilidade cruz
void cria_habilidade_cruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == TAMANHO_HABILIDADE / 2 || j == TAMANHO_HABILIDADE / 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Cria matriz de habilidade octaedro (losango)
void cria_habilidade_octaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Forma de losango: |i - centro| + |j - centro| <= centro
            if (abs(i - TAMANHO_HABILIDADE / 2) + abs(j - TAMANHO_HABILIDADE / 2) <= TAMANHO_HABILIDADE / 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Aplica a matriz de habilidade ao tabuleiro com base na origem
void aplica_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                       int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                       int origem_linha, int origem_coluna) {
    int offset = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int linha_tabuleiro = origem_linha - offset + i;
            int coluna_tabuleiro = origem_coluna - offset + j;

            if (linha_tabuleiro >= 0 && linha_tabuleiro < TAMANHO_TABULEIRO &&
                coluna_tabuleiro >= 0 && coluna_tabuleiro < TAMANHO_TABULEIRO) {
                if (habilidade[i][j] == 1 && tabuleiro[linha_tabuleiro][coluna_tabuleiro] == AGUA) {
                    tabuleiro[linha_tabuleiro][coluna_tabuleiro] = HABILIDADE;
                }
            }
        }
    }
}

// Exibe o tabuleiro com símbolos visuais
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == AGUA) {
                printf("~ ");
            } else if (tabuleiro[i][j] == NAVIO) {
                printf("N ");
            } else if (tabuleiro[i][j] == HABILIDADE) {
                printf("* ");
            } else {
                printf("? ");
            }
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // Inicializa tabuleiro
    inicializa_tabuleiro(tabuleiro);

    // Posiciona navios
    posiciona_navio(tabuleiro, 1, 2, 0, 1, "horizontal");
    posiciona_navio(tabuleiro, 4, 5, 1, 0, "vertical");
    posiciona_navio(tabuleiro, 0, 0, 1, 1, "diagonal ↘");
    posiciona_navio(tabuleiro, 2, 7, 1, -1, "diagonal ↙");

    // Cria matrizes de habilidades
    cria_habilidade_cone(cone);
    cria_habilidade_cruz(cruz);
    cria_habilidade_octaedro(octaedro);

    // Aplica habilidades ao tabuleiro
    aplica_habilidade(tabuleiro, cone, 5, 2);       // Cone no ponto (5,2)
    aplica_habilidade(tabuleiro, cruz, 3, 7);       // Cruz no ponto (3,7)
    aplica_habilidade(tabuleiro, octaedro, 7, 7);   // Octaedro no ponto (7,7)

    // Exibe tabuleiro final
    exibir_tabuleiro(tabuleiro);

    return 0;
}
