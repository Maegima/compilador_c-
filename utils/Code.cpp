/**
 * @file Code.cpp
 * @author André Lucas Maegima
 * @brief Implementação da classe Code.
 * @version 1.3
 * @date 2020-06-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "Code.hpp"
namespace OP{
    const char
    *ADD = "ADD",
    *SUB = "SUB",
    *DIV = "DIV",
    *MULT = "MULT",
    *SLT = "SLT",
    *SLTE = "SLTE",
    *SGT = "SGT",
    *SGTE = "SGTE",
    *EQUAL = "EQUAL",
    *DIFFERENT = "DIFFERENT",
    *FUNC = "FUNC",
    *ARG = "ARG",
    *END = "END",
    *PARAM = "PARAM",
    *CALL = "CALL",
    *ALLOC_MEM = "ALLOC_MEM",
    *LOAD = "LOAD",
    *LOAD_ADDR = "LOAD_ADDR",
    *STORE = "STORE",
    *STORE_ADDR = "STORE_ADDR",
    *IF_NOT = "IF_NOT",
    *LABEL = "LABEL",
    *RETURN = "RETURN",
    *JUMP = "JUMP";

    operation caseOp(std::string op){
        if(op.compare(ADD) == 0)             return operation::add;
        else if(op.compare(SUB) == 0)        return operation::sub;
        else if(op.compare(DIV) == 0)        return operation::div;
        else if(op.compare(MULT) == 0)       return operation::mult;
        else if(op.compare(SLT) == 0)        return operation::slt;
        else if(op.compare(SLTE) == 0)       return operation::slte;
        else if(op.compare(SGT) == 0)        return operation::sgt;
        else if(op.compare(SGTE) == 0)       return operation::sgte;
        else if(op.compare(EQUAL) == 0)      return operation::equal;
        else if(op.compare(DIFFERENT) == 0)  return operation::different;
        else if(op.compare(FUNC) == 0)       return operation::func;
        else if(op.compare(ARG) == 0)        return operation::arg;
        else if(op.compare(END) == 0)        return operation::end;
        else if(op.compare(PARAM) == 0)      return operation::param;
        else if(op.compare(CALL) == 0)       return operation::call;
        else if(op.compare(ALLOC_MEM) == 0)  return operation::alloc_mem;
        else if(op.compare(LOAD) == 0)       return operation::load;
        else if(op.compare(LOAD_ADDR) == 0)  return operation::load_addr;
        else if(op.compare(STORE) == 0)      return operation::store;
        else if(op.compare(STORE_ADDR) == 0) return operation::store_addr;
        else if(op.compare(IF_NOT) == 0)     return operation::if_not;
        else if(op.compare(LABEL) == 0)      return operation::label;
        else if(op.compare(RETURN) == 0)     return operation::ret;
        else if(op.compare(JUMP) == 0)       return operation::jump;
        return operation::noop;
    }
};

using namespace std;

Code::Code(const char *op, const char *first, const char *second, const char *third) : 
_op(op), _first(first), _second(second), _third(third) {} 

std::string Code::op(){
    return _op;
}
std::string Code::first(){
    return _first;
}
std::string Code::second(){
    return _second;
}
std::string Code::third(){
    return _third;
}
