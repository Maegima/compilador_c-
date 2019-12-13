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

#ifndef _ANALYZE_H_
#define _ANALYZE_H_

#include "TreeNode.hpp"

/**
 * @brief Função que constroi uma tabela de simbolos
 * percorrendo a árvore sintática em pré ordem.
 * 
 * @param syntaxTree Raiz da árvore sintática.
 */
void buildSymtab(TreeNode *syntaxTree);

/**
 * @brief uniteStrings junta duas strings em uma 
 * separadas por espaço.
 * 
 * @param str1 Primeira string.
 * @param str2 Segunda string.
 * @return char* Endereço da string resultante.
 */
char *uniteStrings(const char* str1, const char *str2);

#endif
