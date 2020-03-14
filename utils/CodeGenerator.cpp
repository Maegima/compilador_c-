/**
 * @file CodeGenerator.cpp
 * @author André Lucas Maegima
 * @brief Implementação da classe CodeGenerator.
 * @version 1.0
 * @date 2019-12-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "string.h"
#include "Parser.hpp"
#include "CodeGenerator.hpp"

using namespace std;

static char number[11]; /**< Utilizado na conversão de número para string. */
static int cont_aux = 0, cont_lab = 0, cont_vet = 0;

void CodeGenerator::intToString(char *str, int v, int n){
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

char *CodeGenerator::strNumber(const char *str, int number){
    char num[11];
    char *rt;
    int a, b;
    a = strlen(str);
    this->intToString(num, number, 10);
    b = strlen(num);
    rt = (char *)malloc(sizeof(char) * (a + b));
    memcpy(rt, str, a * sizeof(char));
    memcpy(rt + a * sizeof(char), num, b * sizeof(char));
    return rt;
}

void CodeGenerator::genStmt(TreeNode *tree, string **operate){
    TreeNode *p1, *p2, *p3;
    string *op[3] = {NULL, NULL, NULL};
    char *label1, *label2;
    switch (tree->getStmt()){
    case IfK:
        if (this->trace)
            emitComment("-> if");
        p1 = tree->getChild(0);
        p2 = tree->getChild(1);
        p3 = tree->getChild(2);
        /* generate code for test expression */
        label1 = this->strNumber("LABEL", cont_lab);
        cont_lab++;
        this->cGen(p1, &op[0]);
        emitQuadruple("IF_NOT", op[0]->c_str(), label1, "-");
        /* recurse on then part */
        this->cGen(p2, &op[1]);
        if(p3){
            label2 = this->strNumber("LABEL", cont_lab);
            cont_lab++;
            emitComment("if: jump to end belongs here");
            emitQuadruple("JUMP", label2, "-", "-");
        }
        emitQuadruple("LABEL", label1, "-", "-");
        if(p3){
            /* recurse on else part */
            this->cGen(p3, &op[1]);
            emitQuadruple("LABEL", label2, "-", "-");
        }
        if (this->trace)
            emitComment("<- if");
        break; /* if_k */

    case WhileK:
        if (this->trace)
            emitComment("-> repeat");
        p1 = tree->getChild(0);
        p2 = tree->getChild(1);
        emitComment("repeat: jump after body comes back here");
        /* generate code for body */
        label1 = this->strNumber("LABEL", cont_lab);
        cont_lab++;
        label2 = this->strNumber("LABEL", cont_lab);
        cont_lab++;
        emitQuadruple("LABEL", label1, "-", "-");
        this->cGen(p1, &op[0]);
        emitQuadruple("IF_NOT", op[0]->c_str(), label2, "-");
        /* generate code for test */
        this->cGen(p2, &op[1]);
        emitQuadruple("JUMP", label1, "-", "-");
        emitQuadruple("LABEL", label2, "-", "-");
        if (this->trace)
            emitComment("<- repeat");
        break; /* repeat */

    case AssignK:
        if (this->trace)
            emitComment("-> assign");
        /* generate code for rhs */
        this->cGen(tree->getChild(0), &op[0]);
        op[1] = op[0];
        this->cGen(tree->getChild(1), &op[1]);
        if (op[0]->compare(*op[1]) != 0)
            emitQuadruple("ASSIGN", op[0]->c_str(), op[1]->c_str(), "-");
        if (this->trace)
            emitComment("<- assign");
        *operate = op[0];
        break; /* assign_k */
    case ReturnK:
        if (this->trace)
            emitComment("-> return");
        this->cGen(tree->getChild(0), &op[0]);
        emitQuadruple("JR", op[0]->c_str(), "-", "-");
        if (this->trace)
            emitComment("<- return");
    default:
        break;
    }
}

void CodeGenerator::genExp(TreeNode *tree, string **operate){
    TreeNode *p1, *p2, *p;
    string *op[3] = {NULL, NULL, NULL};
    int cont;
    switch (tree->getExp()){
    case ConstK:
        if (this->trace)
            emitComment("-> Const");
        this->intToString(number, tree->getVal(), 10);
        *operate = new string(number);
        if (this->trace)
            emitComment("<- Const");
        break; /* ConstK */

    case IdK:
        if (this->trace)
            emitComment("-> Id");
        if (tree->getChild(0) != NULL){
            this->cGen(tree->getChild(0), &op[2]);
            op[0] = new string(this->strNumber("VET", cont_vet));
            op[1] = tree->getName();
            cont_vet++;
            emitQuadruple("ADD", op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            emitQuadruple("LOAD_ADRESS", op[0]->c_str(), op[0]->c_str(), "-");
            *operate = op[0];
        }
        else
            *operate = tree->getName();
        if (this->trace)
            emitComment("<- Id");
        break; /* IdK */

    case ParamK:
        if (this->trace)
            emitComment("-> Param");
        *operate = tree->getName();;
        if (this->trace)
            emitComment("<- Param");
        break; /* ParamK */

    case DeclK:
        if (this->trace)
            emitComment("-> Decl");
        op[0] = tree->getName();
        if(tree->getChild(0)){
            cGen(tree->getChild(0), &op[1]);
            emitQuadruple("ALOC_MEN", op[0]->c_str(), op[1]->c_str(), "-");
        }
        else{
            emitQuadruple("ALOC_MEN", op[0]->c_str(), "1", "-");
        }
        *operate = op[0];
        if (this->trace)
            emitComment("<- Decl");
        break; /* DeclK */

    case FuncK:
        *operate = tree->getName();
        if (this->trace)
            emitComment("-> Func");
        cont = 0;
        p = tree->getChild(0);
        while (p){
            this->ccGen(p, &op[0]);
            emitQuadruple("PARAM", op[0]->c_str(), "-", "-");
            p = p->getSibling();
            cont++;
        }
        this->intToString(number, cont, 10);
        op[0] = tree->getName();
        op[1] = new string(number);
        emitQuadruple("CALL", op[0]->c_str(), op[1]->c_str(), "-");
        delete op[1];
        if (this->trace)
            emitComment("<- Func");
    break; /* FuncK */

    case FuncDeclK:
        if (this->trace)
            emitComment("-> FuncDecl");
        op[0] = tree->getName();
        emitQuadruple("LABEL", op[0]->c_str(), "-", "-");
        p = tree->getChild(0);
        while (p){
            this->ccGen(p, &op[0]);
            emitQuadruple("LOAD", op[0]->c_str(), "-", "-");
            p = p->getSibling();
        }
        this->cGen(tree->getChild(1), &op[1]);
        if (this->trace)
            emitComment("<- FuncDecl");
        break; /* FuncDeclK */


    case OpK:
        if (this->trace)
            emitComment("-> Op");
        p1 = tree->getChild(0);
        p2 = tree->getChild(1);
        op[0] = *operate;
        this->cGen(p1, &op[1]);
        this->cGen(p2, &op[2]);
        if (op[0] == NULL){
            op[0] = new string(this->strNumber("AUX", cont_aux));
            cont_aux++;
        }
        switch (tree->getOp()){
        case ADD:
            emitQuadruple("ADD", op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            break;
        case SUB:
            emitQuadruple("SUB", op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            break;
        case MULT:
            emitQuadruple("MULT", op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            break;
        case DIV:
            emitQuadruple("DIV", op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            break;
        case SLT:
            emitQuadruple("SLT", op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            break;
        case SLTE:
            emitQuadruple("SLTE", op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            break;
        case SGT:
            emitQuadruple("SLT", op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            break;
        case SGTE:
            emitQuadruple("SGTE", op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            break;
        case EQUAL:
            emitQuadruple("EQUAL", op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            break;
        default:
            emitComment("BUG: Unknown operate");
            break;
        } /* case op */
        *operate = op[0];
        if (this->trace)
            emitComment("<- Op");
        break; /* OpK */
        
    case TypeK:
        if (this->trace)
            emitComment("-> type");
        cGen(tree->getChild(0), operate);
        if (this->trace)
            emitComment("<- type");
        break;
    default:
        break;
    }
}

void CodeGenerator::cGen(TreeNode *tree, string **operate){
    if (tree != NULL){
        switch (tree->getNodekind()){
        case StmtK:
            this->genStmt(tree, operate);
            break;
        case ExpK:
            //printf("dentro do loop\n");
            this->genExp(tree, operate);
            break;
        default:
            break;
        }
        this->cGen(tree->getSibling(), operate);
    }
}

void CodeGenerator::ccGen(TreeNode *tree, string **operate){
    if (tree != NULL){
        switch (tree->getNodekind()){
        case StmtK:
            this->genStmt(tree, operate);
            break;
        case ExpK:
            this->genExp(tree, operate);
            break;
        default:
            break;
        }
    }
}

void CodeGenerator::emitComment(const char *c){
    if (this->trace)
        fprintf(this->code, "* %s\n", c);
}

void CodeGenerator::emitQuadruple(const char *op, const char *first, const char *second, const char *third){
    fprintf(this->code, "(%s, %s, %s, %s)\n", op, first, second, third);
}

CodeGenerator::CodeGenerator(FILE *code, bool trace){ 
    this->code = code;
    this->trace = trace;
}

void CodeGenerator::generate(TreeNode *syntaxTree){
    string *pointer = NULL;
    /* generate standard prelude */
    emitComment("Standard prelude:");

    emitComment("End of standard prelude.");
    /* generate code for TINY program */
    TreeNode *tr = syntaxTree;
    while(tr != NULL){
        this->ccGen(tr, &pointer);
        fprintf(code, "\n");
        tr = tr->getSibling();
    }
    emitComment("End of execution.");
}