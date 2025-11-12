#include <stdio.h>

#define TAM 10      // Tamanho do tabuleiro (10x10)
#define NAVIO 3     // Valor que representa as partes de um navio
#define TAM_NAVIO 3 // Cada navio ocupa 3 posições

// -------------------- Funções utilitárias --------------------

// Inicializa o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Exibe o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n=== TABULEIRO BATALHA NAVAL ===\n\n");

    // Cabeçalho com números das colunas
    printf("    ");
    for (int j = 0; j < TAM; j++)
        printf("%d ", j);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d  ", i); // número da linha
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Verifica se uma posição já está ocupada (para evitar sobreposição)
int posicaoOcupada(int tabuleiro[TAM][TAM], int linha, int coluna) {
    return (tabuleiro[linha][coluna] == NAVIO);
}

// -------------------- Posicionamento de navios --------------------

// Posiciona um navio horizontalmente
void posicionarNavioHorizontal(int tabuleiro[TAM][TAM], int linha, int colunaInicial) {
    if (colunaInicial + TAM_NAVIO > TAM) {
        printf("Erro: navio horizontal ultrapassa o limite!\n");
        return;
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        if (posicaoOcupada(tabuleiro, linha, colunaInicial + i)) {
            printf("Erro: sobreposição detectada (horizontal)!\n");
            return;
        }
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha][colunaInicial + i] = NAVIO;
    }
}

// Posiciona um navio verticalmente
void posicionarNavioVertical(int tabuleiro[TAM][TAM], int linhaInicial, int coluna) {
    if (linhaInicial + TAM_NAVIO > TAM) {
        printf("Erro: navio vertical ultrapassa o limite!\n");
        return;
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        if (posicaoOcupada(tabuleiro, linhaInicial + i, coluna)) {
            printf("Erro: sobreposição detectada (vertical)!\n");
            return;
        }
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaInicial + i][coluna] = NAVIO;
    }
}

// Posiciona um navio diagonal para baixo e à direita
void posicionarNavioDiagonalPrincipal(int tabuleiro[TAM][TAM], int linhaInicial, int colunaInicial) {
    if (linhaInicial + TAM_NAVIO > TAM || colunaInicial + TAM_NAVIO > TAM) {
        printf("Erro: navio diagonal principal ultrapassa o limite!\n");
        return;
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        if (posicaoOcupada(tabuleiro, linhaInicial + i, colunaInicial + i)) {
            printf("Erro: sobreposição detectada (diagonal principal)!\n");
            return;
        }
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaInicial + i][colunaInicial + i] = NAVIO;
    }
}

// Posiciona um navio diagonal para baixo e à esquerda
void posicionarNavioDiagonalSecundaria(int tabuleiro[TAM][TAM], int linhaInicial, int colunaInicial) {
    if (linhaInicial + TAM_NAVIO > TAM || colunaInicial - TAM_NAVIO + 1 < 0) {
        printf("Erro: navio diagonal secundária ultrapassa o limite!\n");
        return;
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        if (posicaoOcupada(tabuleiro, linhaInicial + i, colunaInicial - i)) {
            printf("Erro: sobreposição detectada (diagonal secundária)!\n");
            return;
        }
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaInicial + i][colunaInicial - i] = NAVIO;
    }
}

// -------------------- Programa principal --------------------
int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // === Definição das coordenadas dos navios ===
    // (Todas dentro dos limites e sem sobreposição)
    int linhaH = 1, colunaH = 2; // Navio horizontal
    int linhaV = 5, colunaV = 7; // Navio vertical
    int linhaD1 = 0, colunaD1 = 0; // Navio diagonal principal
    int linhaD2 = 2, colunaD2 = 8; // Navio diagonal secundária

    // === Posicionamento dos 4 navios ===
    posicionarNavioHorizontal(tabuleiro, linhaH, colunaH);
    posicionarNavioVertical(tabuleiro, linhaV, colunaV);
    posicionarNavioDiagonalPrincipal(tabuleiro, linhaD1, colunaD1);
    posicionarNavioDiagonalSecundaria(tabuleiro, linhaD2, colunaD2);

    // === Exibição do resultado final ===
    exibirTabuleiro(tabuleiro);

    return 0;
}
