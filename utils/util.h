/**
 * @file util.h
 * @author André Lucas Maegima
 * @brief Funções utilitárias para o compilador de C-.
 * @version 0.1
 * @date 2019-12-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _UTIL_H_
#define _UTIL_H_

/**
 * @brief O procedimento printToken imprime um token 
 * e seu lexema no arquivo symbtree.
 * 
 * @param token Identificador do token.
 * @param tokenString Descrição textual do token.
 */
void printToken(TokenType token, const char* tokenString);

/**
 * @brief A função newStmtNode cria um novo nó de declaração
 * para a construção da árvore sintática.
 * 
 * @param kind Tipo de declaração.
 * @return TreeNode* Nó da árvore sintática.
 */
TreeNode *newStmtNode(StmtKind kind);

/**
 * @brief A função newExpNode cria um novo nó de expressão
 * para a construção da árvore sintática.
 * 
 * @param kind Tipo de expressão.
 * @return TreeNode* Nó da árvore sintática.
 */
TreeNode * newExpNode(ExpKind kind);

/**
 * @brief A função copyString cria e aloca uma nova
 * cópia da string passada como parâmetro.
 * 
 * @param str String a ser copiada.
 * @return char* Endereço da copia criada.
 */
char * copyString(char *str);

/**
 * @brief O procedimento printTree imprime a árvore sintática
 * no arquivo symbtree usando identação para indicar sub-árvores.
 * 
 * @param tree Raiz da árvore.
 */
void printTree(TreeNode *tree);

#endif
