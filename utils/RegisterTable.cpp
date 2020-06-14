/**
 * @file RegisterTable.cpp
 * @author André Lucas Maegima
 * @brief Implementação da classe RegisterTable.
 * @version 1.1
 * @date 2020-06-12
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "RegisterTable.hpp"

using namespace std;

RegisterTable::RegisterTable(){
    this->_data = new Register[10];
    this->_size = 0;
    this->_maxsize = 10;
}

RegisterTable::RegisterTable(size_t size){
    this->_data = new Register[size];
    this->_size = 0;
    this->_maxsize = size;
}

int RegisterTable::get(string id){
    int key = 0;
    for(Register r : *this){
        if(r.compare(id) == 0)
            return key;
        key++;
    }
    return -1;
}

int RegisterTable::add(string id){
    int key = get(id);
    size_t pos = 0;
    if(key > -1) return key;
    if(_size == _maxsize) return -1;
    _size++;
    while(_data[pos].compare("") != 0) pos++;
    _data[pos] = id; 
    return pos;
}

int RegisterTable::remove(string id){
    int key = get(id);
    if(key > -1) _data[key] = "";
    return key;
}

int RegisterTable::remove(int key){
    if(key > (int)_maxsize || key < -1) return -1;
    if(_data[key].compare("") == 0) return -1;
    _data[key] = "";
    return key;
}