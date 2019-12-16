/**
 * @file Semantic.hpp
 * @author André Lucas Maegima
 * @brief Definição da classe Semantic.
 * @version 1.0
 * @date 2019-12-16
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _SEMANTIC_HPP_
#define _SEMANTIC_HPP_

#include "SymbolTable.hpp"

/**
 * @brief A classe Semantic é responsável pela análise
 * semântica.
 * 
 */
class Semantic{
private:
    /// A tabela de simbolos.
    SymbolTable *table;
    /// Arquivo de saída.
    FILE *listing;
    /**
     * @brief Imprime no arquivo o escopo de name.
     * 
     * @param name Id da tabela de simbolo.
     */
    void printScope(const char *name);

    /**
     * @brief Procura e imprime no arquivo os erros de 
     * não unicidade de declaração.
     * 
     */
    void notUniqueVariable();

    /**
     * @brief Procura e imprime no arquivo de escrita os erros
     * de declaração de variável void.
     * 
     */
    void notVoidVariable();

    /**
     * @brief Procura e imprime no arquivo de escrita os erros
     * de variável não declarada.
     * 
     */
    void variableNotDeclared();

    /**
     * @brief Procura e imprime no arquivo de escrita os erros
     * de função não declarada.
     * 
     */
    void functionNotDeclared();

    /**
     * @brief Procura e imprime no arquivo de escrita o erro
     * de main não declarada.
     * 
     */
    void mainNotDeclared();

    /**
     * @brief Procura e imprime no arquivo de escrita os erros
     * de variável declarada previamente como função.
     * 
     */
    void variableIsFunction();

    /**
     * @brief Procura e imprime no arquivo de escrita os erros
     * atribuição void em variável.
     * 
     */
    void voidAtribuition();
public:
    /**
     * @brief Construct a new Semantic object.
     * 
     * @param table Tabela de simbolos.
     * @param listing Arquivo para saída. 
     */
    Semantic(SymbolTable *table, FILE *listing);
    /**
     * @brief O método analyze procura, imprime os erros 
     * semânticos e retorna 1 caso ocorrar um erro.
     *
     * @return int Erro.
     */
    int analyze();
};

#endif

