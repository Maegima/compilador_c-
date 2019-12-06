/**
 * @file symtab.h
 * @author André Lucas Maegima
 * @brief Interface para o analisador semântico
 * @version 0.1
 * @date 2019-12-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _SYMTAB_H_
#define _SYMTAB_H_

/**
 * @brief Procedimento st_insert insere ou 
 * atualiza um dado na tabela de simbolos
 * 
 * @param name Nome
 * @param idName escopo
 * @param lineno linha
 * @param decl_line linha de declaração
 * @param type tipo
 * @param func se é função
 * @param atrib se é atribuição
 * @param loc localização na memória
 */
void st_insert(char * name, char *idName, int lineno, int decl_line, int type, int func, int atrib, int loc);

/**
 * @brief Função st_lookup procura na tabela
 * de símbolos por um dado
 * 
 * @param name Id do dado a ser procurado
 * @return int Localização do dado
 */
int st_lookup (char * name);

/**
 * @brief Procedimento printSymTab imprime em um
 * arquivo a tabela de simbolos
 * 
 * @param listing arquivo de escrita
 */
void printSymTab(FILE * listing);

/**
 * @brief Função que procura e imprime os erros 
 * semânticos e retorna 1 caso ocorrar um erro
 * 
 * @param symbtab tabela de simbolos 
 * @return int Erro
 */
int semantical(FILE *symbtab);

#endif
