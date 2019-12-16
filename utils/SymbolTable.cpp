/**
 * @file SymbolTable.cpp
 * @author André Lucas Maegima
 * @brief Implementação da classe SymbolTable.
 * @version 1.0
 * @date 2019-12-15
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "SymbolTable.hpp"

using namespace std;

/** SHIFT é a potência de dois usada como multiplicador
na função de hash.  */
#define SHIFT 4

SymbolTable::SymbolTable(){
    this->table = new BucketList*[SIZE];
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

void SymbolTable::insert(string *name, string *idName, int lineno, int decl_line, int type, int func, int atrib, int loc){
    int h = this->hash(name->c_str());
    BucketList *l = this->table[h];
    while ((l != NULL) && (name->compare(*l->getName()) != 0))
        l = l->getNext();
    if (l == NULL){ /* variable not yet in table */
        l = new BucketList(name, idName, loc);
        l->setFunc(func);
        l->setLines(new LineList(lineno, 0));
        if (decl_line > -1)
            l->setDeclLine(new LineList(decl_line, type));
        else
            l->setDeclLine(NULL);
        if (atrib > -1)
            l->setAtrib(new LineList(lineno, type));
        else
            l->setAtrib(NULL);
        l->setNext(this->table[h]);
        this->table[h] = l;
    }
    else{ /* found in table, so just add line number */
        LineList *t;
        if(atrib > -1){
            LineList *p;
            p = new LineList(lineno, type);
            t = l->getAtrib();
            if (t != NULL){
                while (t->getNext() != NULL)
                    t = t->getNext();
                t->setNext(p);
            }
            else
                l->setAtrib(p);
        }
        else if(decl_line > -1){
            LineList *p;
            p = new LineList(decl_line, type);
            t = l->getDeclLine();
            if (t != NULL){
                while (t->getNext() != NULL)
                    t = t->getNext();
                t->setNext(p);
            }
            else
                l->setDeclLine(p);
        }
        else{
            LineList *p;
            p = new LineList(lineno, 0);
            t = l->getLines();
            if (t != NULL){
                while (t->getNext() != NULL)
                    t = t->getNext();
                t->setNext(p);
            }
            else
                l->setLines(p);
        }
    }
}

int SymbolTable::lookup(std::string *name){
    int h = this->hash(name->c_str());
    BucketList* l = this->table[h];
    while ((l != NULL) && (name->compare(*l->getName()) != 0))
        l = l->getNext();
    if (l == NULL)
        return -1;
    else
        return l->getMemloc();
}

void SymbolTable::print(FILE *listing){
    int i, padding = 2, count;
    for (i = 0; i < SIZE; ++i){
        if (this->table[i] != NULL){
            BucketList* l = this->table[i];
            while (l != NULL){
                count = 0;
                LineList *s = l->getDeclLine();
                while (s != NULL){
                    count++;
                    s = s->getNext();
                }
                padding = (count > padding) ? count : padding;
                l = l->getNext();
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
            BucketList* l = this->table[i];
            while (l != NULL){
                LineList *t = l->getLines();
                LineList *r = l->getDeclLine();
                fprintf(listing, "%-20s ", l->getName()->c_str());
                fprintf(listing, "%-8d  ", l->getMemloc());
                for (int j = 0; j < padding; j++){
                    if (r != NULL){
                        fprintf(listing, "%-4d(%d)|", r->getLineno(), r->getType());
                        r = r->getNext();
                    }
                    else{
                        fprintf(listing, "       |");
                    }
                }
                fprintf(listing, " ");
                while (t != NULL){
                    fprintf(listing, "%4d ", t->getLineno());
                    t = t->getNext();
                }
                fprintf(listing, "\n");
                l = l->getNext();
            }
        }
    }
}

BucketList **SymbolTable::getHashTable(){
    return this->table;
}