/**
 * @file parse.h
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
