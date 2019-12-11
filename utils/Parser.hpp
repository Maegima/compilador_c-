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

/**
 * @brief A função parse faz a análise sintática
 * e cria a árvore de análise sintática.
 * 
 * @return TreeNode* Nó raiz da árvore.
 */
TreeNode * parse(void);

/**
 * @brief O procedimento initParser inicializa as váriaveis 
 * do analisador sintático.
 * 
 */
void initParser();

#endif
