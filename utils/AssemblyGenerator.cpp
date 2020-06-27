/**
 * @file AssemblyGenerator.cpp
 * @author André Lucas Maegima
 * @brief Implementação da classe AssemblyGenerator.
 * @version 1.5
 * @date 2020-06-27
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <ext/stdio_filebuf.h>
#include "AssemblyGenerator.hpp"
#include "VariablesTable.hpp"
#include <iostream>

using namespace OP;

using namespace std;

static VariablesTable *var_table = new VariablesTable();

ostream *out;
__gnu_cxx::stdio_filebuf<char> *buff_out;

AssemblyGenerator::AssemblyGenerator(FILE *assembly, bool trace) : 
assembly(assembly), trace(trace), alist(new LinkedList<Code>()), addr(), addr_pos(0){
    buff_out = new __gnu_cxx::stdio_filebuf<char>(fileno(assembly), std::ios::out);
    out = new ostream(buff_out);
}

AssemblyGenerator::~AssemblyGenerator(){
    delete out;
    delete buff_out;
}

void AssemblyGenerator::generateArithmeticLogicOp(string op, Code c){
    if(c.second()[0] == '$'){
        if(c.third()[0] == '$')
            *out << op << " " << c.first() << " " << c.second() << " " << c.third() << endl;
        else
            *out << op << "i " << c.first() << " " << c.second() << " " << c.third() << endl; 
    }
    else if(c.third()[0] == '$'){
        *out << op << "i " << c.first() << " " << c.third() << " " << c.second() << endl;
    }
    else{
        *out << "set " << c.first() << " " << c.second() << endl;
        *out << op << "i " << c.first() << " " << c.first() << " " << c.third() << endl;
    }
    var_table->unlockRegister(c.second());
    var_table->unlockRegister(c.third()); 
}

void AssemblyGenerator::emitAssembly(Code c){
    alist->push(c);
    *out << c.op();
    if(c.first() != "") 
        *out << " " << c.first();
    if(c.second() != "") 
        *out << " " << c.second(); 
    if(c.third() != "")
        *out <<  " " << c.third(); 
    *out << endl;
}

void AssemblyGenerator::generateDirectMemoryOp(string op, Code c){
    string first, second, third;
    if(c.first()[0] == '$')
        first = c.first();
    else{
        first = *var_table->linkRegister();
        *out << "set " << first << " " << c.first() << endl;
        var_table->unlinkRegister(first);
    }
    if(c.third()[0] == '-'){
        if(addr.count(c.second())){
            second = "$fp";
            third = to_string(addr[c.second()]);
        }
        else
            second = to_string(global[c.second()]);
    }
    else{
        if(c.second()[0] == '$'){
            if(addr.count(c.third())){
                second = first;
                if(op == "store"){
                    second = *var_table->linkRegister();
                    var_table->unlinkRegister(second);
                }
                emitAssembly(Code("add", second.c_str(), "$fp", c.second().c_str()));
                third = to_string(addr[c.third()]);
            }
            else{
                second = c.second();
                third = to_string(global[c.third()]);
            }
        }
        else{
            if(addr.count(c.third())){
                second = "$fp";
                third = to_string(addr[c.third()] + stoi(c.second()));
            }
            else
                third = to_string(global[c.third()] + stoi(c.second()));     
        }
    }
    if(trace){
        if(c.third()[0] == '-'){
            *out << "///" << c.second() << ":";
            if(second == "$fp") 
                *out << third << endl;
            else
                *out << second << endl; 
        }
        else
            *out << "///" << c.third() << ":" << third << endl;
    }
    emitAssembly(Code(op.c_str(), first.c_str(), second.c_str(), third.c_str()));
}

void AssemblyGenerator::generateIndirectMemoryOp(string op, Code c){
    string first, second, third;
    if(c.first()[0] == '$')
        first = c.first();
    else{
        first = *var_table->linkRegister();
        emitAssembly(Code("set", first.c_str(), c.first().c_str(), ""));
    }
    if(c.third()[0] == '-'){
        if(op == "load") op = "addi";
        if(addr.count(c.second())){
            second = "$fp";
            third = to_string(addr[c.second()]);
        }
        else{
            second = "$0";
            third = to_string(global[c.second()]);
        }
    }
    else{
        if(addr.count(c.third())){
            third = to_string(addr[c.third()]);
            emitAssembly(Code("load", first.c_str(), "$fp", third.c_str()));
            if(c.second()[0] == '$')
                emitAssembly(Code("add", first.c_str(), first.c_str(), c.second().c_str()));
            else
                emitAssembly(Code("addi", first.c_str(), first.c_str(), c.second().c_str()));
            second = first;
            third = "";
        }
        else{
            *out << "isso nao deveria estar acontecendo " << c.first() << " " << c.second() << " " << c.third() << endl;
        }
    }
    if(trace){
        if(c.third()[0] == '-')
            *out << "///" << c.second() << ":" << third << endl;
        else
            *out << "///" << c.third() << ":" << to_string(addr[c.third()]) << endl;
    }
    emitAssembly(Code(op.c_str(), first.c_str(), second.c_str(), third.c_str()));
}

size_t AssemblyGenerator::generateAllocMemory(Code c){
    size_t size;
     if(c.second()[0] == '-'){
        size = 1;
        if(trace)
            *out << "///alloc var " << c.first() << "[" << addr_pos << "]" << endl;
    }
    else{
        size = stoi(c.second());
        if(trace)    
            *out << "///alloc ptr " << c.first() << "[" << addr_pos << "]" << endl;
    }
    addr[c.first()] = addr_pos;
    addr_pos += size;
    return size;
}

LinkedList<Code> *AssemblyGenerator::generate(LinkedList<Code> *clist){
    int args = 0, local_var = 0, loop_var = 0;
    string *reg;
    int i = 0, func = 0;
    LinkedList<int> loop;
    for(Code c: *clist){
        switch (caseOp(c.op())){
        case operation::func: func = 1; break;
        case operation::end: func = 0; break;
        case operation::alloc_mem:
            if(func == 0){
                local_var += generateAllocMemory(c); 
                clist->remove(i); i--;
            }
            break;
        default:
            break;
        }
        i++;
    }
    if(local_var > 0)
        *out << "addi $sp $sp " << local_var << endl;
    *out << "move $fp $sp" << endl;
    *out << "jump main" << endl;
    global = addr;
    for(Code c : *clist){
        operation last;
        if(last == operation::alloc_mem){
            if(caseOp(c.op()) != last){
                if(loop_var < 0){
                    *out << "addi $sp $sp " << local_var << endl;
                    loop_var = 0;
                }
                else{
                    *out << "addi $sp $sp " << loop_var << endl;
                }
            }
        }
        switch(last = caseOp(c.op())){
        case operation::add:
            generateArithmeticLogicOp("add", c);
            break;
        case operation::sub:
            generateArithmeticLogicOp("sub", c);
            break;
        case operation::div:
            generateArithmeticLogicOp("div", c);
            break;
        case operation::mult:
            generateArithmeticLogicOp("mult", c);
            break;
        case operation::slt:
            generateArithmeticLogicOp("slt", c);
            break;
        case operation::slte:
            generateArithmeticLogicOp("slte", c);
            break;
        case operation::sgt:
            generateArithmeticLogicOp("sgt", c);
            break;
        case operation::sgte:
            generateArithmeticLogicOp("sgte", c);
            break;
        case operation::equal:
            generateArithmeticLogicOp("equal", c);
            break;
        case operation::different:
            generateArithmeticLogicOp("different", c);
            break;
        case operation::func:
            args = stoi(c.third()); addr_pos = 0; local_var = 0, loop_var = -1;
            addr = map<string, int>();
            delete var_table;
            var_table = new VariablesTable();
            *out << c.second() << ":" << endl;
            break;
        case operation::arg:
            addr[c.second()] = -(args--);
            if(trace)
                *out << "///alloc " << c.second() << "[" << addr[c.second()] << "]" << endl;
            break;
        case operation::ret:
            *out << "subi $sp $sp " << local_var << endl;
            if(c.first()[0] == '$'){
                *out << "push " << c.first() << endl;
                var_table->unlinkRegister(c.first());
            }
            else{
                reg = var_table->linkRegister();
                *out << "set " << *reg << c.first() << endl;
                *out << "push " << *reg << endl;
                var_table->unlinkRegister(*reg);
            }
            *out << "jaunl" << endl;
            break;
        case operation::end:
            *out << "subi $sp $sp " << local_var << endl;
            *out << "jaunl" << endl;
            break;
        case operation::param:
            if(c.first()[0] == '$')
                *out << "push " << c.first() << endl;
            else{
                reg = var_table->linkRegister();
                *out << "set " << *reg << " " << c.first() << endl;
                *out << "push " << *reg << endl;
                var_table->unlinkRegister(*reg);
            }
            break;
        case operation::call:
            *out << "move $fp $sp" << endl;
            *out << "jal " << c.first() << endl;
            if(c.third()[0] == '$'){
                *out << "pop " << c.third() << endl;
                var_table->linkRegister();
            }
            for(i = 0; i < stoi(c.second()); i++){
                *out << "pop $0" << endl;
            }
            break;
        case operation::alloc_mem:
            if(loop_var < 0)
                local_var += generateAllocMemory(c);
            else
                loop_var += generateAllocMemory(c);
            break;
        case operation::load:
            if(c.third()[0] == '-')
                var_table->linkRegister(c.second());
            else
                var_table->linkRegister(c.third());
            generateDirectMemoryOp("load", c);
            break;
        case operation::load_addr:
            if(c.third()[0] == '-')
                var_table->linkRegister(c.second());
            else
                var_table->linkRegister(c.third());
            generateIndirectMemoryOp("load", c);
            break;
        case operation::store:
            generateDirectMemoryOp("store", c);
            if(c.third()[0] == '-')
                var_table->unlinkRegister(c.second());
            else
                var_table->unlinkRegister(c.third());
            var_table->unlockRegister(c.first());
            break;
        case operation::store_addr:
            generateIndirectMemoryOp("store", c);
            if(c.third()[0] == '-')
                var_table->unlinkRegister(c.second());
            else
                var_table->unlinkRegister(c.third());
            var_table->unlockRegister(c.first());
            break;
        case operation::if_not:
            if(c.first()[0] == '$'){
                var_table->unlockRegister(c.first());
                *out << "not " << c.first() << endl;
                *out << "beq " << c.second() << endl;
            }
            else if(stoi(c.first()) == 0){
                *out << "jump " << c.second() << endl;
            }
            break;
        case operation::label:
            *out << c.first() << ":" << endl;
            if(c.first().find("WBEGIN") != string::npos){
                loop.push(loop_var);
                loop_var = 0;
            }
            else if(c.first().find("WEND") != string::npos){
                i = loop.size()-1;
                loop_var = loop[i];
                loop.remove(i);
                if(loop_var > 0){
                    *out << "subi $sp $sp " << loop_var << endl;
                    loop_var = 0;
                }
            }
            break;
        case operation::jump:
            *out << "jump " << c.first() << endl;
            break;
        case operation::noop:
            *out << "noop" << endl;
        }
    }
    return this->alist;
}