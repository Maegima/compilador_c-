/**
 * @file LineList.cpp
 * @author André Lucas Maegima
 * @brief Implementação da classe LineList.
 * @version 1.0 
 * @date 2020-06-04
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "Linelist.hpp"

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

LineList *LineList::getNext(){
    return this->next;
}

void LineList::setNext(LineList *next){
    this->next = next;
}