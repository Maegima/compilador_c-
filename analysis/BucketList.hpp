/**
 * @file BucketList.hpp
 * @author André Lucas Maegima
 * @brief Definição da classe BucketList.
 * @version 2.0
 * @date 2020-06-30
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _BUCKETLIST_HPP_
#define _BUCKETLIST_HPP_

#include <iostream>
#include "LineList.hpp"

/**
 * @brief Armazena os dados de uma
 * entrada na tabela de símbolos. 
 * 
 */
class BucketList{
private:
    std::string *name; /**< @brief Nome do identificador. */
    std::string *idName; /**< @brief Nome do escopo do identificador. */
    int func; /**< @brief Se o identificador é uma função. */
    LineList *lines; /**< @brief Linhas onde o identificador aparece. */
    LineList *atrib; /**< @brief Linhas de atribuição ao identificador. */
    LineList *decl_line; /**< @brief Linhas de declaração do identificador. */
    int memloc; /**< @brief Localização na memória. */
    BucketList *next; /**< @brief Próximo item. */
public:
    /**
     * @brief Construct a new Bucket List object.
     * 
     * @param name Nome do identificador.
     * @param idName Nome do escopo do identificador.
     * @param memloc Localização na memória.
     */
    BucketList(std::string *name, std::string *idName, int memloc);
    /**
     * @brief Get the Name object.
     * 
     * @return std::string* Nome do identificador.
     */
    std::string *getName();
    /**
     * @brief Get the Id Name object.
     * 
     * @return std::string* Nome do escopo do identificador.
     */
    std::string *getIdName();
    /**
     * @brief Get the Func object.
     * 
     * @return int 1 caso objeto for uma função ou 0 caso contrário.
     */
    int getFunc();
    /**
     * @brief Set the Func object.
     * 
     * @param func 1 caso identificador seja uma função.
     */
    void setFunc(int func);
    /**
     * @brief Get the Lines object.
     * 
     * @return LineList* Lista de linhas onde o identificador aparece.
     */
    LineList *getLines();
    /**
     * @brief Set the Lines object.
     * 
     * @param lines Lista de linhas onde o identificador aparece.
     */
    void setLines(LineList *lines);
    /**
     * @brief Get the Atrib object.
     * 
     * @return LineList* Lista de linhas onde de atribuição ao identificador.
     */
    LineList *getAtrib();
    /**
     * @brief Set the Atrib object.
     * 
     * @param atrib Lista de linhas onde de atribuição ao identificador.
     */
    void setAtrib(LineList *atrib);
    /**
     * @brief Get the Decl Line object.
     * 
     * @return LineList* Lista de linhas onde o identificador é declarado.
     */
    LineList *getDeclLine();
    /**
     * @brief Set the Decl Line object.
     * 
     * @param decl_line Lista de linhas onde o identificador é declarado.
     */
    void setDeclLine(LineList *decl_line);
    /**
     * @brief Get the Memloc object.
     * 
     * @return int Localização da linha na memória.
     */
    int getMemloc();
    /**
     * @brief Set the Next object.
     * 
     * @param next Próximo item.
     */
    void setNext(BucketList *next);
    /** @brief Iterator class for BucketList */
    class iterator{
        public:
        typedef BucketList* pointer;
        typedef BucketList& reference;
        iterator(pointer ptr) : ptr(ptr) { }
        iterator& operator++() { ptr = ptr->next; return *this; }
        iterator operator++(int) { iterator temp = *this; ptr = ptr->next; return temp; }
        reference operator*() { return *ptr; }
        pointer operator->() { return ptr; }
        bool operator==(const iterator& rhs) { return ptr == rhs.ptr; }
        bool operator!=(const iterator& rhs) { return ptr != rhs.ptr; }
        private:
        pointer ptr;
    };
    /**
     * @brief Return iterator for first item in BucketList
     * 
     * @return iterator 
     */
    iterator begin(){
        return iterator(this);
    }
    /**
     * @brief Return iterator for last item in BucketList
     * 
     * @return iterator 
     */
    iterator end(){
        return iterator(nullptr);
    }
};

#endif