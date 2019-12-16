/**
 * @file BucketList.cpp
 * @author André Lucas Maegima
 * @brief 
 * @version 1.0
 * @date 2019-12-15
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "BucketList.hpp"

using namespace std;

BucketList::BucketList(string *name, string *idName, int memloc){
    this->name = name;
    this->idName = idName;
    this->memloc = memloc;
}

string *BucketList::getName(){
    return this->name;
}
string *BucketList::getIdName(){
    return this->idName;
}
int BucketList::getFunc(){
    return this->func;
}
void BucketList::setFunc(int func){
    this->func = func;
}
LineList *BucketList::getLines(){
    return this->lines;
}
void BucketList::setLines(LineList *lines){
    this->lines = lines;
}
LineList *BucketList::getAtrib(){
    return this->atrib;
}
void BucketList::setAtrib(LineList *atrib){
    this->atrib = atrib;
}
LineList *BucketList::getDeclLine(){
    return this->decl_line;
}
void BucketList::setDeclLine(LineList *decl_line){
    this->decl_line = decl_line;
}
int BucketList::getMemloc(){
    return this->memloc;
}
BucketList *BucketList::getNext(){
    return this->next;
}
void BucketList::setNext(BucketList *next){
    this->next = next;
}