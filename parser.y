%{
//GLC para gerar parser para calculadora simples

#include <iostream>
using namespace std;

#define YYPARSER /* distinguishes Yacc output from other code files */

#include "tiny/globals.h"
#include "tiny/util.h"
#include "tiny/scan.h"
#include "tiny/parse.h"

#define YYSTYPE TreeNode *
static char * savedName; /* for use in assignments */
static int savedLineNo;  /* ditto */
static TreeNode * savedTree; /* stores syntax tree for later return */

extern "C" int yylex(void);
extern int getLineCounter();
extern char* yytext;


void yyerror(char *);
%}

%start programa
%token IF ELSE WHILE         
%token INT VOID           
%token RETURN               
%left ADD SUB           
%left MULT DIV           
%token SLT SLTE SGT SGTE EQUAL DIFFERENT     
%token ATRIB                       
%token OPAREN CPAREN
%token OBRACT CBRACT        
%token OBRACE CBRACE        
%token ID NUM         
%token SEMICOLON COMMA
%token OCOM CCOM                              
%token COM           
%token ERR                      

%%
programa:	declaracao_lista { savedTree = $1;} 
;
declaracao_lista: declaracao_lista declaracao
{ 
    YYSTYPE t = $1;
    if (t != NULL) { 
        while (t->sibling != NULL)
            t = t->sibling;
        t->sibling = $2;
        $$ = $1; 
    }
    else $$ = $2;
}
| declaracao { $$ = $1; }
;
declaracao: var_declaracao { $$ = $1; } | fun_declaracao { $$ = $1; }
;
var_declaracao: tipo_especificador ID { savedName = copyString(yytext); } SEMICOLON 
{
    $$ = $1;
    $$->child[0] = newExpNode(IdK); 
    $$->child[0]->attr.name = savedName; 
} 
| tipo_especificador ID { savedName = copyString(yytext); } OBRACT NUM CBRACT SEMICOLON
{
    $$ = $1;
    $$->child[0] = newExpNode(IdK);
    $$->child[0]->attr.name = savedName; 
    $$->child[0]->child[0] = newExpNode(ConstK);
    $$->child[0]->child[0]->attr.val = atoi("10"); 
} 
;
tipo_especificador: INT { $$ = newExpNode(TypeK); } | VOID { $$ = newExpNode(TypeK); }
;
fun_declaracao: tipo_especificador ID OPAREN params CPAREN composto_decl
;
params: param_lista | VOID
;
param_lista: param_lista COMMA param | param
;
param: tipo_especificador ID | tipo_especificador ID OBRACT CBRACT
;
composto_decl: OBRACE local_declaracoes statement_lista  CBRACE
;
local_declaracoes: local_declaracoes var_declaracao |
;
statement_lista: statement_lista statement |
;
statement: expressao_decl | composto_decl | selecao_decl | iteracao_decl | retorno_decl
;
expressao_decl: expressao SEMICOLON | SEMICOLON
;
selecao_decl: IF OPAREN expressao CPAREN statement | ID OPAREN expressao CPAREN statement ELSE statement
;
iteracao_decl: WHILE OPAREN expressao CPAREN statement
;
retorno_decl: RETURN SEMICOLON | RETURN expressao SEMICOLON
;
expressao: var ATRIB expressao | simples_expressao
;
var: ID | ID OBRACT expressao CBRACT
;
simples_expressao: soma_expressao relacional soma_expressao | soma_expressao
;
relacional: SLTE | SLT | SGT | SGTE | EQUAL | DIFFERENT
;
soma_expressao: soma_expressao soma termo | termo
;
soma: ADD | SUB
;
termo: termo mult fator | fator
;
mult: MULT | DIV
;
fator: OPAREN expressao CPAREN | var | ativacao | NUM
;
ativacao: ID OPAREN simples_expressao CPAREN | ID OPAREN args CPAREN
;
args: arg_lista |
;
arg_lista: arg_lista COMMA expressao | expressao
;
%%

void yyerror(char * msg)
{
  extern char* yytext;
  cout << msg << ": " << yytext << " " << yylval << " " << yychar << " line " << getLineCounter() << endl;
}

/* yylex calls getToken to make Yacc/Bison output
 * compatible with ealier versions of the TINY scanner
 */
/*static int yylex(void)
{ return getToken(); }*/

TreeNode * parse(void)
{ yyparse();
  return savedTree;
}