/**
 * @file symtab.cpp
 * @author André Lucas Maegima
 * @brief Implementação da tabela de simbolos e 
 * analisador semântico.
 * @version 1.0
 * @date 2019-12-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <iostream>
#include "globals.hpp"
#include "symtab.hpp"
#include "analyze.hpp"
#include "LineList.hpp"
#include "BucketList.hpp"

using namespace std;

/** SIZE é o tamanho da tabela hash. */
#define SIZE 211

/** SHIFT é a potência de dois usada como multiplicador
na função de hash.  */
#define SHIFT 4

/** Variável para indicar erro na análise semântica. */
int erro_ = 0;

/**  @brief Função de hash. */
static int hashString(const char *key){
    int temp = 0;
    int i = 0;
    while (key[i] != '\0')
    {
        temp = ((temp << SHIFT) + key[i]) % SIZE;
        ++i;
    }
    return temp;
}

/** @brief A tabela hash */
static BucketList* hashTable[SIZE];

void st_insert(string *name, string *idName, int lineno, int decl_line, int type, int func, int atrib, int loc){
    int h = hashString(name->c_str());
    BucketList *l = hashTable[h];
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
        l->setNext(hashTable[h]);
        hashTable[h] = l;
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

int st_lookup(string *name){
    int h = hashString(name->c_str());
    BucketList* l = hashTable[h];
    while ((l != NULL) && (name->compare(*l->getName()) != 0))
        l = l->getNext();
    if (l == NULL)
        return -1;
    else
        return l->getMemloc();
}

void printSymTab(FILE *listing){
    int i, padding = 2, count;
    for (i = 0; i < SIZE; ++i){
        if (hashTable[i] != NULL){
            BucketList* l = hashTable[i];
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
        if (hashTable[i] != NULL){
            BucketList* l = hashTable[i];
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
 * @param listing Arquivo de escrita.
 */
static void notUniqueVariable(FILE *listing){
    int i, count = 0;
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
 * @param listing Arquivo de escrita. 
 */
static void notVoidVariable(FILE *listing){
    int i;
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
 * @param listing Arquivo de escrita. 
 */
static void variableNotDeclared(FILE *listing){
    int i;
    string *name;
    for (i = 0; i < SIZE; i++){
        if (hashTable[i] != NULL){
            BucketList* l = hashTable[i];
            while (l != NULL){
                LineList *s = l->getLines();
                while (s != NULL){
                    name = new string("GLOBAL " + *l->getIdName());
                    if (!l->getDeclLine() && !l->getFunc()){
                        if (st_lookup(name) == -1){
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
 * @param listing Arquivo de escrita. 
 */
static void functionNotDeclared(FILE *listing){
    int i;
    string *name;
    for (i = 0; i < SIZE; i++){
        if (hashTable[i] != NULL){
            BucketList* l = hashTable[i];
            while (l != NULL){
                LineList *s = l->getLines();
                name = new string("GLOBAL " + *l->getIdName());
                while (s != NULL){
                    if (l->getFunc() && st_lookup(name) == -1 && name->compare(*l->getName()) != 0){
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
 * @param listing Arquivo de escrita.
 */
static void mainNotDeclared(FILE *listing){
    int i, error = 1;
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
 * @param listing Arquivo de escrita.
 */
static void variableIsFunction(FILE *listing){
    int i, j = 0, k = 0, m;
    string *name;
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
static void voidAtribuition(FILE *listing){
    int i;
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

int semantical(FILE *listing){
    notUniqueVariable(listing);
    notVoidVariable(listing);
    variableNotDeclared(listing);
    functionNotDeclared(listing);
    mainNotDeclared(listing);
    variableIsFunction(listing);
    voidAtribuition(listing);
    return erro_;
}