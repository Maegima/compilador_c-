/**
 * @file LineList.cpp
 * @author André Lucas Maegima
 * @brief Implementação da classe LineList.
 * @version 2.0
 * @date 2020-07-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "LineList.hpp"

LineList::LineList(int lineno, int type){
    this->lineno = lineno;
    this->type = type;
    this->next = nullptr;
}

int LineList::getLineno(){
        return this->lineno;
}

int LineList::getType(){
    return this->type;
}

void LineList::setNext(LineList *next){
    this->next = next;
}