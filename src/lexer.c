#include <ctype.h>
#include <string.h>
#include "../include/lexer.h"

Token lexer_next(Lexer* l) {
    Token t;
    memset(&t, 0, sizeof(Token));
    t.line = l->line;

    while (1) {
        char c = l->text[l->current_position];
        
        if (c == '\0') {
            t.kind = END_OF_FILE;
            return t;
        }

        else if (c == ',') {
            t.kind = COMMA;
            l->current_position++;
            return t;
        }

        else if (c == ';') {
            t.kind = SEMICOLON;
            l->current_position++;
            return t;
        }

        else if (c == '\n') {
            t.kind = NEW_LINE;
            l->line++;
            l->current_position++;
            return t;
        }

        else if (c == '[') {
            t.kind = LBRACKET;
            l->current_position++;
            return t;
        }

        else if (c == ']') {
            t.kind = RBRACKET;
            l->current_position++;
            return t;
        }

        else if (c == '(') {
            t.kind = LPAREN;
            l->current_position++;
            return t;
        }

        else if (c == ')') {
            t.kind = RPAREN;
            l->current_position++;
            return t;
        }

        else if (c == '{') {
            t.kind = LBRACE;
            l->current_position++;
            return t;
        }

        else if (c == '}') {
            t.kind = RBRACE;
            l->current_position++;
            return t;
        }

        else if (c == '/' && l->text[l->current_position + 1] == '/') {
            l->current_position += 2;
            while (l->text[l->current_position] != '\n' && l->text[l->current_position] != '\0') {
                l->current_position++;
            }
            return t;
        }
        
        else if (isalpha(c)) {
            int i = 0;
            char buf[64];
            while (l->text[l->current_position] == '.' || isalpha(l->text[l->current_position]) || isdigit(l->text[l->current_position]) || l->text[l->current_position] == '.') {
                buf[i++] = l->text[l->current_position++];
            }
            buf[i] = '\0';
            memcpy(t.text, buf, 64);
            t.kind = INSTR_NAME;
            return t;
        }

        else if (isdigit(c)) {
            int i = 0;
            char buf[64];
            while (isdigit(l->text[l->current_position])) {
                buf[i++] = l->text[l->current_position++];
            }
            buf[i] = '\0';
            memcpy(t.text, buf, 64);
            t.kind = NUMBER;
            return t;
        }

        else if (c == '%') {
            int i = 0;
            char buf[64];
            while (l->text[l->current_position] == '%' || isalpha(l->text[l->current_position]) || isdigit(l->text[l->current_position]) || l->text[l->current_position] == '.') {
                buf[i++] = l->text[l->current_position++];
            }
            buf[i] = '\0';
            memcpy(t.text, buf, 64);
            t.kind = REG_NAME;
            return t;
        }
       

        else if (c == '-') {
            l->current_position++;
            int i = 0;
            char buf[64];
            while (isdigit(l->text[l->current_position])) {
                buf[i++] = l->text[l->current_position++];
            }
            buf[i] = '\0';
            memcpy(t.text, buf, 64);
            t.kind = NUMBER;
            return t;
        }


        else if (c == '.') {
            l->current_position++;
            int i = 0;
            char buf[64];
            while (isalpha(l->text[l->current_position]) || isdigit(l->text[l->current_position]) || l->text[l->current_position] == '.') {
                buf[i++] = l->text[l->current_position++];
            }
            buf[i] = '\0';
            memcpy(t.text, buf, 64);
            t.kind = TYPE;
            return t;
        }

        else {
            l->current_position++;
        }
    }
}
