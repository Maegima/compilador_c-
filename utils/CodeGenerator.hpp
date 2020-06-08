/**
 * @file CodeGenerator.hpp
 * @author André Lucas Maegima
 * @brief Definição da classe CodeGenerator. 
 * @version 1.0 
 * @date 2020-04-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _CODEGENERATOR_HPP_
#define _CODEGENERATOR_HPP_

#include "TreeNode.hpp"

/**
 * @brief Classe responsável por gerar o código
 * intermediário.
 * 
 */
class CodeGenerator{
private:
    /// Arquivo para saída do código intermediário.
    FILE *code;
    /// imprimir ou não comentários na geração do código.
    bool trace;
    /**
     * @brief O método intToString converte um 
     * inteiro em uma string.
     * 
     * @param number Número.
     * @return std::string Número no formato string.
     */
    std::string intToString(int number);

    /**
     * @brief O método cGen gera o código intermediário
     * percorrendo a árvore de forma recursiva.
     * 
     * @param tree Nó da árvore.
     * @param operate Último operando.
     */
    void cGen(TreeNode *tree, std::string **operate);

    /**
     * @brief O método ccGen gera o código intermediário
     * percorrendo a árvore de forma recursiva mas sem fazer
     * chamadas recursivas para seus irmãos.
     * 
     * @param tree Nó da árvore.
     * @param operate Último operando.
     */
    void ccGen(TreeNode *tree, std::string **operate);

    /**
     * @brief O método genStmt gera o código intermediário
     * para um nó de declaração.
     * 
     * @param tree Nó da árvore.
     * @param operate Último operando.
     */
    void genStmt(TreeNode *tree, std::string **operate);

    /**
     * @brief O método genExp gera o código intermediário
     * para um nó de expressão.
     * 
     * @param tree Nó da árvore.
     * @param operate Último operando.
     */
    void genExp(TreeNode *tree, std::string **operate);

    /**
     * @brief O método emitComment imprime um 
     * linha de comentário no arquivo de código.
     * 
     * @param c Comentário.
     */
    void emitComment(const char * c);

    /**
     * @brief O método emitQuadruple imprime no 
     * arquivo de código o código intermediário 
     * na forma de quadrupla.
     * 
     * @param op Operador.
     * @param first Primeiro parâmetro.
     * @param second Segundo parâmetro.
     * @param third Terceiro parâmetro.
     */
    void emitQuadruple(const char *op,const char *first, const char *second, const char *third);
public:
    /**
     * @brief Construct a new Code Generator object.
     * 
     * @param code Arquivo para saída do código intermediário.
     * @param trace Rastrear ou não.
     */
    CodeGenerator(FILE *code, bool trace);
    /**
     * @brief O método generate gera o código
     * intermediário.
     * 
     * @param syntaxTree Árvore sintática. 
     */
    void generate(TreeNode * syntaxTree);
};

#endif