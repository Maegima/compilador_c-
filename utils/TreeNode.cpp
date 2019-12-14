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
                fprintf(symbtree, "Assign to: %s\n", tree->attr.name->c_str());
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
                scan->printToken(tree->attr.op, "\0");
                break;
            case ConstK:
                fprintf(symbtree, "Const: %d\n", tree->attr.val);
                break;
            case IdK:
                fprintf(symbtree, "Id: %s\n", tree->attr.name->c_str());
                break;
            case TypeK:
                fprintf(symbtree, "Type: %s\n", tree->attr.name->c_str());
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

TreeNode *TreeNode::getChild(int index){
    return this->child[index];
}

void TreeNode::setChild(TreeNode *value, int index){
    this->child[index] = value;
}

TreeNode *TreeNode::getSibling(){
    return this->sibling;
}

void TreeNode::setSibling(TreeNode *Sibling){
    this->sibling = Sibling;
}

int TreeNode::getLineno(){
    return this->lineno;
}

void TreeNode::setLineno(int lineno){
    this->lineno = lineno;
}

int TreeNode::getDeclLine(){
    return this->decl_line;
}

void TreeNode::setDeclLine(int decl_line){
    this->decl_line = decl_line;
}

int TreeNode::getFunc(){
    return this->func;
}

void TreeNode::setFunc(int func){
    this->func = func;
}

int TreeNode::getAtrib(){
    return this->atrib;
}

void TreeNode::setAtrib(int atrib){
    this->atrib = atrib;
}

int TreeNode::getDecl(){
    return this->decl;
}

void TreeNode::setDecl(int decl){
    this->decl = decl;
}

NodeKind TreeNode::getNodekind(){
    return this->nodekind;
}

void TreeNode::setNodekind(NodeKind nodekind){
    this->nodekind = nodekind;
}

std::string *TreeNode::getScope(){
    return this->scope;
}

void TreeNode::setScope(std::string *scope){
    this->scope = scope;
}

StmtKind TreeNode::getStmt(){
    return this->kind.stmt;
}

void TreeNode::setStmt(StmtKind stmt){
    this->kind.stmt = stmt;
}

ExpKind TreeNode::getExp(){
    return this->kind.exp;
}

void TreeNode::setExp(ExpKind exp){
    this->kind.exp = exp;
}

TokenType TreeNode::getOp(){
    return this->attr.op;
}

void TreeNode::setOp(TokenType op){
    this->attr.op = op;
}

int TreeNode::getVal(){
    return this->attr.val;
}

void TreeNode::setVal(int val){
    this->attr.val = val;
}

std::string *TreeNode::getName(){
    return this->attr.name;
}

void TreeNode::setName(std::string *name){
    this->attr.name = name;
}

ExpType TreeNode::getType(){
    return this->type;
}

void TreeNode::setType(ExpType type){
    this->type = type; 
}
