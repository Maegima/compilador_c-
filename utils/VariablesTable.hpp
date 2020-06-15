/**
 * @file VariablesTable.hpp
 * @author André Lucas Maegima
 * @brief Definição da classe VariablesTable.
 * @version 1.1
 * @date 2020-06-15
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _VARIABLESTSBLE_HPP_
#define _VARIABLESTSBLE_HPP_

#include <string>
#include "Register.hpp"

/**
 * @brief Classe VariablesTable armazena uma tabela de identificadores e seus respectivos registradores.
 * 
 */
class VariablesTable{
    private:
    class Variable{
        public:
        std::string name;
        Register regId;
        bool loaded;
        Variable() : name(""), regId(Register::nreg), loaded(false) {}
    };
    Variable *_data;
    Register *_regs, _lastreg;
    size_t _maxsize, _size;
    /**
     * @brief Construct a new Variables Table object.
     * 
     */
    public:
    /**
     * @brief Construct a new Variables Table object.
     * 
     */
    VariablesTable();
    /**
     * @brief Construct a new Variables Table object with given size.
     * 
     * @param size Table size.
     */
    VariablesTable(size_t size);
    /**
     * @brief Destroy the Variables Table object
     * 
     */
    ~VariablesTable();
    /**
     * @brief Vincula ,caso não esteja vinculado, um registrador ao identificador
     * e retorna o registrador.
     * 
     * @param id Identificador.
     * @return Register Registrador associado.
     */
    Register linkRegister(std::string id);
    /**
     * @brief Vincula um registrador a um id auxiliar e retorna o número do registrador.
     * 
     * @return Register Registrador associado.
     */
    Register linkRegister();
    /**
     * @brief Desvincula o identificador do registrador e retorna o registrador.
     * 
     * @param id Identificador.
     * @return Register Registrador ou -1 caso o identificador não possua registrador vinculado.
     */
    Register linkRegister(size_t key);
    Register unlinkRegister(std::string id);
    /**
     * @brief Desvincula o registrador especificado através do valor key informado.
     * 
     * @param key Registrador a ser desvinculado.
     * @return Register Registrador ou -1 caso o registrador não esteja vinculado.
     */
    Register unlinkRegister(Register key);
    /**
     * @brief Retorna quantidade de elementos na tabela.
     * 
     * @return size_t Quantidade de elementos na tabela.
     */
    const size_t size();
    /** @brief Interator class for Variables Table */
    class iterator{
        public:
        typedef Variable* pointer;
        typedef Variable& reference;
        iterator(pointer ptr) : ptr(ptr) { }
        iterator& operator++() { ptr++; return *this; }
        iterator operator++(int) { iterator temp = *this; ptr++; return temp; }
        reference operator*() { return *ptr; }
        pointer operator->() { return ptr; }
        bool operator==(const iterator& rhs) { return ptr == rhs.ptr; }
        bool operator!=(const iterator& rhs) { return ptr != rhs.ptr; }
        private:
        pointer ptr;
    };
    /**
     * @brief Return iterator for last item in Variable
     * 
     * @return iterator 
     */
    iterator begin(){
        return iterator(this->_data);
    }
    /**
     * @brief Return iterator for last item in Variable
     * 
     * @return iterator 
     */
    iterator end(){
        return iterator(this->_data + _maxsize);
    }
};

#endif