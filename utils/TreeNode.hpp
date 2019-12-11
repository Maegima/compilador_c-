/**
 * @file TreeNode.hpp
 * @author André Lucas Maegima
 * @brief Definição da árvore sintática.
 * @version 1.0
 * @date 2019-12-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _TREENODE_HPP_
#define _TREENODE_HPP_

#include "TokenType.hpp"

/// Enum de tipos de Nós.
typedef enum {StmtK,ExpK} NodeKind; 
/// Enum de tipos de declarações.
typedef enum {IfK,WhileK,AssignK,ReturnK} StmtKind;
/// Enum de tipos de expressões. 
typedef enum {OpK,ConstK,IdK,TypeK} ExpKind; 
/// ExpType é usado para verificar o tipo da expressão.
typedef enum {Void,Integer} ExpType; 

#define MAXCHILDREN 3 /**< Número máximo de filhos para um nó da árvore sintática. */

/**
 * @brief Definição da árvore.
 * @brief Definição da estrutura da árvore de análise sintática.
 */
class TreeNode{ 
private:
public:
    /// Filhos de um nó.
    TreeNode *child[MAXCHILDREN];
    /// Próximo irmão.
    TreeNode *sibling;
    int lineno /** @brief Número da linha. */, decl_line /** @brief Linha de declaração. */; 
    int func /** @brief Se for função. */, atrib /** @brief Se for atribuição. */, decl /** @brief Se for declaração. */;
    NodeKind nodekind; /**< @brief Tipo de Nó. */
    char *scope; /**< @brief Escopo do Nó. */
    /// Tipo de um nó.
    union { StmtKind stmt; ExpKind exp; } kind;
    /// Dado do nó.
    union { TokenType op; int val; char *name; } attr;
    /// Tipo de expressão.
    ExpType type;
    /**
     * @brief O construtor TreeNode cria um novo nó de declaração
     * para a construção da árvore sintática.
     * 
     * @param kind Tipo de declaração.
     */
    TreeNode(StmtKind kind);

    /**
     * @brief O construtor TreeNode cria um novo nó de expressão
     * para a construção da árvore sintática.
     * 
     * @param kind Tipo de expressão.
     */
    TreeNode(ExpKind kind);

    /**
     * @brief O método print imprime a árvore sintática
     * no arquivo symbtree usando identação para indicar sub-árvores.
     * 
     */
    void print();
};

#endif