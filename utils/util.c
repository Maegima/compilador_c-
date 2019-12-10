/**
 * @file util.c
 * @author André Lucas Maegima
 * @brief Implementação das funções utilitárias.
 * @version 1.0
 * @date 2019-12-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "globals.hpp"
#include "util.h"

/**
 * @brief O procedimento printToken imprime um token 
 * e seu lexema no arquivo symbtree.
 * 
 * @param token Identificador do token.
 * @param tokenString Descrição textual do token.
 */
void printToken(TokenType token, const char *tokenString){
    switch (token){
    case IF:
    case ELSE:
    case RETURN:
    case WHILE:
        fprintf(symbtree,
                "reserved word: %s\n", tokenString);
        break;
    case ATRIB:
        fprintf(symbtree, ":=\n");
        break;
    case SLT:
        fprintf(symbtree, "<\n");
        break;
    case SLTE:
        fprintf(symbtree, "<=\n");
        break;
    case SGT:
        fprintf(symbtree, ">\n");
        break;
    case SGTE:
        fprintf(symbtree, "<=\n");
        break;
    case EQUAL:
        fprintf(symbtree, "=\n");
        break;
    case DIFFERENT:
        fprintf(symbtree, "!=\n");
        break;
    case OPAREN:
        fprintf(symbtree, "(\n");
        break;
    case CPAREN:
        fprintf(symbtree, ")\n");
        break;
    case SEMICOLON:
        fprintf(symbtree, ";\n");
        break;
    case ADD:
        fprintf(symbtree, "+\n");
        break;
    case SUB:
        fprintf(symbtree, "-\n");
        break;
    case MULT:
        fprintf(symbtree, "*\n");
        break;
    case DIV:
        fprintf(symbtree, "/\n");
        break;
    case ENDFILE:
        fprintf(symbtree, "EOF\n");
        break;
    case NUM:
        fprintf(symbtree,
                "NUM, val= %s\n", tokenString);
        break;
    case ID:
        fprintf(symbtree,
                "ID, name= %s\n", tokenString);
        break;
    case ERR:
        fprintf(symbtree,
                "ERROR: %s\n", tokenString);
        break;
    default: /* should never happen */
        fprintf(symbtree, "Unknown token: %d\n", token);
    }
}

/**
 * @brief A função newStmtNode cria um novo nó de declaração
 * para a construção da árvore sintática.
 * 
 * @param kind Tipo de declaração.
 * @return TreeNode* Nó da árvore sintática.
 */
TreeNode *newStmtNode(StmtKind kind){
    TreeNode *t = (TreeNode *)malloc(sizeof(TreeNode));
    int i;
    if (t == NULL)
        fprintf(symbtree, "Out of memory error at line %d\n", scan->getLineNumber());
    else{
        for (i = 0; i < MAXCHILDREN; i++)
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = StmtK;
        t->kind.stmt = kind;
        t->lineno = scan->getLineNumber();
        t->type = Void;
        t->decl_line = -1;
        t->func = 0;
        t->atrib = 0;
        t->decl = 0;
    }
    return t;
}

/**
 * @brief A função newExpNode cria um novo nó de expressão
 * para a construção da árvore sintática.
 * 
 * @param kind Tipo de expressão.
 * @return TreeNode* Nó da árvore sintática.
 */
TreeNode *newExpNode(ExpKind kind)
{
    TreeNode *t = (TreeNode *)malloc(sizeof(TreeNode));
    int i;
    if (t == NULL)
        fprintf(symbtree, "Out of memory error at line %d\n", scan->getLineNumber());
    else{
        for (i = 0; i < MAXCHILDREN; i++)
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = ExpK;
        t->kind.exp = kind;
        t->lineno = scan->getLineNumber();
        t->type = Void;
        t->decl_line = -1;
        t->func = 0;
        t->atrib = 0;
        t->decl = 0;
    }
    return t;
}

/**
 * @brief A função copyString cria e aloca uma nova
 * cópia da string passada como parâmetro.
 * 
 * @param s String a ser copiada.
 * @return char* Endereço da copia criada.
 */
char *copyString(char *s){
    int n;
    char *t;
    if (s == NULL)
        return NULL;
    n = strlen(s) + 1;
    t = (char *)malloc(n);
    if (t == NULL)
        fprintf(symbtree, "Out of memory error at line %d\n", scan->getLineNumber());
    else
        strcpy(t, s);
    return t;
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

/**
 * @brief O procedimento printTree imprime a árvore sintática
 * no arquivo symbtree usando identação para indicar sub-árvores.
 * 
 * @param tree Raiz da árvore.
 */
void printTree(TreeNode *tree){
    int i;
    INDENT;
    while (tree != NULL)
    {
        printSpaces();
        if (tree->nodekind == StmtK)
        {
            switch (tree->kind.stmt)
            {
            case IfK:
                fprintf(symbtree, "If\n");
                break;
            case WhileK:
                fprintf(symbtree, "While\n");
                break;
            case AssignK:
                fprintf(symbtree, "Assign to: %s\n", tree->attr.name);
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
                printToken(tree->attr.op, "\0");
                break;
            case ConstK:
                fprintf(symbtree, "Const: %d\n", tree->attr.val);
                break;
            case IdK:
                fprintf(symbtree, "Id: %s\n", tree->attr.name);
                break;
            case TypeK:
                fprintf(symbtree, "Type: %s\n", tree->attr.name);
                break;
            default:
                fprintf(symbtree, "Unknown ExpNode kind\n");
                break;
            }
        }
        else
            fprintf(symbtree, "Unknown node kind\n");
        for (i = 0; i < MAXCHILDREN; i++)
            printTree(tree->child[i]);
        tree = tree->sibling;
    }
    UNINDENT;
}
