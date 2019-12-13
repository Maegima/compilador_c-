%{
/**
 * @file parser.cpp
 * @author André Lucas Maegima
 * @brief Implementação do analisador sintático.
 * @version 1.0
 * @date 2019-12-10
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <iostream>
using namespace std;

#define YYPARSER /* distinguishes Yacc output from other code files */

#include "utils/globals.hpp"
#include "utils/util.h"
#include "utils/Scanner.hpp"
#include "utils/Parser.hpp"

#define YYSTYPE TreeNode *
static int sc;
static int func_id;
static char **func;
static ExpType *type;
static TreeNode * savedTree; /* raiz da árvore sintática */
static string *str_global;
static string *scope;

int yylex(void);
extern char* yytext;
extern int erro;
void yyerror(const char *msg);

void initParser(){
    sc = 1;
    func = (char**) malloc(sizeof(char)*256);
    type = (ExpType*) malloc(sizeof(ExpType)*256);
    func[0] = (char*) malloc(sizeof(char)*6);
    func[1] = (char*)  malloc(sizeof(char)*7);
    memcpy(func[0], "input\0", sizeof(char)*6);
    memcpy(func[1], "output\0", sizeof(char)*7);
    type[0] = Integer;
    type[1] = Void;
    func_id = 2;
    str_global = new string("GLOBAL");
}
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
programa: declaracao_lista { savedTree = $1; } 
;
declaracao_lista: declaracao_lista declaracao
{ 
    YYSTYPE t = $1;
    if (t != NULL) { 
        while (t->getSibling() != NULL)
            t = t->getSibling();
        t->setSibling($2);
        $$ = $1; 
    }
    else $$ = $2;
}
| declaracao { $$ = $1; }
;
declaracao: var_declaracao { sc = 1; $$ = $1; } | fun_declaracao { sc = 1; $$ = $1; }
;
var_declaracao: tipo_especificador identificador SEMICOLON 
{
    $$ = $1;
    $$->setChild($2, 0);
    $2->setDeclLine($2->getLineno());
    $2->setType($1->getType());
    $2->setDecl(1);
    $1->setDecl(1);
} 
| tipo_especificador identificador OBRACT numero CBRACT SEMICOLON 
{ 
    $$ = $1;
    $$->setChild($2, 0);
    $$->getChild(0)->setChild($4, 0);
    $2->setDeclLine($2->getLineno());
    $2->setType($1->getType());
    $2->setDecl(1);
    $1->setDecl(1);
} 
;
identificador: ID 
{ 
    $$ = new TreeNode(IdK);
    $$->setName(new string(yytext));
    if(sc){
        scope = $$->getName();
        $$->setScope(str_global);
        sc = 0;
    }
    else $$->setScope(scope);
}
;
numero: NUM 
{ 
    $$ = new TreeNode(ConstK);
    $$->setVal(atoi(yytext));
    $$->setType(Integer);
}
;
tipo_especificador: INT 
{ 
    $$ = new TreeNode(TypeK);
    $$->setName(new string("INT"));
    $$->setType(Integer);
} 
| VOID 
{ 
    $$ = new TreeNode(TypeK);
    $$->setName(new string("VOID"));
    $$->setType(Void);
}
;
fun_declaracao: tipo_especificador identificador OPAREN params CPAREN composto_decl
{
    $$ = $1;
    $$->setChild($2, 0);
    $$->getChild(0)->setChild($4, 0);
    $$->getChild(0)->setChild($6, 1);
    $2->setDeclLine($2->getLineno());
    $2->setType($1->getType());
    $2->setFunc(1);
    $2->setDecl(1);
    func[func_id] = copyString($2->getName()->c_str());
    type[func_id] = $2->getType();
    func_id++;
}
;
params: param_lista { $$ = $1; } | VOID { $$ = NULL; }
;
param_lista: param_lista COMMA param
{ 
   YYSTYPE t = $1;
    if (t != NULL) { 
        while (t->getSibling() != NULL)
            t = t->getSibling();
        t->setSibling($3);
        $$ = $1; 
    }
    else $$ = $3;
}
| param { $$ = $1; }
;
param: tipo_especificador identificador 
{  
    $$ = $1;
    $$->setChild($2, 0);
    $2->setDeclLine($2->getLineno());
    $2->setType($1->getType());
    $2->setDecl(1);
    $1->setDecl(1);
} 
| tipo_especificador identificador OBRACT CBRACT
{ 
    $$ = $1;
    $$->setChild($2, 0);
    $2->setDeclLine($2->getLineno());
    $2->setType($1->getType());
    $2->setDecl(1);
    $1->setDecl(1);
}
;
composto_decl: OBRACE local_declaracoes statement_lista CBRACE
{ 
    YYSTYPE t = $2;
    if(t != NULL){
        while(t->getSibling() != NULL)
            t = t->getSibling();
        t->setSibling($3);
        $$ = $2;
    }
    else $$ = $3;
}
;
local_declaracoes: local_declaracoes var_declaracao
{
    YYSTYPE t = $1;
    if(t != NULL){
        while(t->getSibling() != NULL)
            t = t->getSibling();
        t->setSibling($2);
        $$ = $1;
    }
    else $$ = $2;
}
| { $$ = NULL; }
;
statement_lista: statement_lista statement
{
    YYSTYPE t = $1;
    if(t != NULL){
        while(t->getSibling() != NULL)
            t = t->getSibling();
        t->setSibling($2);
        $$ = $1;
    }
    else $$ = $2;
} 
| { $$ = NULL; }
;
statement: expressao_decl { $$ = $1; }
| composto_decl { $$ = $1; }
| selecao_decl { $$ = $1; }
| iteracao_decl { $$ = $1; }
| retorno_decl { $$ = $1; }
;
expressao_decl: expressao SEMICOLON { $$ = $1; }
| SEMICOLON
;
selecao_decl: IF OPAREN expressao CPAREN statement 
{ 
    $$ = new TreeNode(IfK);
    $$->setChild($3, 0);
    $$->setChild($5, 1);
}
| IF OPAREN expressao CPAREN statement ELSE statement
{ 
    $$ = new TreeNode(IfK);
    $$->setChild($3, 0);
    $$->setChild($5, 1);
    $$->setChild($7, 2);
}
;
iteracao_decl: WHILE OPAREN expressao CPAREN statement
{
    $$ = new TreeNode(WhileK);
    $$->setChild($3, 0);
    $$->setChild($5, 1);
}
;
retorno_decl: RETURN SEMICOLON | RETURN expressao SEMICOLON
{
    $$ = new TreeNode(ReturnK);
    $$->setChild($2, 0);
}
;
expressao: var ATRIB expressao
{
    $$ = new TreeNode(AssignK);
    $$->setName($1->getName());
    $$->setAtrib(1);
    $$->setType(($1->getType() == $3->getType()) ? $3->getType() : Void);
    $$->setScope(scope);
    $$->setChild($1, 0);
    $$->setChild($3, 1);
} 
| simples_expressao { $$ = $1; }
;
var: identificador
{ 
    $$ = $1;
    $$->setType(Integer);
} 
| identificador OBRACT expressao CBRACT
{
    $$ = $1;
    $$->setChild($3, 0);
    $$->setType(Integer);
}
;
simples_expressao: soma_expressao relacional soma_expressao 
{
    $$ = $2;
    $$->setChild($1, 0);
    $$->setChild($3, 1);
    $$->setType(($1->getType() == $3->getType()) ? $1->getType() : Void);
}
| soma_expressao { $$ = $1; }
;
relacional: SLTE 
{ 
    $$ = new TreeNode(OpK);
    $$->setOp(SLTE);
} 
| SLT 
{ 
    $$ = new TreeNode(OpK);
    $$->setOp(SLT);
} 
| SGT 
{
    $$ = new TreeNode(OpK);
    $$->setOp(SGT);
} 
| SGTE 
{
    $$ = new TreeNode(OpK); 
    $$->setOp(SGTE);
} 
| EQUAL 
{
    $$ = new TreeNode(OpK);
    $$->setOp(EQUAL);
} 
| DIFFERENT 
{
    $$ = new TreeNode(OpK);
    $$->setOp(DIFFERENT);
} 
;
soma_expressao: soma_expressao soma termo
{
    $$ = $2;
    $$->setChild($1, 0);
    $$->setChild($3, 1);
    $$->setType(($1->getType() == $3->getType()) ? $1->getType() : Void);
} 
| termo { $$ = $1; }
;
soma: ADD
{ 
    $$ = new TreeNode(OpK);
    $$->setOp(ADD); 
} 
| SUB 
{ 
    $$ = new TreeNode(OpK);
    $$->setOp(SUB); 
}
;
termo: termo mult fator
{
    $$ = $2;
    $$->setChild($1, 0);
    $$->setChild($3, 1);
    $$->setType(($1->getType() == $3->getType()) ? $1->getType() : Void);
}  
| fator { $$ = $1; }
;
mult: MULT
{ 
    $$ = new TreeNode(OpK);
    $$->setOp(MULT); 
} 
| DIV
{ 
    $$ = new TreeNode(OpK);
    $$->setOp(DIV); 
} 
;
fator: OPAREN expressao CPAREN { $$ = $2; } 
| var { $$ = $1; } 
| ativacao { $$ = $1; } 
| numero { $$ = $1; }
;
ativacao: identificador OPAREN simples_expressao CPAREN 
{ 
    $$ = $1;
    $$->setChild($3, 0);
    $1->setFunc(1);
    ExpType t = Void;
    for(int i = 0; i < func_id; i++){
        if( strcmp($1->getName()->c_str(), func[i]) == 0 ){
            t = type[i];
            break;
        }
    }
    $$->setType(t);
} 
| identificador OPAREN args CPAREN 
{ 
    $$ = $1;
    $$->setChild($3, 0);
    $1->setFunc(1);
    ExpType t = Void;
    for(int i = 0; i < func_id; i++){
        if( strcmp($1->getName()->c_str(), func[i]) == 0 ){
            t = type[i];
            break;
        }
    }
    $$->setType(t);
}
;
args: arg_lista { $$ = $1; } | { $$ = NULL; }
;
arg_lista: arg_lista COMMA expressao
{
    YYSTYPE t = $1;
    if(t != NULL){
        while(t->getSibling() != NULL)
            t = t->getSibling();
        t->setSibling($3);
        $$ = $1;
    }
    else $$ = $3;
}
| expressao { $$ = $1; }
;
%%

/**
 * @brief O procedimento yyerror imprime na tela 
 * caso ocorra algum erro semântico.
 * 
 * @param msg Mensagem do erro.
 */
void yyerror(const char * msg)
{
  extern char* yytext;
  cout << msg << ": " << yytext << " " << yylval << " " << yychar << " line " << scan->getLineNumber() << endl;
  erro = 1;
}
 
/**
 * @brief A função yylex chama a função getToken do parser
 * para obter o próximo token do arquivo de origem.
 * 
 * @return int Token do arquivo.
 */
int yylex(void){ 
    return scan->getToken(); 
}

TreeNode * parse(void){ 
    scan = new Scanner();
    initParser();
    yyparse();
    return savedTree;
}