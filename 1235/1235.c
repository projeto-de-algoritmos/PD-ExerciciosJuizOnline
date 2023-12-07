#include <stdio.h>
#include <stdlib.h>

struct tarefa {
    int startTime;
    int endTime;
    int profit;
};

// Funcao de comparacao para ordenar as tarefas por tempo de termino
int comparaTarefas(const void *a, const void *b) {
    return ((struct tarefa*)a)->endTime - ((struct tarefa*)b)->endTime;
}

// Funcao para encontrar o indice da tarefa que termina no momento dado ou antes
int buscarIndice(struct tarefa tarefas[], int index) {
    int low = 0, high = index - 1;
    int result = -1;  // Inicializa como -1 para o caso em que nao ha tarefa compativel

    while (low <= high) {
        int mid = (low + high) / 2;
        if (tarefas[mid].endTime <= tarefas[index].startTime) {
            result = mid;  // Atualiza o resultado, mas continua a busca a esquerda
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return result;
}

// Funcao principal
int jobScheduling(int* startTime, int startTimeSize, int* endTime, int endTimeSize, int* profit, int profitSize) {
    // Aloca um array dinamicamente
    struct tarefa *tarefas = (struct tarefa*)malloc(startTimeSize * sizeof(struct tarefa));

    for (int i = 0; i < startTimeSize; i++) {
        // Preenche o array com os dados fornecidos
        tarefas[i].startTime = startTime[i];
        tarefas[i].endTime = endTime[i];
        tarefas[i].profit = profit[i];
    }

    // Ordena as tarefas por tempo de termino
    qsort(tarefas, startTimeSize, sizeof(struct tarefa), comparaTarefas);

    // Aloca um array para armazenar as solucoes otimas
    int *dp = (int*)malloc(startTimeSize * sizeof(int));
    dp[0] = tarefas[0].profit;

    // Preenche a tabela dinamica
    for (int i = 1; i < startTimeSize; i++) {
        // Lucro pegando a tarefa atual
        int inclProf = tarefas[i].profit;
        int l = buscarIndice(tarefas, i);

        if (l != -1){
            inclProf += dp[l];
        }

        // Lucro NAO pegando a tarefa atual
        int exclProf = dp[i - 1];

        // Escolhe o maximo entre pegar ou nao pegar a tarefa atual
        dp[i] = (inclProf > exclProf) ? inclProf : exclProf;
    }

    // Armazena o resultado final
    int result = dp[startTimeSize - 1];

    // Libera a memoria alocada
    free(tarefas);
    free(dp);

    return result;
}