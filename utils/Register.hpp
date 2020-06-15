/**
 * @file Register.hpp
 * @author André Lucas Maegima
 * @brief Definição da classe Register.
 * @version 1.1
 * @date 2020-06-15
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _REGISTER_HPP_
#define _REGISTER_HPP_

#include <string>

/**
 * @brief Classe Register representa um valor de registrador.
 * 
 */
class Register{
    private:
    unsigned int value;
    public:
    /**
     * @brief Construct a new Register object.
     * 
     */
    Register();
    /**
     * @brief Construct a new Register object.
     * 
     * @param v Register value.
     */
    Register(int v);
    Register& operator=(const unsigned int& other);
    Register& operator++();
    Register operator++(int);
    Register& operator--();
    Register operator--(int);
    operator unsigned int() const ;
    operator std::string*();
    static const unsigned int nreg;
};

#endif