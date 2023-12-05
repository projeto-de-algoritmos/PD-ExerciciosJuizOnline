#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Algoritmo Bellman Ford
int shortestPath(int** flights, int flightsSize, int flightsColSize, int src, int dst, int k, int n) {
    // Aloca um array para armazenar as distancias minimas
    int* dist = (int*)malloc(n * sizeof(int));

    // Inicializa todas as distancias como infinito, exceto a origem que eh 0
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    // Loop principal do algoritmo
    for (int count = 0; count <= k; count++) {
        // Cria um array temporario para armazenar as distancias atuais
        int* temp = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            temp[i] = dist[i];
        }

        // Itera sobre os voos
        for (int i = 0; i < flightsSize; i++) {
            if (dist[flights[i][0]] == INT_MAX) {
                continue;
            }
            // Verifica e atualiza a distancia minima entre dois vertices
            if (temp[flights[i][1]] > dist[flights[i][0]] + flights[i][2]) {
                temp[flights[i][1]] = dist[flights[i][0]] + flights[i][2];
            }
        }

        // Libera a memoria do array anterior e atualiza para o novo array
        free(dist);
        dist = temp;
    }

    // Retorna o resultado final (distancia minima para o destino)
    int result = (dist[dst] == INT_MAX ? -1 : dist[dst]);
    free(dist);
    return result;
}

// Função que chama o algoritmo Bellman Ford
int findCheapestPrice(int n, int** flights, int flightsSize, int flightsColSize, int src, int dst, int k) {
    return shortestPath(flights, flightsSize, flightsColSize, src, dst, k, n);
}
