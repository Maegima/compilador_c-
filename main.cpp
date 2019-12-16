/**
 * @file main.cpp
 * @author André Lucas Maegima
 * @brief Compilador para a linguagem C-.
 * @version 1.0
 * @date 2019-12-10
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <iostream>
using namespace std;

#include "utils/globals.hpp"
#include "utils/Scanner.hpp"
#include "utils/Parser.hpp"
#include "utils/SymbolTable.hpp"
#include "utils/Semantic.hpp"
#include "utils/analyze.hpp"
#include "utils/cgen.hpp"

/* allocate global variables */
Scanner *scan = NULL;
Parser *parser = NULL;
FILE * source = NULL;
FILE * listing = stdout;
FILE * symbtab = stdout;
FILE * symbtree = stdout;
FILE * code = stdout;

/* allocate and set tracing flags */
int EchoSource = FALSE;
int TraceScan = FALSE;
int TraceParse = TRUE;
int TraceAnalyze = TRUE;
int TraceCode = FALSE;
int Error = FALSE;

int erro = 0; /**< Variável que indica erro na compilação. */

int main(int argc, char **argv){
    TreeNode *raiz;    
    cout << "\nParser em execução...\n"; 
    if(argc == 1) return 1;
        source = fopen(argv[1], "r");
    if(argc > 2)
        symbtree = fopen(argv[2], "w");
    if(argc > 3)
        symbtab = fopen(argv[3], "w");
    if(argc > 4)
        code = fopen(argv[4], "w");
    scan = new Scanner();
    parser = new Parser();
    raiz = parser->parse();
    if(!erro){
        raiz->print();
        SymbolTable *table = buildSymtab(raiz);
        Semantic *semantic = new Semantic(table, symbtab);
        erro = semantic->analyze();
    }
    if(!erro)
        codeGen(raiz, "code.txt");
    fclose(source);
    fclose(symbtab);
    fclose(symbtree);
    fclose(code);
    return 0;
}