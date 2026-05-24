#include "../include/parser.h"
#include <string.h>

void advance(Parser* p) {
    p->current = lexer_next(&p->l);
}

void parser_init(Parser* p, char* src) {
    p->l.text = src;
    p->l.current_position = 0;
    p->l.line = 1;

    p->current = lexer_next(&p->l);
}

Instr parser_next(Parser *p) {
    Instr instr;
    memset(&instr, 0, sizeof(Instr));

    while (p->current.kind == NEW_LINE) advance(p);

    if (p->current.kind == END_OF_FILE) {
        instr.op = RET;

        return instr;
    }

    if (strcmp(p->current.text, "add.f32") == 0) {
        instr.op = ADD_F32;
        advance(p);

        strcpy(instr.dst.name, p->current.text);
        instr.dst.is_reg = 1;
        advance(p);
        advance(p);

        strcpy(instr.src1.name, p->current.text);
        instr.src1.is_reg = 1;
        advance(p);
        advance(p);

        strcpy(instr.src2.name, p->current.text);
        instr.src2.is_reg = 1;
        advance(p);
        advance(p);

        return instr;
    }
    
    if (strcmp(p->current.text, "sub.f32") == 0) {
        instr.op = SUB_F32;
        advance(p);

        strcpy(instr.dst.name, p->current.text);
        instr.dst.is_reg = 1;
        advance(p);
        advance(p);

        strcpy(instr.src1.name, p->current.text);
        instr.src1.is_reg = 1;
        advance(p);
        advance(p);

        strcpy(instr.src2.name, p->current.text);
        instr.src2.is_reg = 1;
        advance(p);
        advance(p);

        return instr;
    }
    
    if (strcmp(p->current.text, "mul.f32") == 0) {
        instr.op = MUL_F32;
        advance(p);

        strcpy(instr.dst.name, p->current.text);
        instr.dst.is_reg = 1;
        advance(p);
        advance(p);

        strcpy(instr.src1.name, p->current.text);
        instr.src1.is_reg = 1;
        advance(p);
        advance(p);

        strcpy(instr.src2.name, p->current.text);
        instr.src2.is_reg = 1;
        advance(p);
        advance(p);

        return instr;
    }

    if (strcmp(p->current.text, "div.f32") == 0) {
        instr.op = DIV_F32;
        advance(p);

        strcpy(instr.dst.name, p->current.text);
        instr.dst.is_reg = 1;
        advance(p);
        advance(p);

        strcpy(instr.src1.name, p->current.text);
        instr.src1.is_reg = 1;
        advance(p);
        advance(p);

        strcpy(instr.src2.name, p->current.text);
        instr.src2.is_reg = 1;
        advance(p);
        advance(p);

        return instr;
    }

    if (strcmp(p->current.text, "add.u32") == 0) {
        instr.op = ADD_U32;
        advance(p);

        strcpy(instr.dst.name, p->current.text);
        instr.dst.is_reg = 1;
        advance(p);
        advance(p);

        strcpy(instr.src1.name, p->current.text);
        instr.src1.is_reg = 1;
        advance(p);
        advance(p);

        strcpy(instr.src2.name, p->current.text);
        instr.src2.is_reg = 1;
        advance(p);
        advance(p);

        return instr;
    }


    if (strcmp(p->current.text, "sub.u32") == 0) {
        instr.op = SUB_U32;
        advance(p);

        strcpy(instr.dst.name, p->current.text);
        instr.dst.is_reg = 1;
        advance(p);
        advance(p);

        strcpy(instr.src1.name, p->current.text);
        instr.src1.is_reg = 1;
        advance(p);
        advance(p);

        strcpy(instr.src2.name, p->current.text);
        instr.src2.is_reg = 1;
        advance(p);
        advance(p);

        return instr;
    }

    if (strcmp(p->current.text, "mul.u32") == 0) {
        instr.op = MUL_U32;
        advance(p);

        strcpy(instr.dst.name, p->current.text);
        instr.dst.is_reg = 1;
        advance(p);
        advance(p);

        strcpy(instr.src1.name, p->current.text);
        instr.src1.is_reg = 1;
        advance(p);
        advance(p);

        strcpy(instr.src2.name, p->current.text);
        instr.src2.is_reg = 1;
        advance(p);
        advance(p);

        return instr;
    }

    if (strcmp(p->current.text, "ld.global.f32") == 0) {
        instr.op = LD_GLOBAL_F32;
        advance(p);
        strcpy(instr.dst.name, p->current.text);
        instr.dst.is_reg = 1;
        advance(p);
        advance(p);
        advance(p);
        strcpy(instr.src1.name, p->current.text);
        instr.src1.is_reg = 1;
        advance(p);
        advance(p);
        advance(p);
        
        return instr;
    }

    if (strcmp(p->current.text, "st.global.f32") == 0) {
        instr.op = ST_GLOBAL_F32;
        advance(p);
        advance(p);
        strcpy(instr.dst.name, p->current.text);
        instr.dst.is_reg = 1;
        advance(p);
        advance(p);
        advance(p);
        strcpy(instr.src1.name, p->current.text);
        instr.src1.is_reg = 1;
        advance(p);
        advance(p);
        advance(p);

        return instr;
    }

    if (strcmp(p->current.text, "ld.param.u64") == 0) {
        instr.op = LD_PARAM_U64;
        advance(p);
        strcpy(instr.dst.name, p->current.text);
        instr.dst.is_reg = 1;
        advance(p);
        advance(p);
        advance(p);
        strcpy(instr.src1.name, p->current.text);
        instr.src1.is_reg = 1;
        advance(p);
        advance(p);
        advance(p);

        return instr;
    }

    if (strcmp(p->current.text, "mov.f32") == 0) {
        instr.op = MOV_F32;
        advance(p);
        strcpy(instr.dst.name, p->current.text);
        instr.dst.is_reg = 1;
        advance(p);
        advance(p);
        strcpy(instr.src1.name, p->current.text);
        instr.src1.is_reg = 1;
        advance(p);
        advance(p);

        return instr;
    }

    if (strcmp(p->current.text, "mov.u32") == 0) {
        instr.op = MOV_U32;
        advance(p);
        strcpy(instr.dst.name, p->current.text);
        instr.dst.is_reg = 1;
        advance(p);
        advance(p);
        strcpy(instr.src1.name, p->current.text);
        instr.src1.is_reg = 1;
        advance(p);
        advance(p);

        return instr;
    }
    
    if (strcmp(p->current.text, "ret") == 0) {
        instr.op = RET;
        advance(p);

        return instr;
    }

    advance(p);
    return instr;
}
