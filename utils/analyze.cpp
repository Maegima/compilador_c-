/**
 * @file analyze.c
 * @author André Lucas Maegima
 * @brief Analisador semântico para a linguagem C-.
 * @version 1.0
 * @date 2019-12-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "globals.hpp"
#include "symtab.h"
#include "analyze.hpp"

/// @brief Contador para o local das variáveis na memória. 
static int location = 0;

/**
 * @brief Procedimento com sintaxe recursiva 
 * generica para a rotina traverse.
 * 
 * @param t Raiz da árvore.
 * @param preProc Percurso em pré ordem.
 * @param postProc Percurso em pós ordem.
 */
static void traverse(TreeNode*t, void(*preProc)(TreeNode*), void(*postProc)(TreeNode*)){ 
    if (t != NULL){ 
        preProc(t);
        int i;
        for (i = 0; i < MAXCHILDREN; i++)
            traverse(t->getChild(i), preProc, postProc);
        postProc(t);
        traverse(t->getSibling(), preProc, postProc);
    }
}

/**
 * @brief Procedimento que não faz nada.
 * 
 * @param t Raiz da árvore.
 */
static void nullProc(TreeNode * t){ }

char *uniteStrings(const char* str1, const char *str2){
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
 * em t na tabela de simbolos.
 * 
 * @param t No da árvore.
 */
static void insertNode( TreeNode * t){ 
    char *name, *func;
    int n;
    TreeNode *r;
    switch (t->getNodekind()){ 
        case StmtK:
        switch (t->getStmt()){ 
            case AssignK:
                r = t->getChild(0);
                if(r){
                    name = uniteStrings(r->getScope()->c_str(), r->getName()->c_str());
                    if (st_lookup(name) == -1)
                    /* not yet in table, so treat as new definition */
                        st_insert(name,r->getName()->c_str(),r->getLineno(),-1,t->getType(),r->getFunc(),t->getAtrib(),location++);
                    else{
                    /* alrady in table, so ignore location, 
                        add line number of use only */ 
                        st_insert(name,r->getName()->c_str(),r->getLineno(),-1,t->getType(),r->getFunc(),t->getAtrib(),0);
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
        switch (t->getExp()){ 
            case IdK:
                name = uniteStrings(t->getScope()->c_str(), t->getName()->c_str());
                if (st_lookup(name) == -1)
                /* not yet in table, so treat as new definition */
                    st_insert(name,t->getName()->c_str(),t->getLineno(),t->getDeclLine(),t->getType(),t->getFunc(),-1,location++);
                else{
                /* already in table, so ignore location, 
                    add line number of use only */ 
                    st_insert(name,t->getName()->c_str(),t->getLineno(),t->getDeclLine(),t->getType(),t->getFunc(),-1,0);
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

void buildSymtab(TreeNode * syntaxTree){ 
    char *input = (char*) malloc(sizeof(char)*6);
    char *output = (char*) malloc(sizeof(char)*7);
    char *G_input = (char*) malloc(sizeof(char)*13);
    char *G_output = (char*) malloc(sizeof(char)*14);
    memcpy(input, "input\0", sizeof(char)*6);
    memcpy(output, "output\0", sizeof(char)*7);
    memcpy(G_input, "GLOBAL input\0", sizeof(char)*13);
    memcpy(G_output, "GLOBAL output\0", sizeof(char)*14); 
    st_insert(G_input, input, 0, 0, Integer, 1, -1, location++);
    st_insert(G_output, output, 0, 0, Void, 1, -1, location++);
    traverse(syntaxTree, insertNode, nullProc);
    if (TraceAnalyze){ 
        fprintf(symbtab, "\nSymbol table:\n\n");
        printSymTab(symbtab);
    }
}