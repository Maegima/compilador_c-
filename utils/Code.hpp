/**
 * @file Code.hpp
 * @author André Lucas Maegima
 * @brief Definição da classe Code.
 * @version 1.3
 * @date 2020-06-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _CODE_HPP_
#define _CODE_HPP_

#include <string> 

namespace OP{
    extern const char
    *ADD, *SUB, *DIV, *MULT, *SLT, *SLTE, *SGT, *SGTE, *EQUAL, *DIFFERENT, 
    *FUNC, *ARG, *END, *PARAM, *CALL, *ALLOC_MEM, *LOAD, *LOAD_ADDR, *STORE, 
    *STORE_ADDR, *IF_NOT, *LABEL, *RETURN, *JUMP; 
    enum class operation {
    add, sub, div, mult, slt, slte, sgt, sgte, equal, different, 
    func, arg, end, param, call, alloc_mem, load, load_addr, 
    store, store_addr, if_not, label, ret, jump, noop
    };
    extern operation caseOp(std::string op);
};

class Code{
private:
    std::string _op, _first, _second, _third;
public:
    Code(const char *_op, const char *_first, const char *_second, const char *_third);
    std::string op();
    std::string first();
    std::string second();
    std::string third();
};

#endif