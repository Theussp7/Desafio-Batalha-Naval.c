#include <stdio.h>

#define TAMANHO_TABULEIRO 10   // Tamanho fixo do tabuleiro
#define TAMANHO_NAVIO 3        // Tamanho fixo dos navios
#define AGUA 0                 // Valor que representa água
#define NAVIO 3                // Valor que representa parte de um navio

// Função para verificar se há sobreposição (para qualquer direção)
int verifica_sobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int delta_linha, int delta_coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int nova_linha = linha + i * delta_linha;
        int nova_coluna = coluna + i * delta_coluna;
        if (tabuleiro[nova_linha][nova_coluna] != AGUA) {
            return 1; // Houve sobreposição
        }
    }
    return 0; // Nenhuma sobreposição
}

// Função para posicionar um navio em qualquer direção
void posiciona_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int delta_linha, int delta_coluna, const char* tipo) {
    // Verifica se o navio cabe no tabuleiro
    int linha_final = linha + (TAMANHO_NAVIO - 1) * delta_linha;
    int coluna_final = coluna + (TAMANHO_NAVIO - 1) * delta_coluna;

    if (linha_final < 0 || linha_final >= TAMANHO_TABULEIRO || coluna_final < 0 || coluna_final >= TAMANHO_TABULEIRO) {
        printf("Erro: Navio %s não cabe no tabuleiro a partir de (%d, %d)\n", tipo, linha, coluna);
        return;
    }

    // Verifica se há sobreposição
    if (verifica_sobreposicao(tabuleiro, linha, coluna, delta_linha, delta_coluna)) {
        printf("Erro: Sobreposição detectada no navio %s em (%d, %d)\n", tipo, linha, coluna);
        return;
    }

    // Posiciona o navio
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int nova_linha = linha + i * delta_linha;
        int nova_coluna = coluna + i * delta_coluna;
        tabuleiro[nova_linha][nova_coluna] = NAVIO;
    }
}

// Função para imprimir o tabuleiro
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // 1. Inicializa o tabuleiro com água (0)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // 2. Posiciona navios (2 horizontais/verticais, 2 diagonais)

    // Navio 1: Horizontal (linha 1, coluna 2)
    posiciona_navio(tabuleiro, 1, 2, 0, 1, "horizontal");

    // Navio 2: Vertical (linha 4, coluna 5)
    posiciona_navio(tabuleiro, 4, 5, 1, 0, "vertical");

    // Navio 3: Diagonal ↘ (linha 0, coluna 0)
    posiciona_navio(tabuleiro, 0, 0, 1, 1, "diagonal ↘");

    // Navio 4: Diagonal ↙ (linha 2, coluna 7)
    posiciona_navio(tabuleiro, 2, 7, 1, -1, "diagonal ↙");

    // 3. Exibe o tabuleiro
    exibir_tabuleiro(tabuleiro);

    return 0;
}
