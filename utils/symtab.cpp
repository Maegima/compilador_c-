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

/** @brief Lista encadeada de linhas. */
typedef struct LineListRec{
    int lineno; /**< @brief Número da linha. */
    int type; /**< @brief Tipo. */
    struct LineListRec *next; /**< @brief Próxima linha. */
} * LineList;

/**
 * @brief Armazena os dados de uma
 * entrada na tabela de símbolos. 
 * 
 */
typedef struct BucketListRec{
    string *name; /**< @brief Nome do identificador. */
    string *idName; /**< @brief Nome do escopo do identificador. */
    int func; /**< @brief Se o identificador é uma função. */
    LineList lines; /**< @brief Linhas onde o identificador aparece. */
    LineList atrib; /**< @brief Linhas de atribuição ao identificador. */
    LineList decl_line; /**< @brief Linhas de declaração do identificador. */
    int memloc; /**< @brief Localização na memória. */
    struct BucketListRec *next; /**< @brief Próximo item. */
} *BucketList;

/** @brief A tabela hash */
static BucketList hashTable[SIZE];

void st_insert(string *name, string *idName, int lineno, int decl_line, int type, int func, int atrib, int loc){
    int h = hashString(name->c_str());
    BucketList l = hashTable[h];
    while ((l != NULL) && (name->compare(*l->name) != 0))
        l = l->next;
    if (l == NULL){ /* variable not yet in table */
        l = (BucketList)malloc(sizeof(struct BucketListRec));
        l->name = name;
        l->idName = idName;
        l->func = func;
        l->lines = (LineList)malloc(sizeof(struct LineListRec));
        l->lines->lineno = lineno;
        l->memloc = loc;
        l->lines->next = NULL;
        if (decl_line > -1){
            l->decl_line = (LineList)malloc(sizeof(struct LineListRec));
            l->decl_line->lineno = decl_line;
            l->decl_line->type = type;
            l->decl_line->next = NULL;
        }
        else
            l->decl_line = NULL;
        if (atrib > -1){
            l->atrib = (LineList)malloc(sizeof(struct LineListRec));
            l->atrib->lineno = lineno;
            l->atrib->type = type;
            l->atrib->next = NULL;
        }
        else
            l->atrib = NULL;

        l->next = hashTable[h];
        hashTable[h] = l;
    }
    else{ /* found in table, so just add line number */
        LineList t;
        if (atrib > -1){
            LineList p;
            p = (LineList)malloc(sizeof(struct LineListRec));
            p->lineno = lineno;
            p->type = type;
            p->next = NULL;
            t = l->atrib;
            if (t != NULL){
                while (t->next != NULL)
                    t = t->next;
                t->next = p;
            }
            else
                l->atrib = p;
        }
        else{
            LineList p;
            p = (LineList)malloc(sizeof(struct LineListRec));
            p->lineno = lineno;
            p->next = NULL;
            t = l->lines;
            if (t != NULL){
                while (t->next != NULL)
                    t = t->next;
                t->next = p;
            }
            else
                l->lines = p;
        }
        if (decl_line > -1){
            LineList p;
            p = (LineList)malloc(sizeof(struct LineListRec));
            p->lineno = decl_line;
            p->type = type;
            p->next = NULL;
            t = l->decl_line;
            if (t != NULL){
                while (t->next != NULL)
                    t = t->next;
                t->next = p;
            }
            else
                l->decl_line = p;
        }
    }
}

int st_lookup(string *name){
    int h = hashString(name->c_str());
    BucketList l = hashTable[h];
    while ((l != NULL) && (name->compare(*l->name) != 0))
        l = l->next;
    if (l == NULL)
        return -1;
    else
        return l->memloc;
}

void printSymTab(FILE *listing){
    int i, padding = 2, count;
    for (i = 0; i < SIZE; ++i){
        if (hashTable[i] != NULL){
            BucketList l = hashTable[i];
            while (l != NULL){
                count = 0;
                LineList s = l->decl_line;
                while (s != NULL){
                    count++;
                    s = s->next;
                }
                padding = (count > padding) ? count : padding;
                l = l->next;
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
            BucketList l = hashTable[i];
            while (l != NULL){
                LineList t = l->lines;
                LineList r = l->decl_line;
                fprintf(listing, "%-20s ", l->name->c_str());
                fprintf(listing, "%-8d  ", l->memloc);
                for (int j = 0; j < padding; j++){
                    if (r != NULL){
                        fprintf(listing, "%-4d(%d)|", r->lineno, r->type);
                        r = r->next;
                    }
                    else{
                        fprintf(listing, "       |");
                    }
                }
                fprintf(listing, " ");
                while (t != NULL){
                    fprintf(listing, "%4d ", t->lineno);
                    t = t->next;
                }
                fprintf(listing, "\n");
                l = l->next;
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
            BucketList l = hashTable[i];
            while (l != NULL){
                LineList s = l->decl_line;
                while (s != NULL){
                    count++;
                    if (count > 1){
                        fprintf(listing, "Erro semantico no escopo ");
                        printScope(l->name->c_str(), listing);
                        fprintf(listing, " na linha %d: declaração inválida de variável %s, já foi declarada previamente.\n",
                                s->lineno, l->idName->c_str());
                        erro_ = 1;
                    }
                    s = s->next;
                }
                count = 0;
                l = l->next;
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
            BucketList l = hashTable[i];
            while (l != NULL){
                LineList s = l->decl_line;
                while (s != NULL){
                    if (!l->func && !s->type){
                        fprintf(listing, "Erro semantico no escopo ");
                        printScope(l->name->c_str(), listing);
                        fprintf(listing, " na linha %d: declaração inválida de variável %s, void só pode ser usado para declaração de função.\n",
                                s->lineno, l->idName->c_str());
                        erro_ = 1;
                    }
                    s = s->next;
                }
                l = l->next;
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
            BucketList l = hashTable[i];
            while (l != NULL){
                LineList s = l->lines;
                while (s != NULL){
                    name = new string("GLOBAL " + *l->idName);
                    if (!l->decl_line && !l->func){
                        if (st_lookup(name) == -1){
                            fprintf(listing, "Erro semantico no escopo ");
                            printScope(l->name->c_str(), listing);
                            fprintf(listing, " na linha %d: variável %s não declarada.\n",
                                    s->lineno, l->idName->c_str());
                            erro_ = 1;
                        }
                    }
                    s = s->next;
                }
                l = l->next;
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
            BucketList l = hashTable[i];
            while (l != NULL){
                LineList s = l->lines;
                name = new string("GLOBAL " + *l->idName);
                while (s != NULL){
                    if (l->func && st_lookup(name) == -1 && name->compare(*l->name) != 0){
                        fprintf(listing, "Erro semantico no escopo ");
                        printScope(l->name->c_str(), listing);
                        fprintf(listing, " na linha %d: função %s não declarada.\n",
                                s->lineno, l->idName->c_str());
                        erro_ = 1;
                    }
                    s = s->next;
                }
                delete name;
                l = l->next;
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
            BucketList l = hashTable[i];
            while (l != NULL){
                if (l->name->compare("GLOBAL main") == 0 || !error){
                    error = 0;
                    break;
                }
                l = l->next;
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
    BucketList func[2 * SIZE];
    BucketList var[2 * SIZE];
    for (i = 0; i < SIZE; i++){
        if (hashTable[i] != NULL){
            BucketList l = hashTable[i];
            while (l != NULL){
                name = new string("GLOBAL" + *l->idName);
                if (name->compare(*l->name) == 0 && l->func){
                    func[j] = l;
                    j++;
                }
                else if (!l->func){
                    var[k] = l;
                    k++;
                }
                delete name;
                l = l->next;
            }
        }
    }
    for (i = 0; i < j; i++){
        for (m = 0; m < k; m++){
            if (var[m]->idName->compare(*func[i]->idName) == 0){
                LineList s = var[m]->decl_line;
                while (s){
                    fprintf(listing, "Erro semantico no escopo ");
                    printScope(var[m]->name->c_str(), listing);
                    fprintf(listing, " na linha %d: %s já foi declarada como nome de função.\n",
                            s->lineno, var[m]->idName);
                    s = s->next;
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
            BucketList l = hashTable[i];
            while (l != NULL){
                LineList s = l->atrib;
                while (s != NULL){
                    if (!s->type){
                        fprintf(listing, "Erro semantico no escopo ");
                        printScope(l->name->c_str(), listing);
                        fprintf(listing, " na linha %d: atribuição void em %s.\n",
                                s->lineno, l->idName->c_str());
                        erro_ = 1;
                    }
                    s = s->next;
                }
                l = l->next;
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