#include "../include/parser.h"
#include "../include/emulator.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: ptx-emu input.ptx\n");
        return 1;
    }

    FILE* f = fopen(argv[1], "rb");
    if (!f) {
        fprintf(stderr, "could not open %s\n", argv[1]);
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* src = (char*)malloc(size + 1);
    fread(src, 1, size, f);
    src[size] = '\0';
    fclose(f);

    Parser p;
    parser_init(&p, src);

    Instr instrs[256];
    int count = 0;
    while (1) {
        Instr instr = parser_next(&p);
        instrs[count++] = instr;
        if (instr.op == RET) break;
    }
    
    Emulator* e = emulator_create(4, 64 * 1024 * 1024);
   
    float* a = (float*)e->global_mem;
    float* b = (float*)(e->global_mem + 16);
    float* c = (float*)(e->global_mem + 32);
    for (int i = 0; i < 4; i++) {
        a[i] = (float)(i + 1);
        b[i] = (float)((i + 1) * 10);
    }
    for (int i = 0; i < 4; i++) {
        e->threads[i].dregs[1] = i * sizeof(float);      
        e->threads[i].dregs[2] = 16 + i * sizeof(float);
        e->threads[i].dregs[3] = 32 + i * sizeof(float);
    }

    clock_t start = clock();
    emulator_run(e, instrs, count);
    clock_t end = clock();
    double ms = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;

    printf("    Emulator Results\n");
    for (int i = 0; i < 4; i++) {
        printf("thread %d: a=%.1f  b=%.1f  c=%.1f\n",
               i, a[i], b[i], c[i]);
    }
    printf("Emulator time: %.4fms\n", ms);

    emulator_free(e);
    free(src);
    return 0;
}
