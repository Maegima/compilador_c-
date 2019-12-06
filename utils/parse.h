/**
 * @file analyze.h
 * @author André Lucas Maegima
 * @brief Interface para o analisador sintática
 * @version 0.1
 * @date 2019-12-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _PARSE_H_
#define _PARSE_H_

/**
 * @brief Parse faz a análise sintática
 * e cria a árvore de sintática
 * 
 * @return TreeNode* Nó raiz da árvore
 */
TreeNode * parse(void);

/**
 * @brief initParser inicializa as váriaveis 
 * do analizador sintática
 * 
 */
void initParser();

#endif
