#include <stdio.h>

// Tamanho do tabuleiro (fixo 10x10)
#define TAMANHO_TABULEIRO 10

// Tamanho fixo dos navios
#define TAMANHO_NAVIO 3

// Valor que representa a água
#define AGUA 0

// Valor que representa parte do navio
#define NAVIO 3

int main() {
    // Declaração e inicialização da matriz do tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa todas as posições com 0 (água)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // Coordenadas iniciais para o navio horizontal
    int linhaH = 2;
    int colunaH = 4;

    // Coordenadas iniciais para o navio vertical
    int linhaV = 5;
    int colunaV = 1;

    // Validação: Verifica se o navio horizontal cabe no tabuleiro
    if (colunaH + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        // Verifica se as posições estão livres
        int sobreposicao = 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaH][colunaH + i] != AGUA) {
                sobreposicao = 1;
                break;
            }
        }

        if (!sobreposicao) {
            // Posiciona o navio horizontal
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaH][colunaH + i] = NAVIO;
            }
        } else {
            printf("Erro: Sobreposição detectada no navio horizontal.\n");
        }
    } else {
        printf("Erro: Navio horizontal não cabe no tabuleiro.\n");
    }

    // Validação: Verifica se o navio vertical cabe no tabuleiro
    if (linhaV + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        // Verifica se as posições estão livres
        int sobreposicao = 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaV + i][colunaV] != AGUA) {
                sobreposicao = 1;
                break;
            }
        }

        if (!sobreposicao) {
            // Posiciona o navio vertical
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaV + i][colunaV] = NAVIO;
            }
        } else {
            printf("Erro: Sobreposição detectada no navio vertical.\n");
        }
    } else {
        printf("Erro: Navio vertical não cabe no tabuleiro.\n");
    }

    // Exibição do tabuleiro
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
