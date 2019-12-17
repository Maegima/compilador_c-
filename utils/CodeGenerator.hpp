/**
 * @file CodeGenerator.hpp
 * @author André Lucas Maegima
 * @brief Definição da classe CodeGenerator. 
 * @version 1.0 
 * @date 2019-12-17
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
    /**
     * @brief O método intToString converte um 
     * inteiro em uma string.
     * 
     * @param str Buffer onde o número será armazenado.
     * @param v Número.
     * @param n Tamanho do buffer.
     */
    void intToString(char *str, int v, int n);

    /**
     * @brief O método strNumber concatena uma string com um número.
     * 
     * @param str String base.
     * @param number Número.
     * @return char* Endereço da nova string.
     */
    char *strNumber(const char *str, int number);

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
public:
    /**
     * @brief Construct a new Code Generator object.
     * 
     */
    CodeGenerator();
    /**
     * @brief O método generate gera o código
     * intermediário.
     * 
     * @param syntaxTree Árvore sintática. 
     */
    void generate(TreeNode * syntaxTree);
};

#endif