#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TARGET 1000000

double get_elapsed_us(LARGE_INTEGER start, LARGE_INTEGER end, LARGE_INTEGER freq) {
    return (double)(end.QuadPart - start.QuadPart) * 1000000.0 / (double)freq.QuadPart;
}

bool subsetSumDP(int arr[], int n, int target) {
    bool *dp = calloc(target + 1, sizeof(bool));
    int *prev = calloc(target + 1, sizeof(int));  // para reconstruir o caminho

    dp[0] = true;

    LARGE_INTEGER freq, start_total, end_total;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start_total);

    for (int i = 0; i < n; i++) {
        for (int j = target; j >= arr[i]; j--) {
            if (dp[j - arr[i]] && !dp[j]) {
                dp[j] = true;
                prev[j] = i + 1; // guarda índice + 1 para diferenciar de 0
            }
        }
    }

    QueryPerformanceCounter(&end_total);
    double total_time_ms = get_elapsed_us(start_total, end_total, freq) / 1000.0;

    if (!dp[target]) {
        printf("Nenhum subconjunto encontrado com soma %d.\n", target);
        free(dp);
        free(prev);
        return false;
    }

    // Reconstruir subconjunto com tempo acumulado por elemento
    printf("Subconjunto encontrado com soma %d: { ", target);
    int curr = target;

    while (curr > 0) {
        LARGE_INTEGER start_element, end_element;
        QueryPerformanceCounter(&start_element);

        int idx = prev[curr] - 1;
        printf("\n\t%d ", arr[idx]);
        curr -= arr[idx];

        QueryPerformanceCounter(&end_element);
        double elapsed_us = get_elapsed_us(start_element, end_element, freq);
        printf("(tempo para este elemento: %.3f microsegundos)\n", elapsed_us);
    }
    printf("}\n");

    printf("Tempo total da busca: %.2f milissegundos\n ou %.4f segundos", total_time_ms, total_time_ms / 1000.0);

    free(dp);
    free(prev);
    return true;
}



int main() {
    char filename[100], fullpath[150];
    int arr[100000], n = 0, target;

    printf("Digite o nome do arquivo (ex: subset_1000.txt): ");
    scanf("%s", filename);

    printf("Digite o valor da soma alvo: ");
    scanf("%d", &target);

    sprintf(fullpath, "../../data/%s", filename);
    FILE *file = fopen(fullpath, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while (fscanf(file, "%d", &arr[n]) == 1 && n < 100000) n++;
    fclose(file);

    subsetSumDP(arr, n, target);
    return 0;
}
