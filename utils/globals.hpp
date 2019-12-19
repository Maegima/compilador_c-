/**
 * @file globals.h
 * @author André Lucas Maegima
 * @brief Definições de tipos e variáveis globais.
 * @version 1.0
 * @date 2019-12-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "TokenType.hpp"
#include "Scanner.hpp"
#include "Parser.hpp"

/* Yacc/Bison generates internally its own values
 * for the tokens. Other files can access these values
 * by including the tab.h file generated using the
 * Yacc/Bison option -d ("generate header").
 *
 * The YYPARSER flag prevents inclusion of the tab.h
 * into the Yacc/Bison output itself.
 */

#ifndef YYPARSER

/* Nome do header do parser criado pelo bison. */
#include "../parser.h"

/** ENDFILE é definido implicitamente pelo Yacc/Bison,
 * mas não é icluido no arquivo tab.h.
 */
#define ENDFILE 0

#endif

#ifndef FALSE
#define FALSE 0 ///< Definição de FALSE.
#endif

#ifndef TRUE
#define TRUE 1 ///< Definição de TRUE.
#endif


extern FILE* source; /**< Arquivo de origem. */
extern FILE* listing; /**< Arquivo para saída. */
extern FILE* code; /**< Arquivo para saída do código intermediário. */
extern FILE* symbtree; /**< Arquivo para saída da árvore sintática. */
extern FILE *symbtab; /**< Arquivo para saída da tabela de simbolos. */

extern Scanner *scan; /**< Analisador léxico. */

extern Parser *parser; /**< Analisador sintático */

#endif
