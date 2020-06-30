%{
/**
 * @file Scanner.cpp
 * @author André Lucas Maegima
 * @brief Implementação do analisador léxico.
 * @version 2.0
 * @date 2020-06-30
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include "Parser.hpp"
#include "Scanner.hpp"

extern YYSTYPE yylval;
extern "C" int yylex(void);
extern Scanner *scan;

Scanner::Scanner(FILE *source, FILE *listing, bool trace){
    yyin = source;
    yyout = listing;
    this->line_number = 1;
    this->trace = trace;
    this->listing = listing;
}

TokenType Scanner::getToken(void)
{ 
    TokenType currentToken = 0;
    currentToken = yylex();
    if (this->trace) {
        fprintf(listing,"\t%d: ", this->line_number);
        printToken(this->listing, currentToken, yytext);
    }
    return currentToken;
}

TokenType Scanner::lexicalError(){
    printf("Erro lexico: %s na linha %d.\n", yytext, this->line_number);
    return ERR;
}

void Scanner::printToken(FILE *listing, TokenType token, const char *tokenString){
    switch (token){
    case IF:
    case ELSE:
    case RETURN:
    case WHILE:
    case VOID:
    case INT:
        fprintf(listing,"reserved word: %s\n", tokenString);
        break;
    case ATRIB:
        fprintf(listing, "=\n");
        break;
    case SLT:
        fprintf(listing, "<\n");
        break;
    case SLTE:
        fprintf(listing, "<=\n");
        break;
    case SGT:
        fprintf(listing, ">\n");
        break;
    case SGTE:
        fprintf(listing, "<=\n");
        break;
    case EQUAL:
        fprintf(listing, "=\n");
        break;
    case DIFFERENT:
        fprintf(listing, "!=\n");
        break;
    case OPAREN:
        fprintf(listing, "(\n");
        break;
    case CPAREN:
        fprintf(listing, ")\n");
        break;
    case OBRACT:
        fprintf(listing, "[\n");
        break;
    case CBRACT:
        fprintf(listing, "]\n");
        break;
    case OBRACE:
        fprintf(listing, "{\n");
        break;
    case CBRACE:
        fprintf(listing, "}\n");
        break;
    case OCOM:
        fprintf(listing, "OCOM\n");
        break;
    case CCOM:
        fprintf(listing, "CCOM\n");
        break;
    case SEMICOLON:
        fprintf(listing, ";\n");
        break;
    case COMMA:
        fprintf(listing, ",\n");
        break;
    case ADD:
        fprintf(listing, "+\n");
        break;
    case SUB:
        fprintf(listing, "-\n");
        break;
    case MULT:
        fprintf(listing, "*\n");
        break;
    case DIV:
        fprintf(listing, "/\n");
        break;
    case ENDFILE:
        fprintf(listing, "EOF\n");
        break;
    case NUM:
        fprintf(listing, "NUM, val= %s\n", tokenString);
        break;
    case ID:
        fprintf(listing, "ID, name= %s\n", tokenString);
        break;
    case ERR:
        fprintf(listing, "ERROR: %s\n", tokenString);
        break;
    default: /* should never happen */
        fprintf(listing, "Unknown token: %d\n", token);
    }
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