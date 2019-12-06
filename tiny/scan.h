/****************************************************/
/* File: scan.h                                     */
/* The scanner interface for the TINY compiler      */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _SCAN_H_
#define _SCAN_H_

#include "globals.h"

/* function getToken returns the 
 * next token in source file
 */
TokenType getToken(void);

/* function initScanner initialize
 * scanner variables
 */
void initScanner();

#endif
