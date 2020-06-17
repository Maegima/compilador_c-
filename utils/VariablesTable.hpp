/**
 * @file VariablesTable.hpp
 * @author André Lucas Maegima
 * @brief Definição da classe VariablesTable.
 * @version 1.2
 * @date 2020-06-16
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
        bool linked;
        bool locked;
        bool loaded;
        Variable() : name(""), linked(false), locked(false), loaded(false) {}
    };
    Variable *_data;
    size_t _maxsize, _lcsize, _lksize, _lastreg;
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
     * @brief Construct a new Variables Table copying the given Variables table.
     * 
     * @param size Table size.
     */
    VariablesTable(VariablesTable *vartable);
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
     * @brief Vincula um registrador uma posição da tabela e retorna o número do registrador.
     * 
     * @param key Posição da tabela. 
     * @return Register Registrador associado.
     */
    Register linkRegister(size_t key);
    /**
     * @brief Desvincula o identificador do registrador e retorna o registrador.
     * 
     * @param id Identificador.
     * @return Register Registrador ou -1 caso o identificador não possua registrador vinculado.
     */
    Register unlinkRegister(std::string id);
    /**
     * @brief Desvincula o registrador especificado através do valor key informado.
     * 
     * @param key Registrador a ser desvinculado.
     * @return Register Registrador ou -1 caso o registrador não esteja vinculado.
     */
    Register unlinkRegister(size_t key);
    /**
     * @brief Descarrega o registrador do identificador especificado.
     * 
     * @param key Registrador associado.
     * @return Register Registrador ou -1 caso o registrador já esteja descarregado.
     */
    Register unloadRegister(std::string id);
    /**
     * @brief Descarrega o registrador através do valor de key informado.
     * 
     * @param key Registrador associado.
     * @return Register Registrador ou -1 caso o registrador já esteja descarregado.
     */
    Register unloadRegister(size_t key);
    /**
     * @brief Libera o registrador do identificador e retorna o registrador.
     * 
     * @param id Identificador.
     * @return Register Registrador ou -1 caso o registrador já esteja liberado.
     */
    Register unlockRegister(std::string id);
    /**
     * @brief Libera o registrador através do valor de key informado.
     * 
     * @param key Registrador associado.
     * @return Register Registrador ou -1 caso o registrador já esteja liberado.
     */
    Register unlockRegister(size_t key);
    /**
     * @brief Testa se o identificador informado possui um registrador associado.
     * 
     * @param id Identificador.
     * @return true Caso o identificador possua um registrador associado.
     * @return false Caso o identificador não possua um registrador associado.
     */
    bool isLinked(std::string id);
    /**
     * @brief Testa se o identificador informado possui um registrador reservado.
     * 
     * @param id Identificador.
     * @return true Caso o identificador possua um registrador reservado.
     * @return false Caso o identificador não possua um registrador reservado.
     */
    bool isLocked(std::string id);
    /**
     * @brief Testa se o identificador informado possui um registrador carregado.
     * 
     * @param id Identificador.
     * @return true Caso o identificador possua um registrador carregado.
     * @return false Caso o identificador não possua um registrador carregado.
     */
    bool isLoaded(std::string id); 
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