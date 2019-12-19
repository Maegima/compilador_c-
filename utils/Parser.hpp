/**
 * @file Parser.hpp
 * @author André Lucas Maegima
 * @brief Definição da classe utilizada para a análise sintática.
 * @version 1.0
 * @date 2019-12-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include "TreeNode.hpp"

class Parser{
private:
    /// Raiz da árvore sintática.
    TreeNode * savedTree;
    ///  Imprimir ou não a árvore sintática após sua construção.
    bool trace;
public:
    /**
     * @brief O método Parser inicializa as váriaveis 
     * do analisador sintático.
     * 
     */
    Parser();

    /**
     * @brief O método Parser inicializa as váriaveis 
     * do analisador sintático.
     * 
     * @param trace Rastrear ou não.
     */
    Parser(bool trace);

    /**
     * @brief O método parse faz a análise sintática
     * e cria a árvore de análise sintática.
     * 
     * @return TreeNode* Nó raiz da árvore.
     */
    TreeNode *parse();
    /**
     * @brief O método setSavedTree altera o valor da 
     * raiz da árvore de ánalise sintática.
     * 
     * @param savedTree Raiz da árvore.
     */
    void setSavedTree(TreeNode *savedTree);
};

#endif
