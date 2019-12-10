%{
/**
 * @file scanner.cpp
 * @author André Lucas Maegima
 * @brief Implementação do analisador léxico.
 * @version 0.1
 * @date 2019-12-10
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "utils/globals.h"
#include "utils/util.h"
#include "utils/scan.h"

extern YYSTYPE yylval;
extern int line_counter;

void initScanner(){
    yyin = source;
    yyout = listing;
    line_counter = 1;
}

/**
 * @brief A função FreakShow imprime uma mensagem
 * na tela caso ocorra algum erro léxico.
 * 
 * @return ERR Retorna o token de erro.
 */
int FreakShow(){
    printf("Erro lexico: %s na linha %d.\n", yytext, line_counter);
    return ERR;
}

extern "C" int yylex(void);

TokenType getToken(void)
{ 
    TokenType currentToken = 0;
    currentToken = yylex();
    if (TraceScan) {
        fprintf(listing,"\t%d: ",line_counter);
        printToken(currentToken,yytext);
    }
    return currentToken;
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
\n                                    line_counter++;
"/*"                                  {
                                        char c;
                                        int state = 0;
                                        do{ 
                                            c = yyinput();
                                            switch(c){
                                                case '\n': line_counter++; break;
                                                case '*':  state = 1;      break;
                                                case '/':  state++;        break;
                                                default:   state = 0;
                                            }
                                        }while(state < 2 && c != 0);
                                      }
\r
\t
[ ]+
{DIGIT}+({LETTER}|{DIGIT}|{OTHER})*   return FreakShow();
{LETTER}+({LETTER}|{DIGIT}|{OTHER})*  return FreakShow();
{OTHER}+({LETTER}|{DIGIT})*{OTHER}*   return FreakShow();
%%