/**
 * @file VariablesTable.cpp
 * @author André Lucas Maegima
 * @brief Implementação da classe VariablesTable.
 * @version 1.7
 * @date 2020-06-29
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "VariablesTable.hpp"
#include <iostream>

using namespace std;

VariablesTable::VariablesTable(){
    this->_data = new Variable[10];
    this->_lcsize = 0;
    this->_lksize = 0;
    this->_maxsize = 10;
    this->_lastreg = 10;
}

VariablesTable::VariablesTable(size_t size){
    this->_data = new Variable[size];
    this->_lcsize = 0;
    this->_lksize = 0;
    this->_maxsize = size;
    this->_lastreg = size;
}

VariablesTable::VariablesTable(VariablesTable *vartable){
    this->_data = new Variable[vartable->_maxsize];
    this->_lcsize = 0;
    this->_lksize = 0;
    this->_maxsize = vartable->_maxsize;
    this->_lastreg = 0;
    this->_pointers = vartable->_pointers;
    for(size_t i = 0; i < _maxsize; i++){
        if(vartable->_data[i].linked){
            _data[i].name = vartable->_data[i].name;
            _data[i].linked = true;
            _lksize++;
        }
    }
}

VariablesTable::~VariablesTable(){
    delete[] this->_data;
}

size_t VariablesTable::expand(size_t size){
    Variable *data;
    data = new Variable[size + _maxsize];
    for(size_t i = 0; i < _maxsize; i++){
        if(_data[i].linked)
            data[i] = _data[i];    
    }
    delete[] this->_data;
    this->_data = data;
    this->_maxsize += size;
    return this->_maxsize;
}

Register VariablesTable::linkRegister(string id){
    size_t key = 0;
    if(_lcsize == _maxsize) return Register::nreg;
    while(key < _maxsize && _data[key].name.compare(id) != 0) key++;
    if(key == _maxsize){
        if(_lksize == _maxsize){
            cout << "TODO: tratar erro" << endl;
            return Register::nreg;
        }
        key = 0;
        while(_data[key].linked) key++;
        _data[key].name = id;
    }
    return linkRegister(key);
}

Register VariablesTable::linkRegister(){
    size_t key = 0;
    if(_lcsize == _maxsize) return Register::nreg;
    if(_lksize == _maxsize){
        cout << "TODO: tratar erro" << endl;
        return Register::nreg;
    }
    while(_data[key].linked) key++;
    _data[key].name = "$";
    return linkRegister(key);
}

Register VariablesTable::linkRegister(size_t key){
    if(key >= _maxsize) return Register::nreg;
    if(!_data[key].linked){
        _data[key].linked = true;
        _lksize++;
    }
    if(!_data[key].locked){
        _data[key].locked = true;
        _lcsize++;
    }
    _data[key].loaded = true;
    if(_lksize == _maxsize){
        this->expand(1000);
    }
    if(_highsize < _lksize) _highsize = _lksize;
    return key;
}

Register VariablesTable::unlinkRegister(string id){
    size_t key = 0;
    if(id.size() > 2 && id[0] == '$' && id[1] == 't')
        key = stoll(id.substr(2));
    else
        while(key < _maxsize && _data[key].name.compare(id) != 0) key++;
    return unlinkRegister(key);
}

Register VariablesTable::unlinkRegister(size_t key){    
    if(key >= _maxsize) return Register::nreg;
    if(!_data[key].linked) return Register::nreg;
    _lksize--;
    _data[key].name = "";
    _data[key].linked = false;
    _data[key].loaded = false;
    if(_data[key].locked){
        _lcsize--;
        _data[key].locked = false;
        if(key < _lastreg) _lastreg = key;
    }
    return key;
}

Register VariablesTable::unlockRegister(string id){
    size_t key = 0;
    if(id.size() > 2 && id[0] == '$' && id[1] == 't')
        key = stoll(id.substr(2));
    else
        while(key < _maxsize && _data[key].name.compare(id) != 0) key++;
    return unlockRegister(key);
}

Register VariablesTable::unlockRegister(size_t key){
    if(key >= _maxsize) return Register::nreg;
    if(!_data[key].locked) return Register::nreg;
    if(_data[key].name[0] == '$'){
        return unlinkRegister(key);
    } 
    _lcsize--;
    _data[key].locked = false;
    if(key < _lastreg) _lastreg = key;
    return key;
}

Register VariablesTable::unloadRegister(string id){
    size_t key = 0;
    if(id.size() > 2 && id[0] == '$' && id[1] == 't')
        key = stoll(id.substr(2));
    else
        while(key < _maxsize && _data[key].name.compare(id) != 0) key++;
    return unloadRegister(key);
}

Register VariablesTable::unloadRegister(size_t key){
    if(key >= _maxsize) return Register::nreg;
    _data[key].loaded = false;
    return unlockRegister(key);
}

void VariablesTable::addPointer(string id){
    _pointers.push(id);
}

void VariablesTable::removePointer(string id){
    size_t index = _pointers.find(id);
    if(index != nllist)
        _pointers.remove();
}

bool VariablesTable::isLinked(string id){
    size_t key = 0;
    if(id.size() == 0) return false;
    while(key < _maxsize && _data[key].name.compare(id) != 0) key++;
    if(key == _maxsize) return false;
    return _data[key].linked;
}

bool VariablesTable::isLocked(string id){
    size_t key = 0;
    if(id.size() == 0) return false;
    while(key < _maxsize && _data[key].name.compare(id) != 0) key++;
    if(key == _maxsize) return false;
    return _data[key].locked;
}

bool VariablesTable::isLoaded(string id){
    size_t key = 0;
    if(id.size() == 0) return false;
    while(key < _maxsize && _data[key].name.compare(id) != 0) key++;
    if(key == _maxsize) return false;
    return _data[key].loaded;
}

bool VariablesTable::isPointer(string id){
    return (_pointers.find(id) != nllist);
}

const size_t VariablesTable::size(){
    return _lksize;
}

const size_t VariablesTable::highSize(){
    return _highsize;
}