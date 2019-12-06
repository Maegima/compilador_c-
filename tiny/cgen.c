/****************************************************/
/* File: cgen.c                                     */
/* The code generator implementation                */
/* for the TINY compiler                            */
/* (generates code for the TM machine)              */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "symtab.h"
#include "code.h"
#include "cgen.h"

char number[11];

void intToString(char *str, int v, int n){
    int i, value, cont = 0;
    value = v;
    str[0] = '\0';
    for(i = 0; i < n; i++){
        if(value == 0) break;
        value /= 10;
        cont++; 
    }
    for(i = cont-1; i > -1; i--){
        str[i] = '0' + (v%10);
        v /= 10;
    }
    str[cont] = '\0';
}

/* prototype for internal recursive code generator */
static void cGen (TreeNode * tree, char operator);

/* Procedure genStmt generates code at a statement node */
static void genStmt( TreeNode * tree, char operator)
{ 
    TreeNode * p1, * p2, * p3;
    int savedLoc1,savedLoc2,currentLoc;
    char *op[3] = {NULL, NULL, NULL};
    switch (tree->kind.stmt) {

        case IfK :
            if (TraceCode) emitComment("-> if") ;
            p1 = tree->child[0] ;
            p2 = tree->child[1] ;
            p3 = tree->child[2] ;
            /* generate code for test expression */
            cGen(p1, operator);
         
            emitComment("if: jump to else belongs here");
         /* recurse on then part */
            cGen(p2, operator);
            emitComment("if: jump to end belongs here");

            emitQuadruple("IF", "_t0", "LABEL1", "-");
            /* recurse on else part */

            emitQuadruple("JUMP", "LABEL0", "-", "-");
            if (TraceCode)  emitComment("<- if") ;
            break; /* if_k */

        case WhileK:
            if (TraceCode) emitComment("-> repeat") ;
            p1 = tree->child[0] ;
            p2 = tree->child[1] ;
            emitComment("repeat: jump after body comes back here");
            /* generate code for body */
            cGen(p1, operator);
            /* generate code for test */
            cGen(p2, operator);
            emitQuadruple("WHILE", "-", "-", "-");
            if (TraceCode)  emitComment("<- repeat") ;
            break; /* repeat */

        case AssignK:
            if (TraceCode) emitComment("-> assign") ;
            /* generate code for rhs */
            cGen(tree->child[0], operator);
            cGen(tree->child[1], operator);
            /* now store value */
            //emitQuadruple("ASSIGN", "-", "-", "-");
            if (TraceCode)  emitComment("<- assign") ;
            break; /* assign_k */
        default:
            break;
    }
} /* genStmt */

/* Procedure genExp generates code at an expression node */
static void genExp(TreeNode * tree, char *operator)
{
  TreeNode * p1, * p2;
  char op[3] = {NULL, NULL, NULL};
  switch (tree->kind.exp) {
    case ConstK :
      if (TraceCode) emitComment("-> Const") ;
      /* gen code to load integer constant using LDC */
      //emitQuadruple("Const", "-", "-", "-");
      //intToString(number, tree->attr.val, 10);
      if (TraceCode)  emitComment("<- Const") ;
      break; /* ConstK */
    
    case IdK :
      if (TraceCode) emitComment("-> Id") ;
      //emitQuadruple(tree->attr.name, "-", "-", "-");
      cGen(tree->child[0], operator);
      cGen(tree->child[1], operator);
      if (TraceCode)  emitComment("<- Id") ;
      break; /* IdK */

    case OpK :
         if (TraceCode) emitComment("-> Op") ;
         p1 = tree->child[0];
         p2 = tree->child[1];
         op[0] = operator;
         cGen(p1, operator);
         cGen(p2, operator);
         switch (tree->attr.op) {
            case ADD : 
               emitQuadruple("ADD", /*op[0]*/NULL, /*op[1]*/NULL, /*op[2]*/NULL);
               break;
            case SUB :
               emitQuadruple("SUB", /*op[0]*/NULL, /*op[1]*/NULL, /*op[2]*/NULL);
               break;
            case MULT :
               emitQuadruple("MULT", /*op[0]*/NULL, /*op[1]*/NULL, /*op[2]*/NULL);
               break;
            case DIV :
               emitQuadruple("DIV", /*op[0]*/NULL, /*op[1]*/NULL, /*op[2]*/NULL);
               break;
            case SLT :
               emitQuadruple("SLT", "-", "-", "-");
               break;
            case EQUAL :
               emitQuadruple("EQUAL", "-", "-", "-");
               break;
            default:
               emitComment("BUG: Unknown operator");
               break;
         } /* case op */
         if (TraceCode)  emitComment("<- Op") ;
         break; /* OpK */
    case TypeK:
          if (TraceCode) emitComment("-> type") ;
         /* generate code for rhs */
         cGen(tree->child[0], operator);
         /* now store value */
         if (TraceCode)  emitComment("<- type") ;
         break;
    default:
      break;
  }
} /* genExp */

/* Procedure cGen recursively generates code by
 * tree traversal
 */
static void cGen(TreeNode * tree, char operator){ 
    if (tree != NULL){ 
        switch (tree->nodekind){
        case StmtK:
            genStmt(tree, operator);
            break;
        case ExpK:
            genExp(tree, operator);
            break;
        default:
            break;
        }
    cGen(tree->sibling, operator);
  }
}

/**********************************************/
/* the primary function of the code generator */
/**********************************************/
/* Procedure codeGen generates code to a code
 * file by traversal of the syntax tree. The
 * second parameter (codefile) is the file name
 * of the code file, and is used to print the
 * file name as a comment in the code file
 */
void codeGen(TreeNode * syntaxTree, char * codefile){  
    char * s = (char*) malloc(strlen(codefile)+7);
    strcpy(s,"File: ");
    strcat(s,codefile);
    emitComment("TINY Compilation to TM Code");
    emitComment(s);
    /* generate standard prelude */
    emitComment("Standard prelude:");

    emitComment("End of standard prelude.");
    /* generate code for TINY program */
    TreeNode *tr = syntaxTree;
    while (tr != NULL){
        if(tr->child[0]->func){
            printf("func\n");
            cGen(tr->child[0], NULL);
        }
        else{
            printf("var\n");
            cGen(tr->child[0], NULL);
        }
        tr = tr->sibling;
    }
    /* finish */
    emitComment("End of execution.");
}
