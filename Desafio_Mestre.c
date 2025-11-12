#include <stdio.h>
#include <stdlib.h>

#define TAM 10       // Tamanho do tabuleiro (10x10)
#define NAVIO 3      // Valor que representa navio
#define HABILIDADE 5 // Valor que representa área de habilidade
#define H 5          // Tamanho das matrizes de habilidade (5x5)

// -------------------- Funções utilitárias --------------------

// Inicializa o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;
}

// Exibe o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n=== TABULEIRO FINAL ===\n\n");
    printf("    ");
    for (int j = 0; j < TAM; j++)
        printf("%d ", j);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d  ", i);
        for (int j = 0; j < TAM; j++) {
            int valor = tabuleiro[i][j];
            if (valor == 0)
                printf("~ ");  // água
            else if (valor == NAVIO)
                printf("N ");  // navio
            else if (valor == HABILIDADE)
                printf("* ");  // área de habilidade
            else
                printf("? ");  // fallback
        }
        printf("\n");
    }
    printf("\nLegenda: ~ = Água | N = Navio | * = Área de Habilidade\n\n");
}

// -------------------- Construção das matrizes de habilidades --------------------

// Cria uma matriz em formato de cone (triângulo apontando para baixo)
void criarMatrizCone(int matriz[H][H]) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < H; j++) {
            // Área cresce conforme descemos nas linhas
            if (j >= (H / 2) - i && j <= (H / 2) + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria uma matriz em formato de cruz
void criarMatrizCruz(int matriz[H][H]) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < H; j++) {
            if (i == H / 2 || j == H / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria uma matriz em formato de octaedro (losango)
void criarMatrizOctaedro(int matriz[H][H]) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < H; j++) {
            // Distância do centro define o formato losangular
            if (abs(i - H / 2) + abs(j - H / 2) <= H / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// -------------------- Funções de sobreposição --------------------

// Sobrepõe uma matriz de habilidade no tabuleiro, centrando-a em (centroLinha, centroColuna)
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[H][H], int centroLinha, int centroColuna) {
    int deslocamento = H / 2;

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < H; j++) {
            if (habilidade[i][j] == 1) {
                int linhaTab = centroLinha - deslocamento + i;
                int colTab = centroColuna - deslocamento + j;

                // Verifica se a posição está dentro dos limites do tabuleiro
                if (linhaTab >= 0 && linhaTab < TAM && colTab >= 0 && colTab < TAM) {
                    // Se não houver navio, marca como área de habilidade
                    if (tabuleiro[linhaTab][colTab] != NAVIO)
                        tabuleiro[linhaTab][colTab] = HABILIDADE;
                }
            }
        }
    }
}

// -------------------- Programa principal --------------------
int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // === Posicionando alguns navios manualmente ===
    tabuleiro[2][3] = NAVIO;
    tabuleiro[2][4] = NAVIO;
    tabuleiro[2][5] = NAVIO;

    tabuleiro[6][7] = NAVIO;
    tabuleiro[7][7] = NAVIO;
    tabuleiro[8][7] = NAVIO;

    // === Criando as matrizes das habilidades ===
    int cone[H][H], cruz[H][H], octaedro[H][H];

    criarMatrizCone(cone);
    criarMatrizCruz(cruz);
    criarMatrizOctaedro(octaedro);

    // === Definindo as posições de origem das habilidades no tabuleiro ===
    int origemConeLinha = 1, origemConeColuna = 2;
    int origemCruzLinha = 5, origemCruzColuna = 5;
    int origemOctaedroLinha = 7, origemOctaedroColuna = 2;

    // === Aplicando as habilidades ao tabuleiro ===
    aplicarHabilidade(tabuleiro, cone, origemConeLinha, origemConeColuna);
    aplicarHabilidade(tabuleiro, cruz, origemCruzLinha, origemCruzColuna);
    aplicarHabilidade(tabuleiro, octaedro, origemOctaedroLinha, origemOctaedroColuna);

    // === Exibição do tabuleiro final ===
    exibirTabuleiro(tabuleiro);

    return 0;
}
