/**
 * @file Register.cpp
 * @author André Lucas Maegima
 * @brief Definição da classe VariablesTable.
 * @version 2.0
 * @date 2020-06-30
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "Register.hpp"

const unsigned int Register::nreg = -1;

using namespace std;

Register::Register(){
    this->value = Register::nreg;
}
Register::Register(int v){
    this->value = v;
}
Register& Register::operator=(const unsigned int& other){ 
    this->value = other; 
    return *this; 
}
Register::operator unsigned int() const { 
    return this->value; 
}
Register::operator std::string*() {
    return new std::string("$t" + std::to_string(this->value));
}
Register& Register::operator++(){
    this->value++;
    return *this;
}
Register Register::operator++(int){
    Register tmp(*this);
    this->value++;
    return tmp;
}

Register& Register::operator--(){
    this->value--;
    return *this;
}
Register Register::operator--(int){
    Register tmp(*this);
    this->value--;
    return tmp;
}