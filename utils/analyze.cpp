/**
 * @file analyze.cpp
 * @author André Lucas Maegima
 * @brief Analisador semântico para a linguagem C-.
 * @version 1.0
 * @date 2019-12-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "globals.hpp"
#include "analyze.hpp"

using namespace std;

/// @brief Contador para o local das variáveis na memória. 
static int location = 0;

/**
 * @brief Procedimento com sintaxe recursiva 
 * generica para a rotina traverse.
 * 
 * @param t Raiz da árvore.
 * @param table Tabela de simbolos.
 * @param preProc Percurso em pré ordem.
 * @param postProc Percurso em pós ordem.
 */
static void traverse(TreeNode*t, SymbolTable *table, void(*preProc)(TreeNode*, SymbolTable*), void(*postProc)(TreeNode*, SymbolTable*)){ 
    if (t != NULL){ 
        preProc(t, table);
        int i;
        for (i = 0; i < MAXCHILDREN; i++)
            traverse(t->getChild(i), table, preProc, postProc);
        postProc(t, table);
        traverse(t->getSibling(), table, preProc, postProc);
    }
}

/**
 * @brief Procedimento que não faz nada.
 * 
 * @param t Raiz da árvore.
 * @param table Tabela de simbolos.
 */
static void nullProc(TreeNode * t, SymbolTable *table){ }

/**
 * @brief insertNode insere identificadores armazenados
 * em t na tabela de simbolos.
 * 
 * @param t No da árvore.
 * @param table Tabela de simbolos.
 */
static void insertNode(TreeNode *t, SymbolTable *table){ 
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
                    if (table->lookup(name) == -1)
                    /* not yet in table, so treat as new definition */
                        table->insert(name,r->getName(),r->getLineno(),-1,t->getType(),r->getFunc(),t->getAtrib(),location++);
                    else{
                    /* alrady in table, so ignore location, 
                        add line number of use only */ 
                        table->insert(name,r->getName(),r->getLineno(),-1,t->getType(),r->getFunc(),t->getAtrib(),0);
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
                if (table->lookup(name) == -1)
                /* not yet in table, so treat as new definition */
                    table->insert(name,t->getName(),t->getLineno(),t->getDeclLine(),t->getType(),t->getFunc(),-1,location++);
                else{
                /* already in table, so ignore location, 
                    add line number of use only */ 
                    table->insert(name,t->getName(),t->getLineno(),t->getDeclLine(),t->getType(),t->getFunc(),-1,0);
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

SymbolTable *buildSymtab(TreeNode *syntaxTree){ 
    SymbolTable *table = new SymbolTable();
    table->insert(new string("GLOBAL input"), new string("input"), 0, 0, Integer, 1, -1, location++);
    table->insert(new string("GLOBAL output"), new string("output"), 0, 0, Void, 1, -1, location++);
    traverse(syntaxTree, table, insertNode, nullProc);
    if (TraceAnalyze){ 
        fprintf(symbtab, "\nSymbol table:\n\n");
        table->print(symbtab);
    }
    return table;
}