/**
 * @file analyze.hpp
 * @author André Lucas Maegima
 * @brief Interface para o analisador semântico.
 * @version 1.0
 * @date 2019-12-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _ANALYZE_HPP_
#define _ANALYZE_HPP_

#include "TreeNode.hpp"
#include "SymbolTable.hpp"

/**
 * @brief Função que constroi uma tabela de simbolos
 * percorrendo a árvore sintática em pré ordem.
 * 
 * @param syntaxTree Raiz da árvore sintática.
 * @return SymbolTable* Tabela de simbolos.
 */
SymbolTable *buildSymtab(TreeNode *syntaxTree);

#endif
