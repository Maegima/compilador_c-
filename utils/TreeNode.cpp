/**
 * @file TreeNode.cpp
 * @author André Lucas Maegima
 * @brief Implementação da clase árvore sintática.
 * @version 1.0
 * @date 2019-12-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "globals.hpp"
#include "TreeNode.hpp"
#include "util.h"

TreeNode::TreeNode(StmtKind kind){
    int i;
    for (i = 0; i < MAXCHILDREN; i++)
        this->child[i] = NULL;
    this->sibling = NULL;
    this->nodekind = StmtK;
    this->kind.stmt = kind;
    this->lineno = scan->getLineNumber();
    this->type = Void;
    this->decl_line = -1;
    this->func = 0;
    this->atrib = 0;
    this->decl = 0;
}

TreeNode::TreeNode(ExpKind kind){
    int i;
    for (i = 0; i < MAXCHILDREN; i++)
        this->child[i] = NULL;
    this->sibling = NULL;
    this->nodekind = ExpK;
    this->kind.exp = kind;
    this->lineno = scan->getLineNumber();
    this->type = Void;
    this->decl_line = -1;
    this->func = 0;
    this->atrib = 0;
    this->decl = 0;
}

/** A Variável indentno é usada pelo printTree para 
 * guardar o número de espaços para a identação. 
 */
static int indentno = 0;

/** Macro para aumentar a identação. */
#define INDENT indentno += 2
/** Macro para diminuir a identação. */
#define UNINDENT indentno -= 2

/**
 * @brief A função printSpaces identa imprimindo
 * espaços.
 * 
 */
static void printSpaces(void){
    int i;
    for (i = 0; i < indentno; i++)
        fprintf(symbtree, " ");
}

void TreeNode::print(){
    int i;
    INDENT;
    TreeNode *tree = this;
    while (tree != NULL){
        printSpaces();
        if (tree->nodekind == StmtK){
            switch (tree->kind.stmt){
            case IfK:
                fprintf(symbtree, "If\n");
                break;
            case WhileK:
                fprintf(symbtree, "While\n");
                break;
            case AssignK:
                fprintf(symbtree, "Assign to: %s\n", tree->attr.name);
                break;
            case ReturnK:
                fprintf(symbtree, "Return\n");
                break;
            default:
                fprintf(symbtree, "Unknown ExpNode kind\n");
                break;
            }
        }
        else if (tree->nodekind == ExpK){
            switch (tree->kind.exp){
            case OpK:
                fprintf(symbtree, "Op: ");
                printToken(tree->attr.op, "\0");
                break;
            case ConstK:
                fprintf(symbtree, "Const: %d\n", tree->attr.val);
                break;
            case IdK:
                fprintf(symbtree, "Id: %s\n", tree->attr.name);
                break;
            case TypeK:
                fprintf(symbtree, "Type: %s\n", tree->attr.name);
                break;
            default:
                fprintf(symbtree, "Unknown ExpNode kind\n");
                break;
            }
        }
        else
            fprintf(symbtree, "Unknown node kind\n");
        for (i = 0; i < MAXCHILDREN; i++)
            tree->child[i]->print();
        tree = tree->sibling;
    }
    UNINDENT;
}