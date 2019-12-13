/**
 * @file cgen.hpp
 * @author André Lucas Maegima
 * @brief Interface do gerador de código 
 * intermediário para a linguagem C-.
 * @version 1.0
 * @date 2019-12-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _CGEN_H_
#define _CGEN_H_

#include "TreeNode.hpp"

/**
 * @brief O procedimento codeGen gera o código
 * intermediário.
 * 
 * @param syntaxTree Árvore sintática. 
 * @param codefile Arquivo para escrita do código.
 */
void codeGen(TreeNode * syntaxTree, const char *codefile);

#endif
