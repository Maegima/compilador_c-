/**
 * @file Parser.hpp
 * @author André Lucas Maegima
 * @brief Definição da classe utilizada para a análise sintática.
 * @version 1.0
 * @date 2019-12-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _PARSER_HPP_
#define _PARSER_HPP_

/* Yacc/Bison generates internally its own values
 * for the tokens. Other files can access these values
 * by including the tab.h file generated using the
 * Yacc/Bison option -d ("generate header").
 *
 * The YYPARSER flag prevents inclusion of the tab.h
 * into the Yacc/Bison output itself.
 */

#ifndef YYPARSER

/* Nome do header do parser criado pelo bison. */
#include "../parser.h"

/** ENDFILE é definido implicitamente pelo Yacc/Bison,
 * mas não é icluido no arquivo tab.h.
 */
#define ENDFILE 0

#endif

#include "TreeNode.hpp"

/**
 * @brief Classe responsável pela análise sintática. 
 * 
 */
class Parser{
private:
    /// Raiz da árvore sintática.
    TreeNode * savedTree;
    /// Imprimir ou não a árvore sintática após sua construção.
    bool trace;
    ///  Indica se houve erro no parser.
    bool error;
    /// Arquivo para impressão da árvore sintática.
    FILE *listing;
public:
    /**
     * @brief O método Parser inicializa as váriaveis 
     * do analisador sintático.
     * 
     * @param listing Arquivo para impressão da árvore sintática.
     * @param trace Rastrear ou não.
     */
    Parser(FILE *lisiting, bool trace);

    /**
     * @brief O método parse faz a análise sintática
     * e cria a árvore de análise sintática.
     * 
     * @param tree Endereço da raiz da árvore.
     * @return true Caso ocorra erro no parser.
     * @return false Caso não ocorra erro no parser.
     */
    bool parse(TreeNode **tree);
    
    /**
     * @brief O método setSavedTree altera o valor da 
     * raiz da árvore de ánalise sintática.
     * 
     * @param savedTree Raiz da árvore.
     */
    void setSavedTree(TreeNode *savedTree);

    /**
     * @brief O método setError altera o valor de
     * error para true.
     * 
     */
    void setError();
};

#endif
