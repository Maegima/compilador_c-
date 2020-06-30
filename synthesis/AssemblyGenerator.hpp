/**
 * @file AssemblyGenerator.hpp
 * @author André Lucas Maegima
 * @brief Definição da classe AssemblyGenerator.
 * @version 2.0
 * @date 2020-06-30
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _ASSEMBLYGENERATOR_HPP_
#define _ASSEMBLYGENERATOR_HPP_

#include "LinkedList.hpp"
#include "Code.hpp"
#include <map>

class AssemblyGenerator
{
private:
    /// Arquivo para saída do código assembly.
    FILE *assembly;
    /// imprimir ou não informação de debug.
    bool trace;
    /// lista com as linhas do código assembly.
    LinkedList<Code> *alist;
    /// map variables and address.
    std::map<std::string, int> addr, global;
    /// Posição corrente da memória.
    size_t addr_pos;
    /**
     * @brief Generate Arithmetic and Logic Operations.
     * 
     * @param op Operation.
     * @param c Intermediate code.
     */
    void generateArithmeticLogicOp(std::string op, Code c);
    /**
     * @brief Generate Direct Memory Operations.
     * 
     * @param op Operation.
     * @param c Intermediate code.
     */
    void generateDirectMemoryOp(std::string op, Code c);
    /**
     * @brief Generate Indirect Memory Operations.
     * 
     * @param op Operation.
     * @param c Intermediate code.
     */
    void generateIndirectMemoryOp(std::string op, Code c);
    /**
     * @brief Generate Memory allocation.
     * 
     * @param c Intermediate code.
     * @return int Posições de memória alocadas. 
     */
    size_t generateAllocMemory(Code c);
    /**
     * @brief Imprime o código um comando do código assembly. 
     * 
     * @param c Código assembly.
     */
    void emitAssembly(Code c);
public:
    /**
     * @brief Construct a new Assembly Generator object
     * 
     * @param assembly 
     * @param trace 
     */
    AssemblyGenerator(FILE *assembly, bool trace);
    /**
     * @brief Destroy the Assembly Generator object
     * 
     */
    ~AssemblyGenerator();
    /**
     * @brief Gera o código assembly.
     * 
     * @param clist Código intermediário.
     * @return LinkedList<Code> Lista das linhas do código assembly.
     */
    LinkedList<Code> *generate(LinkedList<Code> *clist);
};


#endif