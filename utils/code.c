/**
 * @file code.c
 * @author André Lucas Maegima
 * @brief Implementação para as funções utilitárias para 
 * geração do código intermediário.
 * @version 0.1
 * @date 2019-12-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "globals.h"
#include "code.h"

void emitComment(const char *c){
    if (TraceCode)
        fprintf(code, "* %s\n", c);
}

void emitQuadruple(const char *op, const char *first, const char *second, const char *third){
    fprintf(code, "(%s, %s, %s, %s)\n", op, first, second, third);
}