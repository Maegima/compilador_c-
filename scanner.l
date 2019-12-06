%{
#include <stdlib.h>
#include <stdio.h>
#include "parser.tab.h"
#include "tiny/globals.h"
#include "tiny/util.h"
#include "tiny/scan.h"

extern YYSTYPE yylval;
extern int line_counter;

void initScanner(){
    yyin = source;
    yyout = listing;
    line_counter = 1;
}

int FreakShow (){
    printf("Erro lexico: %s na linha %d.\n", yytext, line_counter);
    return ERR;
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