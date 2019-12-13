/**
 * @file util.h
 * @author André Lucas Maegima
 * @brief Funções utilitárias para o compilador de C-.
 * @version 1.0
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
 * @brief A função copyString cria e aloca uma nova
 * cópia da string passada como parâmetro.
 * 
 * @param s String a ser copiada.
 * @return char* Endereço da copia criada.
 */
char * copyString(const char *s);


#endif
