
/**
 * @file analyze.c
 * @author André Lucas Maegima
 * @brief Analizador semântico para a linguagem c-
 * @version 0.1
 * @date 2019-12-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "globals.h"
#include "symtab.h"
#include "analyze.h"

/**
 * @brief Contador para o local das variáveis na memória 
 * 
 */
static int location = 0;

/**
 * @brief Procedimento com sintaxe recursiva 
 * generica para a rotina traverse
 * 
 * @param t Raiz da arvore
 * @param preProc Percurso em pré ordem
 * @param postProc Percurso em pós ordem
 */
static void traverse(TreeNode*t, void(*preProc)(TreeNode*), void(*postProc)(TreeNode*)){ 
    if (t != NULL){ 
        preProc(t);
        int i;
        for (i = 0; i < MAXCHILDREN; i++)
            traverse(t->child[i],preProc,postProc);
        postProc(t);
        traverse(t->sibling,preProc,postProc);
    }
}

/**
 * @brief Procedimento que não faz nada
 * 
 * @param t Raiz da árvore
 */
static void nullProc(TreeNode * t){ }

/**
 * @brief uniteString junta duas strings em uma 
 * separadas por espaço
 * 
 * @param str1 Primeira string 
 * @param str2 Segunda string
 * @return char* Endereço da string resultante
 */
char *uniteString(const char* str1, const char *str2){
    char *scopeName;
    int len1, len2;
    len1 = strlen(str1);
    len2 = strlen(str2);
    scopeName = (char*) malloc(sizeof(char)*(len1+len2+2));
    memcpy(scopeName, str1, len1);
    memcpy(scopeName+len1, " ", 1);
    memcpy(scopeName+len1+1, str2, len2+1);
    return scopeName;
}

/**
 * @brief insertNode insere identificadores armazenados
 * em t na tabela de simbolos
 * 
 * @param t No da árvore
 */
static void insertNode( TreeNode * t){ 
    char *name, *func;
    int n;
    TreeNode *r;
    switch (t->nodekind){ 
        case StmtK:
        switch (t->kind.stmt){ 
            case AssignK:
                r = t->child[0];
                if(r){
                    name = uniteString(r->scope, r->attr.name);
                    if (st_lookup(name) == -1)
                    /* not yet in table, so treat as new definition */
                        st_insert(name,r->attr.name,r->lineno,-1,t->type,r->func,t->atrib,location++);
                    else{
                    /* already in table, so ignore location, 
                        add line number of use only */ 
                        st_insert(name,r->attr.name,r->lineno,-1,t->type,r->func,t->atrib,0);
                        free(name);
                    }
                }
                break;
            case ReturnK:
            case IfK:
            case WhileK:
            default: break;
        }
        break;
        case ExpK:
        switch (t->kind.exp){ 
            case IdK:
                name = uniteString(t->scope, t->attr.name);
                if (st_lookup(name) == -1)
                /* not yet in table, so treat as new definition */
                    st_insert(name,t->attr.name,t->lineno,t->decl_line,t->type,t->func,-1,location++);
                else{
                /* already in table, so ignore location, 
                    add line number of use only */ 
                    st_insert(name,t->attr.name,t->lineno,t->decl_line,t->type,t->func,-1,0);
                    free(name);
                }
            break;
            case ConstK:
            case TypeK:
            case OpK:
            default: break;
        }
        break;
        default: break;
    }
}

/**
 * @brief Função que constroi uma tabela de simbolos
 * percorrendo a árvore sintática em pré ordem
 * 
 * @param syntaxTree Raiz da árvore sintática
 */
void buildSymtab(TreeNode * syntaxTree)
{ 
    char *input = (char*) malloc(sizeof(char)*6);
    char *output = (char*) malloc(sizeof(char)*7);
    char *G_input = (char*) malloc(sizeof(char)*13);
    char *G_output = (char*) malloc(sizeof(char)*14);
    memcpy(input, "input\0", sizeof(char)*6);
    memcpy(output, "output\0", sizeof(char)*7);
    memcpy(G_input, "GLOBAL input\0", sizeof(char)*13);
    memcpy(G_output, "GLOBAL output\0", sizeof(char)*14); 
    st_insert(G_input,input,0,0,Integer,1,-1,location++);
    st_insert(G_output,output,0,0,Void,1,-1,location++);
    traverse(syntaxTree,insertNode,nullProc);
    if (TraceAnalyze)
    { 
        fprintf(symbtab,"\nSymbol table:\n\n");
        printSymTab(symbtab);
    }
}