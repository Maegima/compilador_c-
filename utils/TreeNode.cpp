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

#include "TreeNode.hpp"
#include "Scanner.hpp"

extern Scanner *scan;

TreeNode::TreeNode(StmtKind kind){
    int i;
    for (i = 0; i < MAXCHILDREN; i++)
        this->child[i] = NULL;
    this->sibling = NULL;
    this->nodekind = StmtK;
    this->kind.stmt = kind;
    this->lineno = scan->getLineNumber();
    this->type = Void;
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
static void printSpaces(FILE *listing){
    int i;
    for (i = 0; i < indentno; i++)
        fprintf(listing, " ");
}

void TreeNode::print(FILE *listing){
    int i;
    INDENT;
    TreeNode *tree = this;
    while (tree != NULL){
        printSpaces(listing);
        if (tree->nodekind == StmtK){
            switch (tree->kind.stmt){
            case IfK:
                fprintf(listing, "If\n");
                break;
            case WhileK:
                fprintf(listing, "While\n");
                break;
            case AssignK:
                fprintf(listing, "Assign to: %s\n", tree->attr.name->c_str());
                break;
            case ReturnK:
                fprintf(listing, "Return\n");
                break;
            default:
                fprintf(listing, "Unknown ExpNode kind\n");
                break;
            }
        }
        else if (tree->nodekind == ExpK){
            switch (tree->kind.exp){
            case OpK:
                fprintf(listing, "Op: ");
                scan->printToken(listing, tree->attr.op, "\0");
                break;
            case ConstK:
                fprintf(listing, "Const: %d\n", tree->attr.val);
                break;
            case IdK:
                fprintf(listing, "Id: %s\n", tree->attr.name->c_str());
                break;
            case TypeK:
                fprintf(listing, "Type: %s\n", tree->attr.name->c_str());
                break;
            case FuncK:
                fprintf(listing, "Func: %s\n", tree->attr.name->c_str());
                break;
            case DeclK:
                fprintf(listing, "Decl: %s\n", tree->attr.name->c_str());
                break;
            case FuncDeclK:
                fprintf(listing, "FuncDecl: %s\n", tree->attr.name->c_str());
                break;
            case ParamK:
                fprintf(listing, "Param: %s\n", tree->attr.name->c_str());
                break;
            default:
                fprintf(listing, "Unknown ExpNode kind\n");
                break;
            }
        }
        else
            fprintf(listing, "Unknown node kind\n");
        for (i = 0; i < MAXCHILDREN; i++)
            tree->child[i]->print(listing);
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