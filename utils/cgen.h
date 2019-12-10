/**
 * @file cgen.h
 * @author André Lucas Maegima
 * @brief Interface do gerador de código 
 * intermediário para a linguagem C-.
 * @version 0.1
 * @date 2019-12-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _CGEN_H_
#define _CGEN_H_

/**
 * @brief O procedimento codeGen gera o código
 * intermediário.
 * 
 * @param syntaxTree Árvore sintática. 
 * @param codefile Arquivo para escrita do código.
 */
void codeGen(TreeNode * syntaxTree, const char *codefile);

#endif
