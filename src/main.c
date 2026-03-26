#include "../include/lexer.h"
#include <stdio.h>
#include <stdlib.h>

const char* kind_to_str(TokenKind k) {
    switch(k) {
        case INSTR_NAME: return "INSTR_NAME";
        case REG_NAME:   return "REG_NAME";
        case TYPE:       return "TYPE";
        case NUMBER:     return "NUMBER";
        case LABEL:      return "LABEL";
        case COMMA:      return "COMMA";
        case SEMICOLON:  return "SEMICOLON";
        case LBRACKET:   return "LBRACKET";
        case RBRACKET:   return "RBRACKET";
        case LPAREN:     return "LPAREN";
        case RPAREN:     return "RPAREN";
        case LBRACE:     return "LBRACE";
        case RBRACE:     return "RBRACE";
        case NEW_LINE:   return "NEWLINE";
        case END_OF_FILE: return "EOF";
        default:         return "UNKNOWN";
    }
}

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

    Lexer l;
    l.text             = src;
    l.current_position = 0;
    l.line             = 1;

    while (1) {
        Token t = lexer_next(&l);
        printf("%s: %s\n", kind_to_str(t.kind), t.text);
        if (t.kind == END_OF_FILE) break;
    }

    free(src);
    return 0;
}
