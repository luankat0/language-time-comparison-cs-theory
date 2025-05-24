#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_TARGET 1000000

double get_elapsed_us(LARGE_INTEGER start, LARGE_INTEGER end, LARGE_INTEGER freq) {
    return (double)(end.QuadPart - start.QuadPart) * 1000000.0 / (double)freq.QuadPart;
}

bool subsetSumDP(int arr[], int n, int target, double *tempo_total_ms) {
    bool *dp = calloc(target + 1, sizeof(bool));
    int *prev = calloc(target + 1, sizeof(int));

    dp[0] = true;

    LARGE_INTEGER freq, start_total, end_total;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start_total);

    for (int i = 0; i < n; i++) {
        for (int j = target; j >= arr[i]; j--) {
            if (dp[j - arr[i]] && !dp[j]) {
                dp[j] = true;
                prev[j] = i + 1;
            }
        }
    }

    QueryPerformanceCounter(&end_total);
    *tempo_total_ms = get_elapsed_us(start_total, end_total, freq) / 1000.0;

    bool resultado = dp[target];

    free(dp);
    free(prev);
    return resultado;
}

int main() {
    srand(time(NULL));

    char filename[100], fullpath[150];
    int arr[100000], n = 0, target;
    FILE *inFile, *outFile;

    printf("Digite o nome do arquivo de entrada (ex: subset_1000.txt): ");
    scanf("%s", filename);
    sprintf(fullpath, "../../data/%s", filename);

    // Captura o nome base do arquivo (sem extensão)
    char *ponto = strchr(filename, '.');
    if (ponto != NULL) *ponto = '\0';  // remove extensão

    inFile = fopen(fullpath, "r");
    if (!inFile) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    while (fscanf(inFile, "%d", &arr[n]) == 1 && n < 100000) n++;
    fclose(inFile);

    outFile = fopen("dataBaseC.csv", "w");
    if (!outFile) {
        printf("Erro ao criar arquivo CSV de saída.\n");
        return 1;
    }

    fprintf(outFile, "Target;Tempo Total (ms);Subset\n");

    for (int cont = 0; cont < 100; cont++) {
        target = rand() % MAX_TARGET;

        double tempo_total;
        bool encontrado = subsetSumDP(arr, n, target, &tempo_total);

        if (encontrado) {
            fprintf(outFile, "%d;%.3f;%s\n", target, tempo_total, filename);
        }
    }

    fclose(outFile);
    printf("Execução concluída. Resultados salvos em dataBaseC.csv\n");
    return 0;
}
