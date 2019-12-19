/**
 * @file Semantic.cpp
 * @author André Lucas Maegima
 * @brief Implementação da classe Semantic.
 * @version 1.0
 * @date 2019-12-16
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "Semantic.hpp"

using namespace std;

void Semantic::printScope(const char *name){
    int i = 0;
    while (name[i] != ' '){
        fprintf(this->listing, "%c", name[i]);
        i++;
    }
}

void Semantic::notUniqueVariable(){
    int i, count = 0;
    BucketList **hashTable = this->table->getHashTable();
    for (i = 0; i < SIZE; i++){
        if (hashTable[i] != NULL){
            BucketList* l = hashTable[i];
            while (l != NULL){
                LineList *s = l->getDeclLine();
                while (s != NULL){
                    count++;
                    if (count > 1){
                        fprintf(this->listing, "Erro semantico no escopo ");
                        printScope(l->getName()->c_str());
                        fprintf(this->listing, " na linha %d: declaração inválida de variável %s, já foi declarada previamente.\n",
                                s->getLineno(), l->getIdName()->c_str());
                        this->error = true;
                    }
                    s = s->getNext();
                }
                count = 0;
                l = l->getNext();
            }
        }
    }
}

void Semantic::notVoidVariable(){
    int i;
    BucketList **hashTable = this->table->getHashTable();
    for (i = 0; i < SIZE; i++){
        if (hashTable[i] != NULL){
            BucketList* l = hashTable[i];
            while (l != NULL){
                LineList *s = l->getDeclLine();
                while (s != NULL){
                    if (!l->getFunc() && !s->getType()){
                        fprintf(this->listing, "Erro semantico no escopo ");
                        printScope(l->getName()->c_str());
                        fprintf(this->listing, " na linha %d: declaração inválida de variável %s, void só pode ser usado para declaração de função.\n",
                                s->getLineno(), l->getIdName()->c_str());
                        this->error = true;
                    }
                    s = s->getNext();
                }
                l = l->getNext();
            }
        }
    }
}

void Semantic::variableNotDeclared(){
    int i;
    string *name;
    BucketList **hashTable = this->table->getHashTable();
    for (i = 0; i < SIZE; i++){
        if (hashTable[i] != NULL){
            BucketList* l = hashTable[i];
            while (l != NULL){
                LineList *s = l->getLines();
                while (s != NULL){
                    name = new string("GLOBAL " + *l->getIdName());
                    if (!l->getDeclLine() && !l->getFunc()){
                        if (table->lookup(name) == -1){
                            fprintf(this->listing, "Erro semantico no escopo ");
                            printScope(l->getName()->c_str());
                            fprintf(this->listing, " na linha %d: variável %s não declarada.\n",
                                    s->getLineno(), l->getIdName()->c_str());
                            this->error = true;
                        }
                    }
                    s = s->getNext();
                }
                l = l->getNext();
            }
        }
    }
}

void Semantic::functionNotDeclared(){
    int i;
    string *name;
    BucketList **hashTable = this->table->getHashTable();
    for (i = 0; i < SIZE; i++){
        if (hashTable[i] != NULL){
            BucketList* l = hashTable[i];
            while (l != NULL){
                LineList *s = l->getLines();
                name = new string("GLOBAL " + *l->getIdName());
                while (s != NULL){
                    if (l->getFunc() && table->lookup(name) == -1 && name->compare(*l->getName()) != 0){
                        fprintf(this->listing, "Erro semantico no escopo ");
                        printScope(l->getName()->c_str());
                        fprintf(this->listing, " na linha %d: função %s não declarada.\n",
                                s->getLineno(), l->getIdName()->c_str());
                        this->error = true;
                    }
                    s = s->getNext();
                }
                delete name;
                l = l->getNext();
            }
        }
    }
}

void Semantic::mainNotDeclared(){
    int i, error = 1;
    BucketList **hashTable = this->table->getHashTable();
    for (i = 0; i < SIZE; i++){
        if (hashTable[i] != NULL){
            BucketList* l = hashTable[i];
            while (l != NULL){
                if (l->getName()->compare("GLOBAL main") == 0 || !error){
                    error = 0;
                    break;
                }
                l = l->getNext();
            }
        }
    }
    if (error){
        fprintf(this->listing, "Erro semantico: função main() não declarada.\n");
        this->error = true;
    }
}

void Semantic::variableIsFunction(){
    int i, j = 0, k = 0, m;
    string *name;
    BucketList **hashTable = this->table->getHashTable();
    BucketList* func[2 * SIZE];
    BucketList* var[2 * SIZE];
    for (i = 0; i < SIZE; i++){
        if (hashTable[i] != NULL){
            BucketList* l = hashTable[i];
            while (l != NULL){
                name = new string("GLOBAL" + *l->getIdName());
                if (name->compare(*l->getName()) == 0 && l->getFunc()){
                    func[j] = l;
                    j++;
                }
                else if (!l->getFunc()){
                    var[k] = l;
                    k++;
                }
                delete name;
                l = l->getNext();
            }
        }
    }
    for (i = 0; i < j; i++){
        for (m = 0; m < k; m++){
            if (var[m]->getIdName()->compare(*func[i]->getIdName()) == 0){
                LineList *s = var[m]->getDeclLine();
                while (s){
                    fprintf(this->listing, "Erro semantico no escopo ");
                    printScope(var[m]->getName()->c_str());
                    fprintf(this->listing, " na linha %d: %s já foi declarada como nome de função.\n",
                            s->getLineno(), var[m]->getIdName());
                    s = s->getNext();
                    this->error = true;
                }
            }
        }
    }
}

void Semantic::voidAtribuition(){
    int i;
    BucketList **hashTable = this->table->getHashTable();
    for (i = 0; i < SIZE; i++){
        if (hashTable[i] != NULL){
            BucketList* l = hashTable[i];
            while (l != NULL){
                LineList *s = l->getAtrib();
                while (s != NULL){
                    if (!s->getType()){
                        fprintf(this->listing, "Erro semantico no escopo ");
                        printScope(l->getName()->c_str());
                        fprintf(this->listing, " na linha %d: atribuição void em %s.\n",
                                s->getLineno(), l->getIdName()->c_str());
                        this->error = true;
                    }
                    s = s->getNext();
                }
                l = l->getNext();
            }
        }
    }
}

Semantic::Semantic(SymbolTable *table, FILE *listing){
    this->table = table;
    this->listing = listing;
}

bool Semantic::analyze(){
    this->notUniqueVariable();
    this->notVoidVariable();
    this->variableNotDeclared();
    this->functionNotDeclared();
    this->mainNotDeclared();
    this->variableIsFunction();
    this->voidAtribuition();
    return this->error;
}