/**
 * @file Assembler.cpp
 * @author André Lucas Maegima
 * @brief Implementação da classe Assembler.
 * @version 1.6
 * @date 2020-06-29
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "Assembler.hpp"
#include <ext/stdio_filebuf.h>
#include <map>
#include <ostream>

using namespace std;

ostream *out_2;
__gnu_cxx::stdio_filebuf<char> *buff_out_2;

Assembler::Assembler(FILE *listing, bool trace) : listing(listing), trace(trace) {
    buff_out_2 = new __gnu_cxx::stdio_filebuf<char>(fileno(listing), std::ios::out);
    out_2 = new ostream(buff_out_2);
}

unsigned int Assembler::opex(string op){
    if(op == "add")        return 0x00000000;
    if(op == "sub")        return 0x00000001;
    if(op == "mult")       return 0x00000002;
    if(op == "div")        return 0x00000003;
    if(op == "or")         return 0x00000004;
    if(op == "nor")        return 0x00000005;
    if(op == "and")        return 0x00000006;
    if(op == "nand")       return 0x00000007;
    if(op == "xor")        return 0x00000008;
    if(op == "xnor")       return 0x00000009;
    if(op == "slt")        return 0x0000000A;
    if(op == "sgt")        return 0x0000000B;
    if(op == "equal")      return 0x0000000C;
    if(op == "rshift")     return 0x0000000D;
    if(op == "lshift")     return 0x0000000E;
    if(op == "different")  return 0x0000000F;
    if(op == "move")       return 0x00000010;
    if(op == "not")        return 0x00000011;
    if(op == "mult2")      return 0x00000012;
    if(op == "div2")       return 0x00000013;
    if(op == "movetm")     return 0x00000014;
    if(op == "movetp")     return 0x00000015;
    if(op == "movehi")     return 0x00000016;
    if(op == "movelo")     return 0x00000017;
    if(op == "jumpr")      return 0x00000018;
    if(op == "beqr")       return 0x00000019;
    if(op == "slt2")       return 0x0000001A;
    if(op == "sgt2")       return 0x0000001B;
    if(op == "equal2")     return 0x0000001C;
    if(op == "different2") return 0x0000001F;
    return 0x00000000;
}

unsigned int Assembler::opcode(string op){
    if(op == "addi")      return 0x00000000;
    if(op == "subi")      return 0x04000000;
    if(op == "multi")     return 0x08000000;
    if(op == "divi")      return 0x0C000000;
    if(op == "ori")       return 0x10000000;
    if(op == "nori")      return 0x14000000;
    if(op == "andi")      return 0x18000000;
    if(op == "nandi")     return 0x1C000000;
    if(op == "xori")      return 0x20000000;
    if(op == "xnori")     return 0x24000000;
    if(op == "slti")      return 0x28000000;
    if(op == "sgti")      return 0x2C000000;
    if(op == "equali")    return 0x30000000;
    if(op == "rshifti")   return 0x34000000;
    if(op == "lshifti")   return 0x38000000;
    if(op == "diffrenti") return 0x3C000000;
    if(op == "set")       return 0x40000000;
    if(op == "multi2")    return 0x44000000;
    if(op == "divi2")     return 0x48000000;
    if(op == "slti2")     return 0x68000000;
    if(op == "sgti2")     return 0x6C000000;
    if(op == "equali2")   return 0x70000000;
    if(op == "diferent2") return 0x7C000000;
    if(op == "load")      return 0x80000000;
    if(op == "push")      return 0x8C000000;
    if(op == "store")     return 0x90000000;
    if(op == "pop")       return 0x9C000000;
    if(op == "jump")      return 0xC0000000;
    if(op == "beq")       return 0xC4000000;
    if(op == "jal")       return 0xC8000000;
    if(op == "jaunl")     return 0xCC000000;
    if(op == "delay")     return 0xE0000000;
    if(op == "set_delay") return 0xE4000000;
    if(op == "input")     return 0xF0000000;
    if(op == "output")    return 0xF4000000;
    return 0xFC000000;
}

unsigned int Assembler::registerToNumber(string reg){
    if(trace)
        *out_2 << "register " << reg << endl;
    if(reg.size() < 2) return 0;
    if(reg == "$sp") return 29;
    if(reg == "$fp") return 28;
    if(reg[0] == '$'){
        if(reg[1] == 't')
            return stoi(reg.substr(2)) + 1;
        else
            return stoi(reg.substr(1));
    }
    return 0;
}

unsigned int Assembler::imediate16(string num){
    unsigned int im;
    if(trace)
        *out_2 << "imediate16 " << num << endl;
    if(num[0] == '-'){
        im = 0x00007FFF & stoi(num.substr(1));
        return 0x00008000 | im;
    }
    im = 0x00007FFF & stoi(num);
    return im;
}

unsigned int Assembler::imediate21(string num){
    unsigned int im;
    if(trace)
        *out_2 << "imediate21 " << num << endl;
    if(num[0] == '-'){
        im = 0x000FFFFF & stoi(num.substr(1));
        return 0x00100000 | im;
    }
    im = 0x000FFFFF & stoi(num);
    return im;
}

unsigned int Assembler::address21(string num){
    if(trace)
        *out_2 << "address21 " << num << endl;
    return 0x001FFFFF & stoi(num);
}

unsigned int Assembler::address26(string num){
    if(trace)
        *out_2 << "address26 " << num << endl;
    return 0x001FFFFF & stoi(num);
}

string Assembler::toBin(unsigned int code){
    char out[38];
    out[37] = 0;
    for(int i = 36; i > -1; i--){
        if(code % 2) out[i] = '1';
        else out[i] = '0';
        if(i == 6 || i == 12 || i == 18 || i == 24 || i == 31) 
            out[i] = ' ';
        else
            code = code >> 1;
    }
    return string(out);
}

string Assembler::toHex(unsigned int code){
    char out[9];
    out[8] = 0;
    char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    for(int i = 0; i < 8; i++){
        int index;
        index = 0x0000000F & (code >> (i*4));
        out[7-i] = hex[index];
    }
    return string(out);
}

LinkedList<unsigned int> Assembler::generate(LinkedList<Code> *alist){
    size_t addr = 0;
    unsigned int code, extended;
    map<string, int> label;
    LinkedList<unsigned int> mlist;
    LinkedList<Code> acode;
    for(Code c : *alist){
        size_t index = c.op().find(':');
        if(index != string::npos){
            label[c.op().substr(0, index)] = 0x03FFFFFF & addr;
        }
        else{
            acode.push(c);
            addr++;
        }
    }
    if(trace)
        for(pair<string, int> a : label)
            *out_2 << a.first << "=" << a.second << "(" << toHex(a.second) << ")" << endl;
    for(Code c : acode){
        if(trace)
            *out_2 << c.op() << endl;
        code = opcode(c.op());
        if(code == 0xFC000000){
            extended = opex(c.op());
            code += extended;
            code += registerToNumber(c.first()) << 21;
            code += registerToNumber(c.second()) << 16;
            if(extended < 0x00000010){
                code += registerToNumber(c.third()) << 11;
            }
        }
        else if(code < 0x40000000){
            code += registerToNumber(c.first()) << 21;
            code += registerToNumber(c.second()) << 16;
            code += imediate16(c.third());
        }
        else if(c.op() == "load" || c.op() == "store"){
            code += registerToNumber(c.first()) << 21;
            if(c.third() == ""){
                code += address21(c.second());       
            }
            else{
                code += 0x20000000;
                code += registerToNumber(c.second()) << 16;
                code += imediate16(c.third());
            }
        }
        else if(code > 0xE0000000){
            code += registerToNumber(c.first()) << 21;
        }
        else if(code > 0xBC000000){
            code += label[c.first()];
        }
        else if(code > 0x30000000){
            code += registerToNumber(c.first()) << 21;
            if(c.second() != "")
                code += imediate21(c.second());
        }
        if(trace)
            *out_2 << toBin(code) << endl;
        else
            *out_2 << toHex(code) << endl;
        mlist.push(code);
    }
    return mlist;
}