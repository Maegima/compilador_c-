/**
 * @file code.h
 * @author André Lucas Maegima
 * @brief Interface para as funções utilitárias para 
 * geração do código intermediário.
 * @version 0.1
 * @date 2019-12-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _CODE_H_
#define _CODE_H_

/* Procedure emitComment prints a comment line 
 * with comment c in the code file
 */

/**
 * @brief O procedimento emitComment imprime um 
 * linha de comentário no arquivo de código.
 * 
 * @param c Comentário.
 */
void emitComment(const char * c);

/**
 * @brief O procedimento emitQuadruple imprime no 
 * arquivo de código o código intermediário 
 * na forma de quadrupla.
 * 
 * @param op Operador.
 * @param first Primeiro parâmetro.
 * @param second Segundo parâmetro.
 * @param third Terceiro parâmetro.
 */
void emitQuadruple(const char *op,const char *first, const char *second, const char *third);


#endif
