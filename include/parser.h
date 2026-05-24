#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"

typedef enum {
    ADD_F32,
    SUB_F32,
    MUL_F32,
    DIV_F32,
    ADD_U32,
    SUB_U32,
    MUL_U32,
    LD_GLOBAL_F32,
    ST_GLOBAL_F32,
    LD_PARAM_U64,
    MOV_F32,
    MOV_U32,
    RET
} OpKind;

typedef struct {
    int     is_reg;
    char    name[64];
    int     imm;
} Operand;

typedef struct {
    OpKind  op;
    Operand dst;
    Operand src1;
    Operand src2;
} Instr;

typedef struct {
    Lexer   l;
    Token   current;
} Parser;

void parser_init(Parser* p, char* src);
Instr parser_next(Parser* p);

#endif
