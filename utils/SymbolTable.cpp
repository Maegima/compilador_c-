/**
 * @file SymbolTable.cpp
 * @author André Lucas Maegima
 * @brief Implementação da classe SymbolTable.
 * @version 1.1
 * @date 2020-06-15
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "SymbolTable.hpp"

using namespace std;

/** SHIFT é a potência de dois usada como multiplicador
na função de hash.  */
#define SHIFT 4

SymbolTable::SymbolTable(FILE *listing, bool trace){
    this->table = new BucketList*[SIZE];
    this->trace = trace;
    this->listing = listing;
    this->location = 0;
}

int SymbolTable::hash(const char *key){
    int temp = 0;
    int i = 0;
    while (key[i] != '\0')
    {
        temp = ((temp << SHIFT) + key[i]) % SIZE;
        ++i;
    }
    return temp;
}

void SymbolTable::traverse(TreeNode *t){ 
    if (t != NULL){ 
        this->insertNode(t);
        int i;
        for (i = 0; i < MAXCHILDREN; i++)
            traverse(t->getChild(i));
        traverse(t->getSibling());
    }
}

void SymbolTable::insertNode(TreeNode *t){ 
    TreeNode *r;
    switch (t->getNodekind()){ 
        case StmtK:
        switch (t->getStmt()){ 
            case AssignK:
                r = t->getChild(1);
                if(r)
                    this->insert(t->getName(),t->getScope(),t->getLineno(),(ExpKind)(t->getExp() | AtribK),r->getType());
                break;
            case ReturnK:
            case IfK:
            case WhileK:
            default: break;
        }
        break;
        case ExpK:
            switch((int)t->getExp()){
                case IdK:
                case IdK | DeclK:
                case FuncK:
                case FuncK | DeclK:
                case ParamK | DeclK:
                    this->insert(t->getName(),t->getScope(),t->getLineno(),t->getExp(),t->getType());
                    break;
                default: break;
            }
            break;
        default: break;
    }
}

void SymbolTable::insert(string *name, string *scope, int lineno, ExpKind flags, ExpType type){
    string *idName = new string(*scope  + " " + *name);
    /*if not yet in table, so treat as new definition */
    int loc = (this->lookup(idName) == -1) ? this->location : -1;
    int h = this->hash(idName->c_str());
    BucketList *l = NULL;
    for(BucketList& list : *this->table[h]){
        if(idName->compare(*list.getName()) == 0){
            l = &list;
            break;
        } 
    }
    if (l == NULL){ /* variable not yet in table */
        l = new BucketList(idName, name, loc);
        l->setFunc(flags & FuncK);
        l->setLines(new LineList(lineno, 0));
        if (flags &  DeclK)
            l->setDeclLine(new LineList(lineno, type));
        else
            l->setDeclLine(NULL);
        if (flags & AtribK)
            l->setAtrib(new LineList(lineno, type));
        else
            l->setAtrib(NULL);
        l->setNext(this->table[h]);
        this->table[h] = l;
        this->location++;
    }
    else{ /* found in table, so just add line number */
        LineList *t;
        if(flags & AtribK){
            LineList *p;
            p = new LineList(lineno, type);
            t = l->getAtrib();
            p->setNext(t);
            l->setAtrib(p);
        }
        else if(flags & DeclK){
            LineList *p;
            p = new LineList(lineno, type);
            t = l->getDeclLine();
            p->setNext(t);
            l->setDeclLine(p);
        }
        else{
            LineList *p;
            p = new LineList(lineno, 0);
            t = l->getLines();
            p->setNext(t);
            l->setLines(p);
        }
    }
}

int SymbolTable::lookup(std::string *name){
    int h = this->hash(name->c_str());
    if(this->table[h] == NULL) return -1;
    for(BucketList list : *this->table[h]){
        if(name->compare(*list.getName()) == 0){
            return list.getMemloc();
        }
    }
    return -1;
}

void SymbolTable::print(FILE *listing){
    int i, padding = 2, count;
    for (i = 0; i < SIZE; ++i){
        if (this->table[i] != NULL){
            for(BucketList list : *this->table[i]){
                count = 0;
                LineList *decl = list.getDeclLine();
                for(LineList::iterator l = decl->begin();l != decl->end(); l++) count++;
                padding = (count > padding) ? count : padding;
            }
        }
    }
    fprintf(listing, "Variable Name        Location  Declaration    ");
    for (int j = 2; j < padding; j++)
        fprintf(listing, "         ");
    fprintf(listing, "  Line Numbers\n");
    fprintf(listing, "-------------------  --------  ---------------");
    for (int j = 2; j < padding; j++)
        fprintf(listing, "---------");
    fprintf(listing, "  -------------\n");
    for (i = 0; i < SIZE; ++i){
        if (this->table[i] != NULL){
            for (BucketList list : *this->table[i]){
                fprintf(listing, "%-20s ", list.getName()->c_str());
                fprintf(listing, "%-8d  ", list.getMemloc());
                count = 0;
                for (LineList decl : *list.getDeclLine()){
                    fprintf(listing, "%-4d(%d)|", decl.getLineno(), decl.getType());
                    count++;
                }
                for (int j = count; j < padding; j++){
                    fprintf(listing, "       |");
                }
                fprintf(listing, " ");
                for (LineList line : *list.getLines()){
                    fprintf(listing, "%4d ", line.getLineno());
                }
                fprintf(listing, "\n");
            }
        }
    }
}

BucketList **SymbolTable::getHashTable(){
    return this->table;
}

void SymbolTable::build(TreeNode *syntaxTree){ 
    this->insert(new string("input"), new string("GLOBAL"), 0, (ExpKind)(FuncK | DeclK), Integer);
    this->insert(new string("output"), new string("GLOBAL"), 0, (ExpKind)(FuncK | DeclK), Void);
    traverse(syntaxTree);
    if (this->trace){ 
        fprintf(this->listing, "\nSymbol table:\n\n");
        this->print(this->listing);
    }
}