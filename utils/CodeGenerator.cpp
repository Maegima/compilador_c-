/**
 * @file CodeGenerator.cpp
 * @author André Lucas Maegima
 * @brief Implementação da classe CodeGenerator.
 * @version 1.4
 * @date 2020-06-24
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <sstream>
#include "Parser.hpp"
#include "CodeGenerator.hpp"
#include "VariablesTable.hpp"

using namespace std;

static int cont_lab = 0, cont_while = 0;
static string *types[] = {new string("void"), new string("int")};

static VariablesTable *var_table = new VariablesTable(100);

string CodeGenerator::intToString(int number){
    return to_string(number);
}

void CodeGenerator::genStmt(TreeNode *tree, string **operate){
    TreeNode *p1, *p2, *p3;
    string *op[3] = {NULL, NULL, NULL};
    string label1, label2;
    VariablesTable *local;
    switch (tree->getStmt()){
    case IfK:
        emitComment("-> if");
        p1 = tree->getChild(0);
        p2 = tree->getChild(1);
        p3 = tree->getChild(2);
        /* generate code for test expression */
        label1 = OP::LABEL + this->intToString(cont_lab);
        cont_lab++;
        this->cGen(p1, &op[0]);
        emitQuadruple(OP::IF_NOT, op[0]->c_str(), label1.c_str(), "-");
        var_table->unlockRegister(*op[0]);
        /* recurse on then part */
        this->cGen(p2, &op[1]);
        if(p3){
            label2 = OP::LABEL + this->intToString(cont_lab);
            cont_lab++;
            emitComment("if: jump to end belongs here");
            emitQuadruple(OP::JUMP, label2.c_str(), "-", "-");
        }
        emitQuadruple(OP::LABEL, label1.c_str(), "-", "-");
        if(p3){
            /* recurse on else part */
            this->cGen(p3, &op[1]);
            emitQuadruple(OP::LABEL, label2.c_str(), "-", "-");
        }
        emitComment("<- if");
        break; /* if_k */

    case WhileK:
        emitComment("-> repeat");
        local = var_table;
        var_table = new VariablesTable(local);
        delete local;
        p1 = tree->getChild(0);
        p2 = tree->getChild(1);
        while(p2 && p2->getExp() == TypeK){
            this->ccGen(p2, &op[0]);
            p2 = p2->getSibling();
        }
        emitComment("repeat: jump after body comes back here");
        /* generate code for body */
        label1 = "WBEGIN" + this->intToString(cont_while);
        label2 = "WEND" + this->intToString(cont_while);
        cont_while++;
        emitQuadruple(OP::LABEL, label1.c_str(), "-", "-");
        this->cGen(p1, &op[0]);
        emitQuadruple(OP::IF_NOT, op[0]->c_str(), label2.c_str(), "-");
        var_table->unlockRegister(*op[0]);
        /* generate code for test */
        this->cGen(p2, &op[1]);
        emitQuadruple(OP::JUMP, label1.c_str(), "-", "-");
        emitQuadruple(OP::LABEL, label2.c_str(), "-", "-");
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
            if(var_table->isPointer(*op[2]))
                emitQuadruple(OP::STORE, op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            else
                emitQuadruple(OP::STORE_ADDR, op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            var_table->unlockRegister(*op[0]);
            var_table->unlockRegister(*op[1]);
        }
        else{
            if(var_table->isPointer(*op[1]))
                emitQuadruple(OP::STORE_ADDR, op[0]->c_str(), op[1]->c_str(), "-");
            else
                emitQuadruple(OP::STORE, op[0]->c_str(), op[1]->c_str(), "-");
            var_table->unlockRegister(*op[0]);
            var_table->unloadRegister(*op[1]);
        }
        emitComment("<- assign");
        *operate = op[0];
        break; /* assign_k */
    case ReturnK:
        emitComment("-> return");
        this->cGen(tree->getChild(0), &op[0]);
        emitQuadruple(OP::RETURN, op[0]->c_str(), "-", "-");
        var_table->unlockRegister(*op[0]);
        emitComment("<- return");
    default:
        break;
    }
}

void CodeGenerator::genExp(TreeNode *tree, string **operate){
    TreeNode *p1, *p2, *p;
    string *op[3] = {NULL, NULL, NULL};
    int cont;
    VariablesTable *local;
    switch ((int)tree->getExp()){
    case ConstK:
        emitComment("-> Const");
        *operate = new string(this->intToString(tree->getVal()));
        emitComment("<- Const");
        break; /* ConstK */

    case IdK:
        emitComment("-> Id");
        if (tree->getChild(0) != NULL){
            op[0] = var_table->linkRegister();
            op[1] = NULL;
            op[2] = tree->getName();
            this->cGen(tree->getChild(0), &op[1]);
            if(var_table->isPointer(*op[2]))
                emitQuadruple(OP::LOAD, op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            else
                emitQuadruple(OP::LOAD_ADDR, op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            var_table->unlockRegister(*op[1]);
        }
        else if(!var_table->isLoaded(*tree->getName())){
            op[0] = var_table->linkRegister(*tree->getName());
            op[1] = tree->getName();
            if(var_table->isPointer(*op[1]))
                emitQuadruple(OP::LOAD_ADDR, op[0]->c_str(), op[1]->c_str(), "-");
            else
                emitQuadruple(OP::LOAD, op[0]->c_str(), op[1]->c_str(), "-");
        }
        else{
            op[0] = var_table->linkRegister(*tree->getName());
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
            emitQuadruple(OP::ALLOC_MEM, op[0]->c_str(), op[1]->c_str(), "-");
            var_table->addPointer(*op[0]);
        }
        else{
            emitQuadruple(OP::ALLOC_MEM, op[0]->c_str(), "-", "-");
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
            emitQuadruple(OP::PARAM, op[0]->c_str(), "-", "-");
            var_table->unlockRegister(*op[0]);
            p = p->getSibling();
            cont++;
        }
        op[0] = tree->getName();
        op[1] = new string(this->intToString(cont));
        if(tree->getType()){
            op[2] = var_table->linkRegister();
            emitQuadruple(OP::CALL, op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
        }
        else
            emitQuadruple(OP::CALL, op[0]->c_str(), op[1]->c_str(), "-");
        *operate = op[2];
        delete op[1];
        emitComment("<- Func");
    break; /* FuncK */

    case FuncK | DeclK:
        emitComment("-> FuncDecl");
        local = var_table;
        var_table = new VariablesTable(local);
        op[0] = types[tree->getType()];
        op[1] = tree->getName();
        cont = 0;
        p = tree->getChild(0);
        while (p){
            cont++;
            p = p->getSibling();
        }
        op[2] = new string(this->intToString(cont));
        emitQuadruple(OP::FUNC, op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
        delete op[2];
        op[2] = op[1];
        p = tree->getChild(0);
        while (p){
            this->ccGen(p, &op[1]);
            op[0] = types[p->getType()];
            var_table->removePointer(*op[1]);
            emitQuadruple(OP::ARG, op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            p = p->getSibling();
        }
        this->cGen(tree->getChild(1), &op[1]);
        op[0] = tree->getName();
        emitQuadruple(OP::END, op[0]->c_str(), "-", "-");
        delete var_table;
        var_table = local;
        emitComment("<- FuncDecl");
        break; /* FuncDeclK */


    case OpK:
        emitComment("-> Op");
        p1 = tree->getChild(0);
        p2 = tree->getChild(1);
        op[0] = *operate;
        this->cGen(p1, &op[1]);
        this->cGen(p2, &op[2]);
        if (op[0] == NULL){
            op[0] = var_table->linkRegister();
        }
        switch (tree->getOp()){
        case ADD:
            emitQuadruple(OP::ADD, op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            break;
        case SUB:
            emitQuadruple(OP::SUB, op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            break;
        case MULT:
            emitQuadruple(OP::MULT, op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            break;
        case DIV:
            emitQuadruple(OP::DIV, op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            break;
        case SLT:
            emitQuadruple(OP::SLT, op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            break;
        case SLTE:
            emitQuadruple(OP::SLTE, op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            break;
        case SGT:
            emitQuadruple(OP::SGT, op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            break;
        case SGTE:
            emitQuadruple(OP::SGTE, op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            break;
        case EQUAL:
            emitQuadruple(OP::EQUAL, op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            break;
        case DIFFERENT:
            emitQuadruple(OP::DIFFERENT, op[0]->c_str(), op[1]->c_str(), op[2]->c_str());
            break;
        default:
            emitComment("BUG: Unknown operate");
            break;
        } /* case op */
        *operate = op[0];
        if(op[0]->compare(*op[1]) != 0) var_table->unlockRegister(*op[1]);
        if(op[0]->compare(*op[2]) != 0) var_table->unlockRegister(*op[2]);
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
    Code line = Code(op, first, second, third);
    clist->push(line);
    fprintf(this->code, "(%s, %s, %s, %s)\n", op, first, second, third);
}

CodeGenerator::CodeGenerator(FILE *code, bool trace){ 
    this->code = code;
    this->trace = trace;
    this->clist = new LinkedList<Code>();
}

LinkedList<Code> *CodeGenerator::generate(TreeNode *syntaxTree){
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
    return this->clist;
}