/**
 * @file util.c
 * @author André Lucas Maegima
 * @brief Implementação das funções utilitárias.
 * @version 1.0
 * @date 2019-12-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "globals.hpp"
#include "util.h"

/**
 * @brief O procedimento printToken imprime um token 
 * e seu lexema no arquivo symbtree.
 * 
 * @param token Identificador do token.
 * @param tokenString Descrição textual do token.
 */
void printToken(TokenType token, const char *tokenString){
    switch (token){
    case IF:
    case ELSE:
    case RETURN:
    case WHILE:
        fprintf(symbtree,
                "reserved word: %s\n", tokenString);
        break;
    case ATRIB:
        fprintf(symbtree, ":=\n");
        break;
    case SLT:
        fprintf(symbtree, "<\n");
        break;
    case SLTE:
        fprintf(symbtree, "<=\n");
        break;
    case SGT:
        fprintf(symbtree, ">\n");
        break;
    case SGTE:
        fprintf(symbtree, "<=\n");
        break;
    case EQUAL:
        fprintf(symbtree, "=\n");
        break;
    case DIFFERENT:
        fprintf(symbtree, "!=\n");
        break;
    case OPAREN:
        fprintf(symbtree, "(\n");
        break;
    case CPAREN:
        fprintf(symbtree, ")\n");
        break;
    case SEMICOLON:
        fprintf(symbtree, ";\n");
        break;
    case ADD:
        fprintf(symbtree, "+\n");
        break;
    case SUB:
        fprintf(symbtree, "-\n");
        break;
    case MULT:
        fprintf(symbtree, "*\n");
        break;
    case DIV:
        fprintf(symbtree, "/\n");
        break;
    case ENDFILE:
        fprintf(symbtree, "EOF\n");
        break;
    case NUM:
        fprintf(symbtree,
                "NUM, val= %s\n", tokenString);
        break;
    case ID:
        fprintf(symbtree,
                "ID, name= %s\n", tokenString);
        break;
    case ERR:
        fprintf(symbtree,
                "ERROR: %s\n", tokenString);
        break;
    default: /* should never happen */
        fprintf(symbtree, "Unknown token: %d\n", token);
    }
}

/**
 * @brief A função copyString cria e aloca uma nova
 * cópia da string passada como parâmetro.
 * 
 * @param s String a ser copiada.
 * @return char* Endereço da copia criada.
 */
char *copyString(char *s){
    int n;
    char *t;
    if (s == NULL)
        return NULL;
    n = strlen(s) + 1;
    t = (char *)malloc(n);
    if (t == NULL)
        fprintf(symbtree, "Out of memory error at line %d\n", scan->getLineNumber());
    else
        strcpy(t, s);
    return t;
}
