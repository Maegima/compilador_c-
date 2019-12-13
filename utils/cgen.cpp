/**
 * @file cgen.c
 * @author André Lucas Maegima
 * @brief Implementação do gerador de código 
 * intermediário para a linguagem C-.
 * @version 1.0
 * @date 2019-12-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdlib.h>
#include <string.h>
#include "globals.hpp"
#include "symtab.h"
#include "code.h"
#include "util.h"
#include "cgen.hpp"
#include "TreeNode.hpp"

static char number[11]; /**< Utilizado na conversão de número para string. */
static int cont_aux = 0, cont_lab = 0, cont_vet = 0;

/**
 * @brief O procedimento intToString converte um 
 * inteiro em uma string.
 * 
 * @param str Buffer onde o número será armazenado.
 * @param v Número.
 * @param n Tamanho do buffer.
 */
static void intToString(char *str, int v, int n){
    int i, value, cont = 0;
    value = v;
    str[0] = '0';
    str[1] = '\0';
    for (i = 0; i < n; i++){
        if (value == 0)
            break;
        value /= 10;
        cont++;
    }
    for (i = cont - 1; i > -1; i--){
        str[i] = '0' + (v % 10);
        v /= 10;
    }
    if (cont > 0)
        str[cont] = '\0';
}

/**
 * @brief A função strNumber concatena uma string com um número.
 * 
 * @param str String base.
 * @param number Número.
 * @return char* Endereço da nova string.
 */
static char *strNumber(const char *str, int number){
    char num[11];
    char *rt;
    int a, b;
    a = strlen(str);
    intToString(num, number, 10);
    b = strlen(num);
    rt = (char *)malloc(sizeof(char) * (a + b));
    memcpy(rt, str, a * sizeof(char));
    memcpy(rt + a * sizeof(char), num, b * sizeof(char));
    return rt;
}

/**
 * @brief O procedimento cGen gera o código intermediário
 * percorrendo a árvore de forma recursiva.
 * 
 * @param tree Nó da árvore.
 * @param operate Último operando.
 */
static void cGen(TreeNode *tree, char **operate);

/**
 * @brief O procedimento ccGen gera o código intermediário
 * percorrendo a árvore de forma recursiva mas sem fazer
 * chamadas recursivas para seus irmãos.
 * 
 * @param tree Nó da árvore.
 * @param operate Último operando.
 */
static void ccGen(TreeNode *tree, char **operate);

/**
 * @brief O procedimento genStmt gera o código intermediário
 * para um nó de declaração.
 * 
 * @param tree Nó da árvore.
 * @param operate Último operando.
 */
static void genStmt(TreeNode *tree, char **operate){
    TreeNode *p1, *p2, *p3;
    char *op[3] = {NULL, NULL, NULL};
    char *label1, *label2;
    switch (tree->getStmt()){
    case IfK:
        if (TraceCode)
            emitComment("-> if");
        p1 = tree->getChild(0);
        p2 = tree->getChild(1);
        p3 = tree->getChild(2);
        /* generate code for test expression */
        label1 = strNumber("LABEL", cont_lab);
        cont_lab++;
        cGen(p1, &op[0]);
        emitQuadruple("IF_NOT", op[0], label1, "-");
        /* recurse on then part */
        cGen(p2, &op[1]);
        if(p3){
            label2 = strNumber("LABEL", cont_lab);
            cont_lab++;
            emitComment("if: jump to end belongs here");
            emitQuadruple("JUMP", label2, "-", "-");
        }
        emitQuadruple("LABEL", label1, "-", "-");
        if(p3){
            /* recurse on else part */
            cGen(p3, &op[1]);
            emitQuadruple("LABEL", label2, "-", "-");
        }
        if (TraceCode)
            emitComment("<- if");
        break; /* if_k */

    case WhileK:
        if (TraceCode)
            emitComment("-> repeat");
        p1 = tree->getChild(0);
        p2 = tree->getChild(1);
        emitComment("repeat: jump after body comes back here");
        /* generate code for body */
        label1 = strNumber("LABEL", cont_lab);
        cont_lab++;
        label2 = strNumber("LABEL", cont_lab);
        cont_lab++;
        emitQuadruple("LABEL", label1, "-", "-");
        cGen(p1, &op[0]);
        emitQuadruple("IF_NOT", op[0], label2, "-");
        /* generate code for test */
        cGen(p2, &op[1]);
        emitQuadruple("JUMP", label1, "-", "-");
        emitQuadruple("LABEL", label2, "-", "-");
        if (TraceCode)
            emitComment("<- repeat");
        break; /* repeat */

    case AssignK:
        if (TraceCode)
            emitComment("-> assign");
        /* generate code for rhs */
        cGen(tree->getChild(0), &op[0]);
        op[1] = op[0];
        cGen(tree->getChild(1), &op[1]);
        if (strcmp(op[0], op[1]) != 0)
            emitQuadruple("ASSIGN", op[0], op[1], "-");
        if (TraceCode)
            emitComment("<- assign");
        *operate = op[0];
        break; /* assign_k */
    case ReturnK:
        if (TraceCode)
            emitComment("-> return");
        cGen(tree->getChild(0), &op[0]);
        emitQuadruple("JR", op[0], "-", "-");
        if (TraceCode)
            emitComment("<- return");
    default:
        break;
    }
}

/**
 * @brief O procedimento genExp gera o código intermediário
 * para um nó de expressão.
 * 
 * @param tree Nó da árvore.
 * @param operate Último operando.
 */
static void genExp(TreeNode *tree, char **operate){
    TreeNode *p1, *p2;
    char *op[3] = {NULL, NULL, NULL};
    switch (tree->getExp()){
    case ConstK:
        if (TraceCode)
            emitComment("-> Const");
        intToString(number, tree->getVal(), 10);
        *operate = number;
        if (TraceCode)
            emitComment("<- Const");
        break; /* ConstK */

    case IdK:
        if (TraceCode)
            emitComment("-> Id");
        *operate = copyString(tree->getName()->c_str());
        if (tree->getFunc()){
            if (tree->getDecl()){
                op[0] = copyString(tree->getName()->c_str());
                emitQuadruple("LABEL", op[0], "-", "-");
                TreeNode *p = tree->getChild(0);
                while (p){
                    ccGen(p->getChild(0), &op[0]);
                    emitQuadruple("LOAD", op[0], "-", "-");
                    p = p->getSibling();
                }
                cGen(tree->getChild(1), &op[1]);
            }
            else{
                TreeNode *p = tree->getChild(0);
                int cont = 0;
                while (p){
                    ccGen(p, &op[0]);
                    emitQuadruple("PARAM", op[0], "-", "-");
                    p = p->getSibling();
                    cont++;
                }
                intToString(number, cont, 10);
                op[0] = copyString(tree->getName()->c_str());
                op[1] = number;
                emitQuadruple("CALL", op[0], op[1], "-");
            }
        }
        else{
            if (!tree->getDecl()){
                cGen(tree->getChild(0), &op[2]);
                if (tree->getChild(0) != NULL){
                    op[0] = strNumber("VET", cont_vet);
                    op[1] = copyString(tree->getName()->c_str());
                    cont_vet++;
                    emitQuadruple("ADD", op[0], op[1], op[2]);
                    emitQuadruple("LOAD_ADRESS", op[0], op[0], "-");
                    *operate = op[0];
                }
            }
        }
        if (TraceCode)
            emitComment("<- Id");
        break; /* IdK */

    case OpK:
        if (TraceCode)
            emitComment("-> Op");
        p1 = tree->getChild(0);
        p2 = tree->getChild(1);
        op[0] = *operate;
        cGen(p1, &op[1]);
        cGen(p2, &op[2]);
        if (op[0] == NULL){
            op[0] = strNumber("AUX", cont_aux);
            cont_aux++;
        }
        switch (tree->getOp()){
        case ADD:
            emitQuadruple("ADD", op[0], op[1], op[2]);
            break;
        case SUB:
            emitQuadruple("SUB", op[0], op[1], op[2]);
            break;
        case MULT:
            emitQuadruple("MULT", op[0], op[1], op[2]);
            break;
        case DIV:
            emitQuadruple("DIV", op[0], op[1], op[2]);
            break;
        case SLT:
            emitQuadruple("SLT", op[0], op[1], op[2]);
            break;
        case SLTE:
            emitQuadruple("SLTE", op[0], op[1], op[2]);
            break;
        case SGT:
            emitQuadruple("SLT", op[0], op[1], op[2]);
            break;
        case SGTE:
            emitQuadruple("SGTE", op[0], op[1], op[2]);
            break;
        case EQUAL:
            emitQuadruple("EQUAL", op[0], op[1], op[2]);
            break;
        default:
            emitComment("BUG: Unknown operate");
            break;
        } /* case op */
        *operate = op[0];
        if (TraceCode)
            emitComment("<- Op");
        break; /* OpK */
    case TypeK:
        if (TraceCode)
            emitComment("-> type");
        /* generate code for rhs */
        if (tree->getDecl()){
            op[0] = copyString(tree->getChild(0)->getName()->c_str());
            if (tree->getChild(0)->getChild(0)){
                cGen(tree->getChild(0)->getChild(0), &op[1]);
                emitQuadruple("ALOC_MEN", op[0], op[1], "-");
            }
            else{
                emitQuadruple("ALOC_MEN", op[0], "1", "-");
            }
            cGen(tree->getChild(0), &op[1]);
        }
        /* now store value */
        if (TraceCode)
            emitComment("<- type");
        break;
    default:
        break;
    }
}

static void cGen(TreeNode *tree, char **operate){
    if (tree != NULL){
        switch (tree->getNodekind()){
        case StmtK:
            genStmt(tree, operate);
            break;
        case ExpK:
            genExp(tree, operate);
            break;
        default:
            break;
        }
        cGen(tree->getSibling(), operate);
    }
}

static void ccGen(TreeNode *tree, char **operate){
    if (tree != NULL){
        switch (tree->getNodekind()){
        case StmtK:
            genStmt(tree, operate);
            break;
        case ExpK:
            genExp(tree, operate);
            break;
        default:
            break;
        }
    }
}

void codeGen(TreeNode *syntaxTree, const char *codefile){
    char *s = (char *)malloc(strlen(codefile) + 7);
    char *pointer = NULL;
    strcpy(s, "File: ");
    strcat(s, codefile);
    emitComment("TINY Compilation to TM Code");
    emitComment(s);
    /* generate standard prelude */
    emitComment("Standard prelude:");

    emitComment("End of standard prelude.");
    /* generate code for TINY program */
    TreeNode *tr = syntaxTree;
    while (tr != NULL){
        if (tr->getChild(0)->getFunc()){
            cGen(tr->getChild(0), &pointer);
            fprintf(code,"\n");
        }
        else{
            cGen(tr, &pointer);
            fprintf(code,"\n");
        }
        tr = tr->getSibling();
    }
    emitComment("End of execution.");
}