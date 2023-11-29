#include <stdio.h>

int lengthOfLIS(int nums[], int n) {
    int sequenciaCrescente[n];

    for (int i = 0; i < n; i++) {
        sequenciaCrescente[i] = 1;
    }

    int tamanhoMaximo = 1;

    for (int i = 1; i < n; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (nums[j] < nums[i] && sequenciaCrescente[i] < sequenciaCrescente[j] + 1) {
                sequenciaCrescente[i] = sequenciaCrescente[j] + 1;
            }
        }

        if (tamanhoMaximo < sequenciaCrescente[i]) {
            tamanhoMaximo = sequenciaCrescente[i];
        }
    }

    return tamanhoMaximo;
}

int main() {
    int nums[] = {10, 9, 2, 5, 3, 7, 101, 18};
    int n = sizeof(nums) / sizeof(nums[0]);

    int result = lengthOfLIS(nums, n);

    printf("Length of Longest Increasing Subsequence: %d\n", result);

    return 0;
}