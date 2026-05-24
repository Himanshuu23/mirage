#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1048576

void vector_add_cpu(float* a, float* b, float* c, int n) {
    for (int i = 0; i < n; i++) c[i] = a[i] + b[i];
}

int main() {
    float* a = (float*)malloc(N * sizeof(float));
    float* b = (float*)malloc(N * sizeof(float));
    float* c = (float*)malloc(N * sizeof(float));

    for (int i = 0; i < N; i++) {
        a[i] = (float)i;
        b[i] = (float)(i * 2);
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    vector_add_cpu(a, b, c, N);
    clock_gettime(CLOCK_MONOTONIC, &end);

    float ms = (end.tv_sec - start.tv_sec) * 1000.0f +
               (end.tv_nsec - start.tv_nsec) / 1e6f;

    printf("    CPU Vector Addition: %d elements \n\n", N);
    printf("CPU time : %.4f ms\n", ms);
    printf("\nSample results (first 4):\n");
    for (int i = 0; i < 4; i++) {
        printf("  [%d] %.1f + %.1f = %.1f\n", i, a[i], b[i], c[i]);
    }

    free(a); free(b); free(c);
    return 0;
}
