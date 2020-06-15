/**
 * @file VariablesTable.cpp
 * @author André Lucas Maegima
 * @brief Implementação da classe VariablesTable.
 * @version 1.1
 * @date 2020-06-15
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "VariablesTable.hpp"
#include <iostream>

using namespace std;

VariablesTable::VariablesTable(){
    this->_data = new Variable[10];
    this->_regs = new Register[10];
    this->_size = 0;
    this->_maxsize = 10;
    this->_lastreg = 0;
}

VariablesTable::VariablesTable(size_t size){
    this->_data = new Variable[size];
    this->_regs = new Register[size];
    this->_size = 0;
    this->_maxsize = size;
    this->_lastreg = 0;
}

VariablesTable::~VariablesTable(){
    delete[] this->_data;
    delete[] this->_regs;
}

Register VariablesTable::linkRegister(string id){
    size_t key = 0;
    if(_size == _maxsize) return Register::nreg;
    while(key < _maxsize && _data[key].name.compare(id) != 0) key++;
    if(key == _maxsize){
        key = 0;
        while(_data[key].name.size() > 0) key++;
        _data[key].name = id;
    }
    return linkRegister(key);
}

Register VariablesTable::linkRegister(){
    size_t key = 0;
    if(_size == _maxsize) return Register::nreg;
    while(key < _maxsize && _data[key].name.size() > 0) key++;
    if(key == _maxsize){
        cout << "TODO: tratar erro" << endl;
        return Register::nreg;
    }
    _data[key].name = "$";
    return linkRegister(key);
}

Register VariablesTable::linkRegister(size_t key){
    size_t regId;
    if(key >= _maxsize) return Register::nreg;
    if(_data[key].regId == Register::nreg)
        _data[key].regId = _lastreg;
    regId = _data[key].regId;
    _data[key].loaded = true;
    _regs[regId] = key;
    _size++;
    //cout << _size << "  " << _data[key].name << "(" << key << ") last " << (int)_lastreg << " reg " << regId << endl;
    while(_lastreg < _maxsize && _regs[_lastreg] != Register::nreg) _lastreg++;
    if(_lastreg == _maxsize){
        /*for(size_t i = 0; i < _maxsize; i++) cout << (int) _regs[i] << " ";
        cout << endl;
        for(size_t i = 0; i < _maxsize; i++) cout << _data[i].name << "(" << (int)_data[i].regId << ") ";
        cout << endl;*/
        _lastreg = 0;
        do{
            key = _regs[_lastreg++];
            /*cout << "id:" << (int)_data[key].regId << " key:" << key 
            << " ld:" << _data[key].loaded << " " << _data[key].name << endl;*/
        }while(_lastreg < _maxsize && _data[key].loaded); 
        _lastreg--;
        if(!_data[key].loaded){
            /*cout << "limpando " << key << " " << (int)_lastreg << " " << Register::nreg << endl;*/
            _data[key].name = "";
            _data[key].regId = Register::nreg;
            _regs[_lastreg] = Register::nreg;
        }
        /*for(size_t i = 0; i < _maxsize; i++) cout << (int) _regs[i] << " ";
        cout << endl;
        for(size_t i = 0; i < _maxsize; i++) cout << _data[i].name << "(" << (int)_data[i].regId << ") ";
        cout << endl;*/    
    }
    return regId;
}

Register VariablesTable::unlinkRegister(string id){
    size_t key = 0;
    if(id[0] == '$' && id[1] == 't')
        key = stoll(id.substr(2));
    else{
        while(key < _maxsize && _data[key].name.compare(id) != 0) key++;
        if(key == _maxsize) return Register::nreg;
        key =_data[key].regId;
    } 
    return unlinkRegister(key);
}

Register VariablesTable::unlinkRegister(Register reg){    
    size_t key, regId;
    if(reg > _maxsize) return Register::nreg;
    key = _regs[reg];
    if(key == Register::nreg) return Register::nreg;
    regId = _data[key].regId;
    if(_data[key].name[0] == '$'){
        _data[key].name = "";
        _data[key].regId = Register::nreg;
        _regs[regId] = Register::nreg;
        if(regId < _lastreg) _lastreg = regId;
    }
    _data[key].loaded = false;
    _size--;
    return regId;
}