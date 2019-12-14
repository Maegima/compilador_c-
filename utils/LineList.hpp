/**
 * @file LineList.hpp
 * @author André Lucas Maegima
 * @brief Definição da classe LineList.
 * @version 1.0
 * @date 2019-12-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _LINELIST_HPP_
#define _LINELIST_HPP_

/** @brief Lista encadeada de linhas. */
class LineList{
private:
    /** @brief Número da linha. */
    int lineno;
    /** @brief Tipo. */ 
    int type; 
    /** @brief Próxima linha. */
    LineList *next; 
public:
    /**
     * @brief Construct a new Line List object.
     * 
     * @param lineno Número da linha.
     * @param type Tipo.
     */
    LineList(int lineno, int type);
    /**
     * @brief Get the Lineno object.
     * 
     * @return int Número da linha.
     */
    int getLineno();
    /**
     * @brief Get the Type object.
     * 
     * @return int Tipo.
     */
    int getType();
    /**
     * @brief Get the Next object.
     * 
     * @return LineList* Próxima linha.
     */
    LineList *getNext();
    /**
     * @brief Set the Next object.
     * 
     * @param next Próxima linha.
     */
    void setNext(LineList *next);

};

#endif