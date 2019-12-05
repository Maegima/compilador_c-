%{
//GLC para gerar parser para calculadora simples

#include <iostream>
using namespace std;

extern "C" int yylex(void);
extern void abrirArq();
extern void fecharArq();


void yyerror(char *);
%}

%start programa
%token IF            
%token ELSE          
%token INT           
%token RETURN        
%token VOID          
%token WHILE         
%token ADD           
%token SUB           
%token MULT          
%token DIV           
%token SLT           
%token SLTE          
%token SGT           
%token SGTE          
%token EQUAL         
%token DIFFERENT     
%token ATRIB         
%token SEMICOLON     
%token COMMA         
%token OBRACE        
%token CBRACE        
%token OPAREN        
%token CPAREN        
%token OBRACT        
%token CBRACT        
%token OCOM          
%token CCOM          
%token ID            
%token NUM           
%token END           
%token COM           
%token ERR           
%token IGN           

%%
programa:	            declaracao-lista
                    ;
declaracao-lista:       declaracao-lista declaracao
                    |   declaracao
                    ;
declaracao:             var-declaracao
                    ;
fator:	                '('exp')'		{$$ = $2;}
	                |	NUM 			{$$ = $1;}
	                ;
%%

int main(){
  cout << "\nParser em execução...\n";
  abrirArq();
  yyparse();
  fecharArq();
  return 0;
}

void yyerror(char * msg)
{
  extern char* yytext;
  cout << msg << ": " << yytext << yylval << yychar << " " << n << endl;
}

