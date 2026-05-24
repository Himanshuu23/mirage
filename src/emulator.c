#include "../include/emulator.h"
#include <stdlib.h>
#include <string.h>

static int freg(char* name) {
    return atoi(name + 2);
}

static int rreg(char* name) {
    return atoi(name + 2);
}

static int dreg(char* name) {
    return atoi(name + 3);
}

Emulator* emulator_create(int num_threads, int global_mem_size) {
    Emulator* e = (Emulator*)malloc(sizeof(Emulator));

    e->threads = (Thread*)malloc(num_threads * sizeof(Thread));
    memset(e->threads, 0, num_threads * sizeof(Thread));

    e->global_mem = (unsigned char*)malloc(global_mem_size);
    memset(e->global_mem, 0, global_mem_size);

    e->num_threads = num_threads;
    e->global_mem_size = global_mem_size;

    return e;
}

void emulator_free(Emulator* e) {
    free(e->threads);
    free(e->global_mem);
    free(e);
}

static void execute(Thread* t, Instr* instr, unsigned char* gmem) {
    switch(instr->op) {
        case ADD_F32:
            t->fregs[freg(instr->dst.name)] = t->fregs[freg(instr->src1.name)] + t->fregs[freg(instr->src2.name)];
            break;
       
        case SUB_F32:
            t->fregs[freg(instr->dst.name)] = t->fregs[freg(instr->src1.name)] - t->fregs[freg(instr->src2.name)];
            break;
        
        case MUL_F32:
            t->fregs[freg(instr->dst.name)] = t->fregs[freg(instr->src1.name)] * t->fregs[freg(instr->src2.name)];
            break;
      
        case DIV_F32:
            t->fregs[freg(instr->dst.name)] = t->fregs[freg(instr->src1.name)] / t->fregs[freg(instr->src2.name)];
            break;

        case ADD_U32:
            t->regs[rreg(instr->dst.name)] = t->regs[rreg(instr->src1.name)] + t->regs[rreg(instr->src2.name)];
            break;
        
        case SUB_U32:
            t->regs[rreg(instr->dst.name)] = t->regs[rreg(instr->src1.name)] - t->regs[rreg(instr->src2.name)];
            break;
      
        case MUL_U32:
            t->regs[rreg(instr->dst.name)] = t->regs[rreg(instr->src1.name)] * t->regs[rreg(instr->src2.name)];
            break;
        
        case LD_GLOBAL_F32:
            t->fregs[freg(instr->dst.name)] = *(float*)(gmem + t->dregs[dreg(instr->src1.name)]);
            break;

        case ST_GLOBAL_F32:
            *(float*)(gmem + t->dregs[dreg(instr->dst.name)]) = t->fregs[freg(instr->src1.name)];
            break;

        case LD_PARAM_U64:
            t->dregs[dreg(instr->dst.name)] = t->dregs[dreg(instr->src1.name)];
            break;

        case MOV_F32:
            t->fregs[freg(instr->dst.name)] = t->fregs[freg(instr->src1.name)];
            break;

        case MOV_U32:
            t->regs[rreg(instr->dst.name)] = t->regs[rreg(instr->src1.name)];
            break;

        case RET:
            break;

        default:
            break;
    }
}

void emulator_run(Emulator* e, Instr* instr, int count) {
    for (int t = 0; t < e->num_threads; t++) {
        e->threads[t].tid_x = t;
        for (int i = 0; i < count; i++) {
            execute(&e->threads[t], &instr[i], e->global_mem);
        }
    }
}
