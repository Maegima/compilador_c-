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
#include "utils/util.h"
#include "utils/scanner.hpp"
#include "utils/parse.h"
#include "utils/analyze.h"
#include "utils/cgen.h"

/* allocate global variables */
Scanner *scan = NULL;
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

extern int semantical(FILE *listing);

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
    raiz = parse();
    if(!erro){
        printTree(raiz);
        buildSymtab(raiz);
        erro = semantical(listing);
    }
    if(!erro)
        codeGen(raiz, "code.txt");
    fclose(source);
    fclose(symbtab);
    fclose(symbtree);
    fclose(code);
    return 0;
}