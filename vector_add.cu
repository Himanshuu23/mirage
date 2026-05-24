#include <stdio.h>
#include <cuda_runtime.h>

__global__ void vector_add(float* a, float* b, float* c, int n) {
    int i = threadIdx.x;
    if (i < n) c[i] = a[i] + b[i];
}

int main() {
    int n = 4;
    float h_a[] = {1.0, 2.0, 3.0, 4.0};
    float h_b[] = {10.0, 20.0, 30.0, 40.0};
    float h_c[4] = {0};

    float *d_a, *d_b, *d_c;
    cudaMalloc(&d_a, n * sizeof(float));
    cudaMalloc(&d_b, n * sizeof(float));
    cudaMalloc(&d_c, n * sizeof(float));

    cudaMemcpy(d_a, h_a, n * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, n * sizeof(float), cudaMemcpyHostToDevice);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);
    vector_add<<<1, n>>>(d_a, d_b, d_c, n);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float ms = 0;
    cudaEventElapsedTime(&ms, start, stop);

    cudaMemcpy(h_c, d_c, n * sizeof(float), cudaMemcpyDeviceToHost);

    printf("=== GPU Results ===\n");
    for (int i = 0; i < n; i++) {
        printf("thread %d: a=%.1f  b=%.1f  c=%.1f\n", i, h_a[i], h_b[i], h_c[i]);
    }
    printf("GPU time: %.4fms\n", ms);

    cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);
    return 0;
}
