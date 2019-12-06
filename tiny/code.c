/****************************************************/
/* File: code.c                                     */
/* TM Code emitting utilities                       */
/* implementation for the TINY compiler             */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "code.h"

/* Procedure emitComment prints a comment line 
 * with comment c in the code file
 */
void emitComment( char * c )
{ if (TraceCode) fprintf(code,"* %s\n",c);}

/* Procedure emit emit Quadruple prints a 
 * quadruple.
 */
void emitQuadruple(char *op, char *first, char *second, char *third){
    fprintf(code,"(%s, %s, %s, %s)\n", op, first, second, third);
}