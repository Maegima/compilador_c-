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

#include "SymbolTable.hpp"

/**
 * @brief A função que procura e imprime os erros 
 * semânticos e retorna 1 caso ocorrar um erro.
 * 
 * @param table Tabela de simbolos.
 * @param listing Arquivo de escrita.
 * @return int Erro.
 */
int semantical(SymbolTable *table, FILE *listing);

#endif
