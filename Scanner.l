%{
/**
 * @file Scanner.cpp
 * @author André Lucas Maegima
 * @brief Implementação do analisador léxico.
 * @version 1.0
 * @date 2019-12-10
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "utils/globals.hpp"
#include "utils/util.h"
#include "utils/Scanner.hpp"

extern YYSTYPE yylval;
extern "C" int yylex(void);

Scanner::Scanner(){
    yyin = source;
    yyout = listing;
    this->line_number = 1;
}

TokenType Scanner::getToken(void)
{ 
    TokenType currentToken = 0;
    currentToken = yylex();
    if (TraceScan) {
        fprintf(listing,"\t%d: ", this->line_number);
        printToken(currentToken, yytext);
    }
    return currentToken;
}

TokenType Scanner::lexicalError(){
    printf("Erro lexico: %s na linha %d.\n", yytext, this->line_number);
    return ERR;
}

int Scanner::getLineNumber(){
    return this->line_number;
}

void Scanner::incrementLine(){
    this->line_number++;
}
%}

DIGIT [0-9]
LETTER [a-zA-Z]
OTHER [^0-9a-zA-Z;"+""*"/\"<>=,"{""}""("")"\-\[\]\n\t\r ]
%%
if                                    return IF;
else                                  return ELSE;
int                                   return INT;
return                                return RETURN;
void                                  return VOID;
while                                 return WHILE;
{LETTER}+                             return ID;
{DIGIT}+                              return NUM;
"+"                                   return ADD;
-                                     return SUB;
"*"                                   return MULT;
"/"                                   return DIV;
"<"                                   return SLT;
"<="                                  return SLTE;
">"                                   return SGT;
">="                                  return SGTE;
==                                    return EQUAL;
!=                                    return DIFFERENT;
=                                     return ATRIB;
;                                     return SEMICOLON;
,                                     return COMMA;
"{"                                   return OBRACE;
"}"                                   return CBRACE;
"("                                   return OPAREN;
")"                                   return CPAREN;
"["                                   return OBRACT;
"]"                                   return CBRACT;
\n                                    scan->incrementLine();
"/*"                                  {
                                        char c;
                                        int state = 0;
                                        do{ 
                                            c = yyinput();
                                            switch(c){
                                                case '\n': scan->incrementLine(); break;
                                                case '*':  state = 1;             break;
                                                case '/':  state++;               break;
                                                default:   state = 0;
                                            }
                                        }while(state < 2 && c != 0);
                                      }
\r
\t
[ ]+
{DIGIT}+({LETTER}|{DIGIT}|{OTHER})*   return scan->lexicalError();
{LETTER}+({LETTER}|{DIGIT}|{OTHER})*  return scan->lexicalError();
{OTHER}+({LETTER}|{DIGIT})*{OTHER}*   return scan->lexicalError();
%%