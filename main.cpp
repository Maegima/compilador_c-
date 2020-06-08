/**
 * @file main.cpp
 * @author André Lucas Maegima
 * @brief Compilador para a linguagem C-.
 * @version 1.0
 * @date 2020-03-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <iostream>
using namespace std;

#include "utils/Scanner.hpp"
#include "utils/Parser.hpp"
#include "utils/SymbolTable.hpp"
#include "utils/Semantic.hpp"
#include "utils/CodeGenerator.hpp"

/* allocate global variables */
Scanner *scan = NULL; /**< Analisador léxico. */
Parser *parser = NULL; /**< Analisador sintático. */
FILE * source = NULL; /**< Arquivo do código fonte. */
FILE * listing = stdout; /**< Arquivo de saída padrão. */
FILE * symbtab = stdout; /**< Arquivo para impressão da tabela de simbolos. */
FILE * symbtree = stdout; /**< Arquivo para impressão da árvore sintática. */
FILE * code = stdout; /**< Arquivo para impressão do código intermediário. */

/* allocate and set tracing flags */
bool TraceScan = false;
bool TraceParse = true;
bool TraceAnalyze = true;
bool TraceCode = false;

int main(int argc, char **argv){
    int erro = 0; /**< Variável que indica erro na compilação. */
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
    scan = new Scanner(source, listing, TraceScan);
    parser = new Parser(symbtree, TraceParse);
    erro = parser->parse(&raiz);
    if(!erro){
        SymbolTable *table = new SymbolTable(symbtab, TraceAnalyze);
        table->build(raiz);
        Semantic *semantic = new Semantic(table, listing);
        erro = semantic->analyze();
    }
    if(!erro){
        CodeGenerator *codeGen = new CodeGenerator(code, TraceCode);
        codeGen->generate(raiz);
    }
    fclose(source);
    fclose(symbtab);
    fclose(symbtree);
    fclose(code);
    return 0;
}