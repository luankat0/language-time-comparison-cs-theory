#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define LCG_SEED 12345

static uint32_t lcg_state = LCG_SEED;

uint32_t lcg_rand(void) {
    lcg_state = (1103515245U * lcg_state + 12345U) & 0x7fffffff;
    return lcg_state;
}

int subset_sum_bruteforce(int *arr, int n, int target) {
    unsigned long long total_masks = 1ULL << n;
    for (unsigned long long mask = 0; mask < total_masks; ++mask) {
        int soma = 0;
        for (int i = 0; i < n; ++i) {
            if (mask & (1ULL << i)) {
                soma += arr[i];
            }
        }
        if (soma == target) {
            return 1;
        }
    }
    return 0;
}


int ler_arquivo(const char *nome_arquivo, int *arr) {
    FILE *fp = fopen(nome_arquivo, "r");
    if (!fp) {
        fprintf(stderr, "Erro ao abrir %s\n", nome_arquivo);
        exit(EXIT_FAILURE);
    }
    int count = 0;
    while (fscanf(fp, "%d", &arr[count]) != EOF) {
        count++;
    }
    fclose(fp);
    return count;
}


void testar_subset(const char *nome_arquivo, int iteracao, FILE *fp_csv) {
    int arr[1024];
    int n = ler_arquivo(nome_arquivo, arr);

    long long soma_total = 0;
    for (int i = 0; i < n; ++i) {
        soma_total += arr[i];
    }

    int target = (int)(lcg_rand() % (soma_total + 1));

    clock_t inicio = clock();
    int found = subset_sum_bruteforce(arr, n, target);
    clock_t fim = clock();
    double duracao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    fprintf(fp_csv, "%d,%s,%d,%d,%d,%.6f\n",
            iteracao,
            nome_arquivo,
            n,
            target,
            found,
            duracao);

    printf("%d, %s, %d, %d, %d, %.6f\n",
           iteracao,
           nome_arquivo,
           n,
           target,
           found,
           duracao);
}

int main(void) {
    const char *arquivos[] = {
        "data/subset_pequeno.txt",
        "data/subset_medio.txt",
        "data/subset_grande.txt"
    };
    const int num_testes = 3;

    FILE *fp_csv = fopen("data/dataBaseC.csv", "w");
    if (!fp_csv) {
        fprintf(stderr, "Nao foi possível criar 'data/dataBaseC.csv'\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fp_csv, "iteracao,arquivo,n,target,found,duracao\n");

    for (int iter = 1; iter <= 50; ++iter) {

        for (int i = 0; i < num_testes; ++i) {
            testar_subset(arquivos[i], iter, fp_csv);
        }
    }
    fclose(fp_csv);
    return 0;
}
