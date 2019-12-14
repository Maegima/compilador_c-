/**
 * @file symtab.hpp
 * @author André Lucas Maegima
 * @brief Interface para o analisador semântico.
 * @version 1.0
 * @date 2019-12-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _SYMTAB_HPP_
#define _SYMTAB_HPP_

#include <iostream>

/**
 * @brief Procedimento st_insert insere ou 
 * atualiza um dado na tabela de simbolos.
 * 
 * @param name Nome.
 * @param idName Escopo.
 * @param lineno Linha.
 * @param decl_line Linha de declaração.
 * @param type Tipo.
 * @param func Se é função.
 * @param atrib Se é atribuição.
 * @param loc Localização na memória.
 */
void st_insert(std::string *name, std::string *idName, int lineno, int decl_line, int type, int func, int atrib, int loc);

/**
 * @brief A função st_lookup procura na tabela
 * de símbolos por um dado.
 * 
 * @param name Id do dado a ser procurado.
 * @return int Localização do dado.
 */
int st_lookup (std::string *name);

/**
 * @brief O procedimento printSymTab imprime em um
 * arquivo a tabela de simbolos.
 * 
 * @param listing Arquivo de escrita.
 */
void printSymTab(FILE * listing);

/**
 * @brief A função que procura e imprime os erros 
 * semânticos e retorna 1 caso ocorrar um erro.
 * 
 * @param listing Arquivo de escrita.
 * @return int Erro.
 */
int semantical(FILE *listing);

#endif
