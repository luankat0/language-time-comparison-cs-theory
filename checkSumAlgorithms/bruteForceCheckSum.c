#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int subset_sum_bruteforce(int *arr, int n, int target) {
    unsigned long long total_masks = 1ULL << n;
    
    for (unsigned long long mask = 0; mask < total_masks; ++mask) {
        int sum = 0;

        for (int i = 0; i < n; ++i) {
            if (mask & (1ULL << i)) 
                sum+= arr[i];
        }

        if (sum == target)
            return 1;
    }
    return 0;
}

int main(void) {
    int sizes[] = {5 ,15 ,25};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    srand((unsigned) time(NULL));

    for (int idx = 0; idx < num_sizes; ++idx) {
        int n = sizes[idx];

        int *arr = malloc(n * sizeof(int));

        if (!arr) {
            fprintf(stderr, "Erro de alocacao para n = %d\n", n);
        }
        
        for (int i = 0; i < n; ++i) {
            arr[i] = rand() % 100;
        }

        printf("Array: [");
        for (int i = 0; i < n; ++i) {
            printf("%d", arr[i]);
            if (i < n - 1) printf(", ");
        }
        printf("]\n");

        int target = rand() % (n * 100);

        clock_t t_start = clock();
        int found = subset_sum_bruteforce(arr, n, target);
        clock_t t_end = clock();

        double seconds = (double)(t_end - t_start) / CLOCKS_PER_SEC;
        printf("n = %2d | target = %3d | found = %d | time = %.6f s\n\n", n, target, found, seconds);

        free(arr);

    }
}
