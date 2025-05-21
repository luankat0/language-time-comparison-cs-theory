#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

void printSubset(int arr[], int n, int mask) {
    printf("Subconjunto encontrado: {");
    for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
            printf("%d ", arr[i]);
        }
    }
    printf("}\n");
}

void subsetSum(int arr[], int n, int target) {
    int totalSubsets = pow(2, n);
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    for (int mask = 0; mask < totalSubsets; mask++) {
        int sum = 0;

        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum += arr[i];
            }
        }

        if (sum == target) {
            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

            printSubset(arr, n, mask);
            printf("Tempo de execucao ate o subconjunto: %.6f segundos\n\n", cpu_time_used);

            start = clock();
        }
    }
}

int main() {
    int arr[] = {3, 34, 4, 12, 5, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 9;

    printf("Subconjunto cuja soma eh %d.\n\n", target);
    subsetSum(arr, n, target);

    return 0;
}