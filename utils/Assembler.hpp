/**
 * @file Assembler.hpp
 * @author André Lucas Maegima
 * @brief Definição da classe Assembler.
 * @version 1.6
 * @date 2020-06-27
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "LinkedList.hpp"
#include "Code.hpp"
#include <string>

class Assembler{
private:
     /// Arquivo para saída do código de máquina.
    FILE *listing;
    /// Imprimir ou não informação de debug.
    bool trace;
    /**
     * @brief Convert register to number.
     * 
     * @return unsigned int Register number.
     */
    unsigned int registerToNumber(std::string reg);
    /**
     * @brief Convert string number to 21 bit address.
     * 
     * @param num String number.
     * @return unsigned int 21 bit address.
     */
    unsigned int address21(std::string num);
    /**
     * @brief Convert string number to 26 bit address.
     * 
     * @param num String number.
     * @return unsigned int 26 bit address.
     */
    unsigned int address26(std::string num);
    /**
     * @brief Convert string number to 16 bit imediate.
     * 
     * @param num String number.
     * @return unsigned int 16 bit imediate.
     */
    unsigned int imediate16(std::string num);
    /**
     * @brief Convert string number to 21 bit imediate.
     * 
     * @param num String number.
     * @return unsigned int 21 bit imediate.
     */
    unsigned int imediate21(std::string num);
    /**
     * @brief Convert string to opcode.
     * 
     * @param op Operation.
     * @return unsigned int Opcode.  
     */
    unsigned int opcode(std::string op);
    /**
     * @brief Convert string to extended opcode.
     * 
     * @param op Operation.
     * @return unsigned int extended opcode. 
     */
    unsigned int opex(std::string op);
    /**
     * @brief Convert instruction to hexadecimal string representation.
     * 
     * @param inst Instruction.
     * @return string Hexadecimal representation.
     */
    std::string toHex(unsigned int inst);
    /**
     * @brief Convert instruction to binary string representation.
     * 
     * @param inst Instruction.
     * @return string Binary representation.
     */
    std::string toBin(unsigned int inst);
public:
    /**
     * @brief Construct a new Assembler object.
     * 
     * @param listing 
     * @param trace 
     */
    Assembler(FILE *listing, bool trace);
    /**
     * @brief Destroy the Assembler object.
     * 
     */
    ~Assembler();
    /**
     * @brief Gera o código de máquina.
     * 
     * @param alist Lista com as linhas do código assembly.
     * @return LinkedList<unsigned int> Lista com as instruções em código de máquina.
     */
    LinkedList<unsigned int> generate(LinkedList<Code> *alist);
};
