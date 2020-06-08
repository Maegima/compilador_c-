/**
 * @file Semantic.cpp
 * @author André Lucas Maegima
 * @brief Implementação da classe Semantic.
 * @version 1.0
 * @date 2020-06-08
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
            for (BucketList list : *hashTable[i]){
                for (LineList decl : *list.getDeclLine()){
                    count++;
                    if (count > 1){
                        fprintf(this->listing, "Erro semantico no escopo ");
                        printScope(list.getName()->c_str());
                        fprintf(this->listing, " na linha %d: declaração inválida de variável %s, já foi declarada previamente.\n",
                                decl.getLineno(), list.getIdName()->c_str());
                        this->error = true;
                    }
                }
                count = 0;
            }
        }
    }
}

void Semantic::notVoidVariable(){
    int i;
    BucketList **hashTable = this->table->getHashTable();
    for (i = 0; i < SIZE; i++){
        if (hashTable[i] != NULL){
            for (BucketList list : *hashTable[i]){
                for (LineList decl : *list.getDeclLine()){
                    if (!list.getFunc() && !decl.getType()){
                        fprintf(this->listing, "Erro semantico no escopo ");
                        printScope(list.getName()->c_str());
                        fprintf(this->listing, " na linha %d: declaração inválida de variável %s, void só pode ser usado para declaração de função.\n",
                                decl.getLineno(), list.getIdName()->c_str());
                        this->error = true;
                    }
                }
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
            for (BucketList list : *hashTable[i]){
                for (LineList line : *list.getLines()){
                    name = new string("GLOBAL " + *list.getIdName());
                    if (!list.getDeclLine() && !list.getFunc()){
                        if (table->lookup(name) == -1){
                            fprintf(this->listing, "Erro semantico no escopo ");
                            printScope(list.getName()->c_str());
                            fprintf(this->listing, " na linha %d: variável %s não declarada.\n",
                                    line.getLineno(), list.getIdName()->c_str());
                            this->error = true;
                        }
                    }
                }
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
            for (BucketList list : *hashTable[i]){
                name = new string("GLOBAL " + *list.getIdName());
                for (LineList line : *list.getLines()){
                    if (list.getFunc() && table->lookup(name) == -1 && name->compare(*list.getName()) != 0){
                        fprintf(this->listing, "Erro semantico no escopo ");
                        printScope(list.getName()->c_str());
                        fprintf(this->listing, " na linha %d: função %s não declarada.\n",
                                line.getLineno(), list.getIdName()->c_str());
                        this->error = true;
                    }
                }
                delete name;
            }
        }
    }
}

void Semantic::mainNotDeclared(){
    int i, error = 1;
    BucketList **hashTable = this->table->getHashTable();
    for (i = 0; i < SIZE; i++){
        if (hashTable[i] != NULL){
            for (BucketList list : *hashTable[i]){
                if (list.getName()->compare("GLOBAL main") == 0 || !error){
                    error = 0;
                    break;
                }
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
            for (BucketList& list : *hashTable[i]){
                name = new string("GLOBAL" + *list.getIdName());
                if (name->compare(*list.getName()) == 0 && list.getFunc()){
                    func[j] = &list;
                    j++;
                }
                else if (!list.getFunc()){
                    var[k] = &list;
                    k++;
                }
                delete name;
            }
        }
    }
    for (i = 0; i < j; i++){
        for (m = 0; m < k; m++){
            if (var[m]->getIdName()->compare(*func[i]->getIdName()) == 0){
                for (LineList decl : *var[m]->getDeclLine()){
                    fprintf(this->listing, "Erro semantico no escopo ");
                    printScope(var[m]->getName()->c_str());
                    fprintf(this->listing, " na linha %d: %s já foi declarada como nome de função.\n",
                            decl.getLineno(), var[m]->getIdName());
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
            for (BucketList list : *hashTable[i]){
                for (LineList atrib : *list.getAtrib()){
                    if (!atrib.getType()){
                        fprintf(this->listing, "Erro semantico no escopo ");
                        printScope(list.getName()->c_str());
                        fprintf(this->listing, " na linha %d: atribuição void em %s.\n",
                                atrib.getLineno(), list.getIdName()->c_str());
                        this->error = true;
                    }
                }
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