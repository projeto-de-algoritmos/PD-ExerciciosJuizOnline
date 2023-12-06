#include <stdio.h>

#define TAM_MAX 1000

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int lenLongestFibSubseq(int *arr, int arrSize) {
    int dp[TAM_MAX][TAM_MAX] = {0};
    int comprimentoMaximo = 0;

    for (int i = 2; i < arrSize; i++) {
        int numEsquerda = 0;
        int numDireita = i - 1;

        while (numEsquerda < numDireita) {
            int soma = arr[numEsquerda] + arr[numDireita];
            if (soma > arr[i]) {
                numDireita--;
            } else if (soma < arr[i]) {
                numEsquerda++;
            } else {
                dp[numDireita][i] = dp[numEsquerda][numDireita] + 1;
                comprimentoMaximo = max(comprimentoMaximo, dp[numDireita][i]);
                numEsquerda++;
                numDireita--;
            }
        }
    }

    if (comprimentoMaximo == 0) {
        return 0;
    }
    return comprimentoMaximo + 2;
}

int main() {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = sizeof(a) / sizeof(a[0]);

    int result = lenLongestFibSubseq(a, n);

    printf("%d\n", result);

    return 0;
}
