/**
 * @file VariableTable.hpp
 * @author André Lucas Maegima
 * @brief Definição da classe VariableTable.
 * @version 1.1
 * @date 2020-06-12
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _REGISTERTABLE_HPP_
#define _REGISTERTABLE_HPP_

#include <iostream>

/**
 * @brief Classe RegisterTable armazena uma tabela de identificadores e seus respectivos registradores.
 * 
 */
class RegisterTable{
    private:
    typedef std::string Register;
    Register *_data;
    size_t _maxsize, _size;
    /**
     * @brief Construct a new Register Table object.
     * 
     */
    public:
    /**
     * @brief Construct a new Register Table object.
     * 
     */
    RegisterTable();
    /**
     * @brief Construct a new Register Table object with given size.
     * 
     * @param size Table size.
     */
    RegisterTable(size_t size);
    /**
     * @brief Obtém um valor de registrador de acordo com o identificador. 
     * 
     * @param id Identificador.
     * @return int Valor do registrador.
     */
    int get(std::string id);
    /**
     * @brief Adiciona na tabela o identificador e retorno o valor do registrador associado.
     * 
     * @param id Identificador.
     * @return int Valor do registrador associado ao identificador.
     */
    int add(std::string id);
    /**
     * @brief Remove da tabela o identificador e retorno o valor do registrador associado.
     * 
     * @param id Identificador.
     * @return int Valor do registrador associado ao identificador removido ou -1 caso contrário.
     */
    int remove(std::string id);
    /**
     * @brief Remove da tabela o identificador associado ao valor de key informado.
     * 
     * @param key Valor associado ao identificador.
     * @return int Valor do registrador associado ao identificador removido ou -1 caso contrário.
     */
    int remove(int key);
    /**
     * @brief Retorna quantidade de elementos na tabela.
     * 
     * @return size_t Quantidade de elementos na tabela.
     */
    const size_t size();
    /** @brief Interator class for Register */
    class iterator{
        public:
        typedef Register* pointer;
        typedef Register& reference;
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
     * @brief Return iterator for last item in Register
     * 
     * @return iterator 
     */
    iterator begin(){
        return iterator(this->_data);
    }
    /**
     * @brief Return iterator for last item in Register
     * 
     * @return iterator 
     */
    iterator end(){
        return iterator(this->_data + _maxsize);
    }
};

#endif