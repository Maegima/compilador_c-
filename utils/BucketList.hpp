/**
 * @file BucketList.hpp
 * @author André Lucas Maegima
 * @brief Definição da classe BucketList.
 * @version 1.0
 * @date 2019-12-14
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
     * @return int 1 se o for função e o caso contrário.
     */
    int getFunc();
    /**
     * @brief Set the Func object.
     * 
     * @param func Se o identificador é uma função.
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
     * @brief Get the Next object.
     * 
     * @return BucketList* P
     */
    BucketList *getNext();
    /**
     * @brief Set the Next object.
     * 
     * @param next Próximo item.
     */
    void setNext(BucketList *next);
};

#endif