#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

char tabuleiro[3][3]; // Variáveis globais
int l, c;

void InicializarTab() {
    for (l = 0; l < 3; l++) {
        for (c = 0; c < 3; c++) {
            tabuleiro[l][c] = ' ';
        }
    }
}

void ImprimirTab() {
    printf("0    1    2\n");
    for (l = 0; l < 3; l++) {
        for (c = 0; c < 3; c++) {
            printf(" %c ", tabuleiro[l][c]);
            if (c < 2)
                printf("|");
            if (c == 2)
                printf(" %d ", l);
        }
        if (l < 2)
            printf("\n-----------");
        printf("\n");
    }
}

bool VerificarVitoria() {
    for (l = 0; l < 3; l++) {
        if (tabuleiro[l][0] == tabuleiro[l][1] && tabuleiro[l][1] == tabuleiro[l][2] && tabuleiro[l][0] != ' ') {
            printf("\nVitória do jogador %c na linha %d\n", tabuleiro[l][0], l);
            return true;
        }
    }

    for (c = 0; c < 3; c++) {
        if (tabuleiro[0][c] == tabuleiro[1][c] && tabuleiro[1][c] == tabuleiro[2][c] && tabuleiro[0][c] != ' ') {
            printf("\nVitória do jogador %c na coluna %d\n", tabuleiro[0][c], c);
            return true;
        }
    }

    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && tabuleiro[0][0] != ' ') {
        printf("\nVitória do jogador %c na diagonal principal\n", tabuleiro[0][0]);
        return true;
    }

    if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0] && tabuleiro[0][2] != ' ') {
        printf("\nVitória do jogador %c na diagonal secundária\n", tabuleiro[0][2]);
        return true;
    }

    return false;
}

bool VerificarEmpate() {
    for (l = 0; l < 3; l++) {
        for (c = 0; c < 3; c++) {
            if (tabuleiro[l][c] == ' ') {
                return false; 
            }
        }
    }
    return true; 
}

bool JogarNovamente() {
    char resposta;
    printf("Deseja jogar novamente? (s/n): ");
    scanf(" %c", &resposta);
    return (resposta == 's' || resposta == 'S');
}

void Entrada() {
    int jogada = 1;
    int linha, coluna;

    while (jogada < 9) {
        jogada++;
        printf("\nJogador %d\n", (jogada % 2) + 1);
        printf("Informe a linha e a coluna da jogada (0 a 2): ");
        scanf("%d%d", &linha, &coluna);

        if (linha < 0 || linha > 2 || coluna < 0 || coluna > 2 || tabuleiro[linha][coluna] != ' ') {
            printf("Jogada inválida. Tente novamente.\n");
            jogada--;
        } else {
            tabuleiro[linha][coluna] = (jogada % 2 == 1) ? 'X' : 'O';

            system("cls");
            ImprimirTab();

            if (VerificarVitoria()) {
                printf("Fim de jogo\n");
                if (JogarNovamente()) {
                    InicializarTab();
                    system("cls");
                    ImprimirTab();
                    jogada = 1;
                } else {
                    break;
                }
            } else if (VerificarEmpate()) {
                printf("Jogo empatado.\n");
                if (JogarNovamente()) {
                    InicializarTab();
                    system("cls");
                    ImprimirTab();
                    jogada = 1;
                } else {
                    break;
                }
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    InicializarTab();
    ImprimirTab();
    Entrada();
    return 0;
}
