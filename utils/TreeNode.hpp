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

#include <iostream>
#include "TokenType.hpp"

/// Enum de tipos de Nós.
typedef enum {StmtK,ExpK} NodeKind; 
/// Enum de tipos de declarações.
typedef enum {IfK,WhileK,AssignK,ReturnK} StmtKind;
/// Enum de tipos de expressões. 
typedef enum {OpK,ConstK,IdK,FuncK,TypeK,DeclK,FuncDeclK} ExpKind; 
/// ExpType é usado para verificar o tipo da expressão.
typedef enum {Void,Integer} ExpType; 

#define MAXCHILDREN 3 /**< Número máximo de filhos para um nó da árvore sintática. */

/**
 * @brief Definição da árvore.
 * @brief Definição da estrutura da árvore de análise sintática.
 */
class TreeNode{ 
private:
    /// Filhos de um nó.
    TreeNode *child[MAXCHILDREN];
    /// Próximo irmão.
    TreeNode *sibling;
    int lineno; /**< @brief Número da linha. */
    NodeKind nodekind; /**< @brief Tipo de Nó. */
    std::string *scope; /**< @brief Escopo do Nó. */
    /// Tipo de um nó.
    union { StmtKind stmt; ExpKind exp; } kind;
    /// Dado do nó.
    union { TokenType op; int val; std::string *name; } attr;
    /// Tipo de expressão.
    ExpType type;
public:
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
     * @param lisiting Arquivo para impressão da árvore.
     */
    void print(FILE *listing);
    /**
     * @brief Get the Child object
     * 
     * @param index 
     * @return TreeNode* 
     */
    TreeNode *getChild(int index);
    /**
     * @brief Set the Child object
     * 
     * @param value 
     * @param index 
     */
    void setChild(TreeNode *value, int index);
    /**
     * @brief Get the Sibling object
     * 
     * @return TreeNode* 
     */
    TreeNode *getSibling();
    /**
     * @brief Set the Sibling object
     * 
     * @param Sibling 
     */
    void setSibling(TreeNode *Sibling);
    /**
     * @brief Get the Lineno object
     * 
     * @return int 
     */
    int getLineno();
    /**
     * @brief Set the Lineno object
     * 
     * @param lineno 
     */
    void setLineno(int lineno);
    /**
     * @brief Get the Dec Line object
     * 
     * @return int 
     */
    NodeKind getNodekind();
    /**
     * @brief Set the Nodekind object
     * 
     * @param nodekind 
     */
    void setNodekind(NodeKind nodekind);
    /**
     * @brief Get the Scope object
     * 
     * @return std::string* 
     */
    std::string *getScope();
    /**
     * @brief Set the Scope object
     * 
     * @param scope 
     */
    void setScope(std::string *scope);
    /**
     * @brief Get the Stmt object
     * 
     * @return StmtKind 
     */
    StmtKind getStmt();
    /**
     * @brief Set the Stmt object
     * 
     * @param stmt 
     */
    void setStmt(StmtKind stmt);
    /**
     * @brief Get the Exp object
     * 
     * @return ExpKind 
     */
    ExpKind getExp();
    /**
     * @brief Set the Stmt object
     * 
     * @param exp 
     */
    void setExp(ExpKind exp);
    /**
     * @brief Get the Op object
     * 
     * @return TokenType 
     */
    TokenType getOp();
    /**
     * @brief Set the Op object
     * 
     * @param op 
     */
    void setOp(TokenType op);
    /**
     * @brief Get the Val object
     * 
     * @return int 
     */
    int getVal();
    /**
     * @brief Set the Val object
     * 
     * @param val 
     */
    void setVal(int val);
    /**
     * @brief Get the Name object
     * 
     * @return std::string* 
     */
    std::string *getName();
    /**
     * @brief Set the Name object
     * 
     * @param name 
     */
    void setName(std::string *name);
    /**
     * @brief Get the Type object
     * 
     * @return ExpType 
     */
    ExpType getType();
    /**
     * @brief Set the Type object
     * 
     * @param type 
     */
    void setType(ExpType type);
};

#endif