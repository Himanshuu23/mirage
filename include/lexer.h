#ifndef LEXER_H
#define LEXER_H

typedef enum {
    INSTR_NAME,
    REG_NAME,
    TYPE,
    COMMA,
    LBRACKET,
    RBRACKET,
    LPAREN,
    RPAREN,
    SEMICOLON,
    LBRACE,
    RBRACE,
    NUMBER,
    LABEL,
    NEW_LINE,
    END_OF_FILE
} TokenKind;

typedef struct {
   TokenKind kind;
   char      text[64];
   int       line;
} Token;

typedef struct {
    char*   text;
    int     line;
    int     current_position;
} Lexer;

Token lexer_next(Lexer* l);

#endif
