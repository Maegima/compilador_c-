/**
 * @file CodeGenerator.cpp
 * @author André Lucas Maegima
 * @brief Implementação da classe CodeGenerator.
 * @version 1.1
 * @date 2020-06-12
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <sstream>
#include "Parser.hpp"
#include "CodeGenerator.hpp"
#include "RegisterTable.hpp"

using namespace std;

static int cont_lab = 0, aux_reg = 0, tab = 0;
static string *types[] = {new string("void"), new string("int")};

static RegisterTable reg_table = RegisterTable(1000);

string CodeGenerator::intToString(int number){
    return to_string(number);
}

int stractNumber(string *reg){
    stringstream ss = stringstream(*reg);
    int a = -1;
    string str = "";
    char c;
    ss >> c;
    str = c;
    ss >> c;
    str += c;
    if(str.compare("$t") == 0) ss >> a;
    return a;
}


void CodeGenerator::genStmt(TreeNode *tree, string **operate){
    TreeNode *p1, *p2, *p3;
    string *op[3] = {NULL, NULL, NULL};
    string label1, label2;
    switch (tree->getStmt()){
    case IfK:
        emitComment("-> if");
        p1 = tree->getChild(0);
        p2 = tree->getChild(1);
        p3 = tree->getChild(2);
        /* generate code for test expression */
        label1 = "LABEL" + this->intToString(cont_lab);
        cont_lab++;
        this->cGen(p1, &op[0]);
        emitQuadruple("IF_NOT", op[0]->c_str(), label1.c_str(), "-");
        reg_table.remove(stractNumber(op[0]));
        /* recurse on then part */
        this->cGen(p2, &op[1]);
        if(p3){
            label2 = "LABEL" + this->intToString(cont_lab);
            cont_lab++;
            emitComment("if: jump to end belongs here");
            emitQuadruple("JUMP", label2.c_str(), "-", "-");
        }
        emitQuadruple("LABEL", label1.c_str(), "-", "-");
        if(p3){
            /* recurse on else part */
            this->cGen(p3, &op[1]);
            emitQuadruple("LABEL", label2.c_str(), "-", "-");
        }
        emitComment("<- if");
        break; /* if_k */

    case WhileK:
        emitComment("-> repeat");
        p1 = tree->getChild(0);
        p2 = tree->getChild(1);
        emitComment("repeat: jump after body comes back here");
        /* generate code for body */
        label1 = "LABEL" + this->intToString(cont_lab);
        cont_lab++;
        label2 = "LABEL" + this->intToString(cont_lab);
        cont_lab++;
        emitQuadruple("LABEL", label1.c_str(), "-", "-");
        this->cGen(p1, &op[0]);
        emitQuadruple("IF_NOT", op[0]->c_str(), label2.c_str(), "-");
        reg_table.remove(stractNumber(op[0]));
        /* generate code for test */
        this->cGen(p2, &op[1]);
        emitQuadruple("JUMP", label1.c_str(), "-", "-");
        emitQuadruple("LABEL", label2.c_str(), "-", "-");
        emitComment("<- repeat");
        break; /* repeat */

    case AssignK:
        emitComment("-> assign");
        /* generate code for rhs */
        op[1] = tree->getChild(0)->getName();
        this->cGen(tree->getChild(1), &op[0]);
        if(tree->getChild(0)->getChild(0) != NULL){
            op[2] = op[1];
            this->cGen(tree->getChild(0)->getChild(0), &op[1]);
            emitQuadruple("STORE_ADDR", op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            reg_table.remove(stractNumber(op[0]));
            reg_table.remove(stractNumber(op[1]));
        }
        else{
            emitQuadruple("STORE", op[0]->c_str(), op[1]->c_str(), "-");
            reg_table.remove(stractNumber(op[0]));
        }
        emitComment("<- assign");
        *operate = op[0];
        break; /* assign_k */
    case ReturnK:
        emitComment("-> return");
        this->cGen(tree->getChild(0), &op[0]);
        emitQuadruple("RETURN", op[0]->c_str(), "-", "-");
        reg_table.remove(stractNumber(op[0]));
        emitComment("<- return");
    default:
        break;
    }
}

void CodeGenerator::genExp(TreeNode *tree, string **operate){
    TreeNode *p1, *p2, *p;
    string *op[3] = {NULL, NULL, NULL};
    int cont, aux;
    switch ((int)tree->getExp()){
    case ConstK:
        emitComment("-> Const");
        *operate = new string(this->intToString(tree->getVal()));
        emitComment("<- Const");
        break; /* ConstK */

    case IdK:
        emitComment("-> Id");
        if (tree->getChild(0) != NULL){
            aux = reg_table.add("$aux" + intToString(aux_reg));
            aux_reg++;
            op[0] = new string("$t" + intToString(aux));
            op[1] = NULL;
            op[2] = tree->getName();
            this->cGen(tree->getChild(0), &op[1]);
            emitQuadruple("LOAD_ADDR", op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            reg_table.remove(stractNumber(op[1]));
        }
        else{
            aux = reg_table.add(*tree->getName());
            op[0] = new string("$t" + intToString(aux));
            op[1] = tree->getName();
            emitQuadruple("LOAD", op[0]->c_str(), op[1]->c_str(), "-");
        }
        *operate = op[0];
        emitComment("<- Id");
        break; /* IdK */

    case ParamK | DeclK:
        emitComment("-> Param");
        *operate = tree->getName();;
        emitComment("<- Param");
        break; /* ParamK */

    case IdK | DeclK:
        emitComment("-> Decl");
        op[0] = tree->getName();
        op[2] = *operate;
        if(tree->getChild(0)){
            cGen(tree->getChild(0), &op[1]);
            emitQuadruple("ALOC_MEM", op[0]->c_str(), op[1]->c_str(), "-");
        }
        else{
            emitQuadruple("ALOC_MEM", op[0]->c_str(), "1", "-");
        }
        emitComment("<- Decl");
        break; /* DeclK */

    case FuncK:
        *operate = tree->getName();
        emitComment("-> Func");
        cont = 0;
        p = tree->getChild(0);
        while (p){
            op[0] = NULL;
            this->ccGen(p, &op[0]);
            emitQuadruple("PARAM", op[0]->c_str(), "-", "-");
            reg_table.remove(stractNumber(op[0]));
            p = p->getSibling();
            cont++;
        }
        aux = reg_table.add("$aux" + intToString(aux_reg));
        aux_reg++;
        op[0] = tree->getName();
        op[1] = new string(this->intToString(cont));
        op[2] = new string("$t" + intToString(aux));
        emitQuadruple("CALL", op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
        *operate = op[2];
        delete op[1];
        emitComment("<- Func");
    break; /* FuncK */

    case FuncK | DeclK:
        emitComment("-> FuncDecl");
        op[0] = types[tree->getType()];
        op[1] = tree->getName();
        emitQuadruple("FUNC", op[0]->c_str(), op[1]->c_str(), "-");
        op[2] = op[1];
        p = tree->getChild(0);
        while (p){
            this->ccGen(p, &op[1]);
            op[0] = types[p->getType()];
            emitQuadruple("ARG", op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            p = p->getSibling();
        }
        this->cGen(tree->getChild(1), &op[1]);
        op[0] = tree->getName();
        emitQuadruple("END", op[0]->c_str(), "-", "-");
        emitComment("<- FuncDecl");
        break; /* FuncDeclK */


    case OpK:
        emitComment("-> Op");
        p1 = tree->getChild(0);
        p2 = tree->getChild(1);
        op[0] = *operate;
        this->cGen(p1, &op[1]);
        this->cGen(p2, &op[2]);
        aux = -1;
        if (op[0] == NULL){
            aux = reg_table.add("$aux" + intToString(aux_reg));
            aux_reg++;
            op[0] = new string("$t" + intToString(aux));
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
        //if(aux > -1) reg_table.remove(aux);
        if(op[0]->compare(*op[1]) != 0) reg_table.remove(stractNumber(op[1]));
        if(op[0]->compare(*op[2]) != 0) reg_table.remove(stractNumber(op[2]));
        emitComment("<- Op");
        break; /* OpK */
        
    case TypeK:
        emitComment("-> type");
        cGen(tree->getChild(0), operate);
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