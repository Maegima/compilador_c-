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
#include "symtab.hpp"
#include "analyze.hpp"

using namespace std;

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

/**
 * @brief insertNode insere identificadores armazenados
 * em t na tabela de simbolos.
 * 
 * @param t No da árvore.
 */
static void insertNode(TreeNode *t){ 
    string *name;
    int n;
    TreeNode *r;
    switch (t->getNodekind()){ 
        case StmtK:
        switch (t->getStmt()){ 
            case AssignK:
                r = t->getChild(0);
                if(r){
                    name = new string(*r->getScope() + " " + *r->getName());
                    if (st_lookup(name) == -1)
                    /* not yet in table, so treat as new definition */
                        st_insert(name,r->getName(),r->getLineno(),-1,t->getType(),r->getFunc(),t->getAtrib(),location++);
                    else{
                    /* alrady in table, so ignore location, 
                        add line number of use only */ 
                        st_insert(name,r->getName(),r->getLineno(),-1,t->getType(),r->getFunc(),t->getAtrib(),0);
                        delete name;
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
                name = new string(*t->getScope()  + " " + *t->getName());
                if (st_lookup(name) == -1)
                /* not yet in table, so treat as new definition */
                    st_insert(name,t->getName(),t->getLineno(),t->getDeclLine(),t->getType(),t->getFunc(),-1,location++);
                else{
                /* already in table, so ignore location, 
                    add line number of use only */ 
                    st_insert(name,t->getName(),t->getLineno(),t->getDeclLine(),t->getType(),t->getFunc(),-1,0);
                    delete name;
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
    st_insert(new string("GLOBAL input"), new string("input"), 0, 0, Integer, 1, -1, location++);
    st_insert(new string("GLOBAL output"), new string("output"), 0, 0, Void, 1, -1, location++);
    traverse(syntaxTree, insertNode, nullProc);
    if (TraceAnalyze){ 
        fprintf(symbtab, "\nSymbol table:\n\n");
        printSymTab(symbtab);
    }
}