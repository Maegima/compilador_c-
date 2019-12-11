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

/**************************************************/
/***********   Flags para o rastreamento   ********/
/**************************************************/

/** EchoSource = TRUE causes the source program to
 * be echoed to the listing file with line numbers
 * during parsing.
 */
extern int EchoSource;

/** TraceScan = TRUE causes token information to be
 * printed to the listing file as each token is
 * recognized by the scanner.
 */
extern int TraceScan;

/** TraceParse = TRUE causes the syntax tree to be
 * printed to the listing file in linearized form
 * (using indents for children).
 */
extern int TraceParse;

/** TraceAnalyze = TRUE causes symbol table inserts
 * and lookups to be reported to the listing file.
 */
extern int TraceAnalyze;

/** TraceCode = TRUE causes comments to be written
 * to the TM code file as code is generated.
 */
extern int TraceCode;

/** Error = TRUE prevents further passes if an error occurs. */
extern int Error; 
#endif
