#include <stdio.h>

#define TAM 10      // Tamanho fixo do tabuleiro (10x10)
#define NAVIO 3     // Valor que representa um navio no tabuleiro
#define TAM_NAVIO 3 // Tamanho fixo de cada navio (3 posições)

// Função para inicializar o tabuleiro com zeros (água)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0; // 0 representa água
        }
    }
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n=== TABULEIRO ===\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Função para posicionar um navio horizontalmente
void posicionarNavioHorizontal(int tabuleiro[TAM][TAM], int linha, int colunaInicial) {
    // Verifica se o navio cabe no tabuleiro
    if (colunaInicial + TAM_NAVIO > TAM) {
        printf("Erro: navio horizontal ultrapassa o limite do tabuleiro!\n");
        return;
    }

    // Posiciona o navio (3 representando o navio)
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha][colunaInicial + i] = NAVIO;
    }
}

// Função para posicionar um navio verticalmente
void posicionarNavioVertical(int tabuleiro[TAM][TAM], int linhaInicial, int coluna) {
    // Verifica se o navio cabe no tabuleiro
    if (linhaInicial + TAM_NAVIO > TAM) {
        printf("Erro: navio vertical ultrapassa o limite do tabuleiro!\n");
        return;
    }

    // Posiciona o navio (3 representando o navio)
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaInicial + i][coluna] = NAVIO;
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // === Coordenadas iniciais ===
    // (Esses valores podem ser alterados para testar diferentes posições)
    int linhaNavioHorizontal = 2; // Linha onde o navio horizontal começará
    int colunaNavioHorizontal = 4;

    int linhaNavioVertical = 5;   // Linha onde o navio vertical começará
    int colunaNavioVertical = 1;

    // === Validação simples para evitar sobreposição ===
    // Verifica se o navio vertical vai ocupar alguma das posições horizontais
    int sobrepoe = 0;
    for (int i = 0; i < TAM_NAVIO; i++) {
        for (int j = 0; j < TAM_NAVIO; j++) {
            if ((linhaNavioHorizontal == linhaNavioVertical + i) &&
                (colunaNavioHorizontal + j == colunaNavioVertical)) {
                sobrepoe = 1;
            }
        }
    }

    if (sobrepoe) {
        printf("Erro: os navios se sobrepõem! Ajuste as coordenadas.\n");
        return 1; // Encerra o programa
    }

    // Posiciona os dois navios no tabuleiro
    posicionarNavioHorizontal(tabuleiro, linhaNavioHorizontal, colunaNavioHorizontal);
    posicionarNavioVertical(tabuleiro, linhaNavioVertical, colunaNavioVertical);

    // Exibe o resultado final
    exibirTabuleiro(tabuleiro);

    return 0;
}
