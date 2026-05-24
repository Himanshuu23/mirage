#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cuda_runtime.h>

#define N 1048576  // 1 million elements

__global__ void vector_add_gpu(float* a, float* b, float* c, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) c[i] = a[i] + b[i];
}

void vector_add_cpu(float* a, float* b, float* c, int n) {
    for (int i = 0; i < n; i++) c[i] = a[i] + b[i];
}

int main() {
    float* h_a = (float*)malloc(N * sizeof(float));
    float* h_b = (float*)malloc(N * sizeof(float));
    float* h_c_gpu = (float*)malloc(N * sizeof(float));
    float* h_c_cpu = (float*)malloc(N * sizeof(float));

    for (int i = 0; i < N; i++) {
        h_a[i] = (float)i;
        h_b[i] = (float)(i * 2);
    }

    float *d_a, *d_b, *d_c;
    cudaMalloc(&d_a, N * sizeof(float));
    cudaMalloc(&d_b, N * sizeof(float));
    cudaMalloc(&d_c, N * sizeof(float));

    cudaMemcpy(d_a, h_a, N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, N * sizeof(float), cudaMemcpyHostToDevice);

    int blockSize = 256;
    int numBlocks = (N + blockSize - 1) / blockSize;

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // warm up
    vector_add_gpu<<<numBlocks, blockSize>>>(d_a, d_b, d_c, N);
    cudaDeviceSynchronize();

    cudaEventRecord(start);
    vector_add_gpu<<<numBlocks, blockSize>>>(d_a, d_b, d_c, N);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float gpu_ms = 0;
    cudaEventElapsedTime(&gpu_ms, start, stop);
    cudaMemcpy(h_c_gpu, d_c, N * sizeof(float), cudaMemcpyDeviceToHost);

    // CPU timing
    clock_t cpu_start = clock();
    vector_add_cpu(h_a, h_b, h_c_cpu, N);
    clock_t cpu_end = clock();
    float cpu_ms = 1000.0f * (float)(cpu_end - cpu_start) / CLOCKS_PER_SEC;

    // verify
    int correct = 1;
    for (int i = 0; i < N; i++) {
        if (h_c_gpu[i] != h_c_cpu[i]) { correct = 0; break; }
    }

    printf("=== Vector Addition: %d elements ===\n\n", N);
    printf("GPU time : %.4f ms\n", gpu_ms);
    printf("CPU time : %.4f ms\n", cpu_ms);
    printf("Speedup  : %.2fx\n", cpu_ms / gpu_ms);
    printf("Results  : %s\n\n", correct ? "CORRECT" : "MISMATCH");
    printf("Sample results (first 4):\n");
    for (int i = 0; i < 4; i++) {
        printf("  [%d] %.1f + %.1f = %.1f\n", i, h_a[i], h_b[i], h_c_gpu[i]);
    }

    cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);
    free(h_a); free(h_b); free(h_c_gpu); free(h_c_cpu);
    return 0;
}
