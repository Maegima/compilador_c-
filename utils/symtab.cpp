/**
 * @file symtab.cpp
 * @author André Lucas Maegima
 * @brief Implementação do analisador semântico.
 * @version 1.0
 * @date 2019-12-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <iostream>
#include "globals.hpp"
#include "symtab.hpp"

using namespace std;

/** Variável para indicar erro na análise semântica. */
int erro_ = 0;

/**
 * @brief Imprime no arquivo o escopo de name.
 * 
 * @param name Id da tabela de simbolo.
 * @param listing Arquivo de escrita.
 */
static void printScope(const char *name, FILE *listing){
    int i = 0;
    while (name[i] != ' '){
        fprintf(listing, "%c", name[i]);
        i++;
    }
}

/**
 * @brief Procura e imprime no arquivo os erros de 
 * não unicidade de declaração.
 * 
 * @param table Tabela de simbolos.
 * @param listing Arquivo de escrita.
 */
static void notUniqueVariable(SymbolTable *table, FILE *listing){
    int i, count = 0;
    BucketList **hashTable = table->getHashTable();
    for (i = 0; i < SIZE; i++){
        if (hashTable[i] != NULL){
            BucketList* l = hashTable[i];
            while (l != NULL){
                LineList *s = l->getDeclLine();
                while (s != NULL){
                    count++;
                    if (count > 1){
                        fprintf(listing, "Erro semantico no escopo ");
                        printScope(l->getName()->c_str(), listing);
                        fprintf(listing, " na linha %d: declaração inválida de variável %s, já foi declarada previamente.\n",
                                s->getLineno(), l->getIdName()->c_str());
                        erro_ = 1;
                    }
                    s = s->getNext();
                }
                count = 0;
                l = l->getNext();
            }
        }
    }
}

/**
 * @brief Procura e imprime no arquivo de escrita os erros
 * de declaração de variável void.
 * 
 * @param table Tabela de simbolos.
 * @param listing Arquivo de escrita. 
 */
static void notVoidVariable(SymbolTable *table, FILE *listing){
    int i;
    BucketList **hashTable = table->getHashTable();
    for (i = 0; i < SIZE; i++){
        if (hashTable[i] != NULL){
            BucketList* l = hashTable[i];
            while (l != NULL){
                LineList *s = l->getDeclLine();
                while (s != NULL){
                    if (!l->getFunc() && !s->getType()){
                        fprintf(listing, "Erro semantico no escopo ");
                        printScope(l->getName()->c_str(), listing);
                        fprintf(listing, " na linha %d: declaração inválida de variável %s, void só pode ser usado para declaração de função.\n",
                                s->getLineno(), l->getIdName()->c_str());
                        erro_ = 1;
                    }
                    s = s->getNext();
                }
                l = l->getNext();
            }
        }
    }
}

/**
 * @brief Procura e imprime no arquivo de escrita os erros
 * de variável não declarada.
 * 
 * @param table Tabela de simbolos.
 * @param listing Arquivo de escrita. 
 */
static void variableNotDeclared(SymbolTable *table, FILE *listing){
    int i;
    string *name;
    BucketList **hashTable = table->getHashTable();
    for (i = 0; i < SIZE; i++){
        if (hashTable[i] != NULL){
            BucketList* l = hashTable[i];
            while (l != NULL){
                LineList *s = l->getLines();
                while (s != NULL){
                    name = new string("GLOBAL " + *l->getIdName());
                    if (!l->getDeclLine() && !l->getFunc()){
                        if (table->lookup(name) == -1){
                            fprintf(listing, "Erro semantico no escopo ");
                            printScope(l->getName()->c_str(), listing);
                            fprintf(listing, " na linha %d: variável %s não declarada.\n",
                                    s->getLineno(), l->getIdName()->c_str());
                            erro_ = 1;
                        }
                    }
                    s = s->getNext();
                }
                l = l->getNext();
            }
        }
    }
}

/**
 * @brief Procura e imprime no arquivo de escrita os erros
 * de função não declarada.
 * 
 * @param table Tabela de simbolos.
 * @param listing Arquivo de escrita. 
 */
static void functionNotDeclared(SymbolTable *table, FILE *listing){
    int i;
    string *name;
    BucketList **hashTable = table->getHashTable();
    for (i = 0; i < SIZE; i++){
        if (hashTable[i] != NULL){
            BucketList* l = hashTable[i];
            while (l != NULL){
                LineList *s = l->getLines();
                name = new string("GLOBAL " + *l->getIdName());
                while (s != NULL){
                    if (l->getFunc() && table->lookup(name) == -1 && name->compare(*l->getName()) != 0){
                        fprintf(listing, "Erro semantico no escopo ");
                        printScope(l->getName()->c_str(), listing);
                        fprintf(listing, " na linha %d: função %s não declarada.\n",
                                s->getLineno(), l->getIdName()->c_str());
                        erro_ = 1;
                    }
                    s = s->getNext();
                }
                delete name;
                l = l->getNext();
            }
        }
    }
}

/**
 * @brief Procura e imprime no arquivo de escrita o erro
 * de main não declarada.
 * 
 * @param table Tabela de simbolos.
 * @param listing Arquivo de escrita.
 */
static void mainNotDeclared(SymbolTable *table, FILE *listing){
    int i, error = 1;
    BucketList **hashTable = table->getHashTable();
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
        fprintf(listing, "Erro semantico: função main() não declarada.\n");
        erro_ = 1;
    }
}

/**
 * @brief Procura e imprime no arquivo de escrita os erros
 * de variável declarada previamente como função.
 * 
 * @param table Tabela de simbolos.
 * @param listing Arquivo de escrita.
 */
static void variableIsFunction(SymbolTable *table, FILE *listing){
    int i, j = 0, k = 0, m;
    string *name;
    BucketList **hashTable = table->getHashTable();
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
                    fprintf(listing, "Erro semantico no escopo ");
                    printScope(var[m]->getName()->c_str(), listing);
                    fprintf(listing, " na linha %d: %s já foi declarada como nome de função.\n",
                            s->getLineno(), var[m]->getIdName());
                    s = s->getNext();
                    erro_ = 1;
                }
            }
        }
    }
}

/**
 * @brief Procura e imprime no arquivo de escrita os erros
 * atribuição void em variável.
 * 
 * @param listing Arquivo para saída. 
 */
static void voidAtribuition(SymbolTable *table, FILE *listing){
    int i;
    BucketList **hashTable = table->getHashTable();
    for (i = 0; i < SIZE; i++){
        if (hashTable[i] != NULL){
            BucketList* l = hashTable[i];
            while (l != NULL){
                LineList *s = l->getAtrib();
                while (s != NULL){
                    if (!s->getType()){
                        fprintf(listing, "Erro semantico no escopo ");
                        printScope(l->getName()->c_str(), listing);
                        fprintf(listing, " na linha %d: atribuição void em %s.\n",
                                s->getLineno(), l->getIdName()->c_str());
                        erro_ = 1;
                    }
                    s = s->getNext();
                }
                l = l->getNext();
            }
        }
    }
}

int semantical(SymbolTable *table, FILE *listing){
    notUniqueVariable(table, listing);
    notVoidVariable(table, listing);
    variableNotDeclared(table, listing);
    functionNotDeclared(table, listing);
    mainNotDeclared(table, listing);
    variableIsFunction(table, listing);
    voidAtribuition(table, listing);
    return erro_;
}