#ifndef EMULATOR_H
#define EMULATOR_H
#include "parser.h"

typedef struct {
    float               fregs[256];
    unsigned int        regs[256];
    unsigned long long  dregs[256];
    int                 tid_x;
    int                 bid_x;
} Thread;

typedef struct {
    Thread*         threads;
    int             num_threads;
    unsigned char*  global_mem;
    int             global_mem_size;
} Emulator;

Emulator* emulator_create(int num_threads, int global_mem_size);
void emulator_run(Emulator* e, Instr* instrs, int count);
void emulator_free(Emulator* e);

#endif
