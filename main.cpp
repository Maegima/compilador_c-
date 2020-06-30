/**
 * @file main.cpp
 * @author André Lucas Maegima
 * @brief Compilador para a linguagem C-.
 * @version 2.0
 * @date 2020-06-30
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <iostream>
using namespace std;

#include "analysis/Scanner.hpp"
#include "analysis/Parser.hpp"
#include "analysis/SymbolTable.hpp"
#include "analysis/Semantic.hpp"
#include "synthesis/CodeGenerator.hpp"
#include "synthesis/AssemblyGenerator.hpp"
#include "synthesis/Assembler.hpp"

/* allocate global variables */
Scanner *scan = NULL; /**< Analisador léxico. */
Parser *parser = NULL; /**< Analisador sintático. */
FILE * source = NULL; /**< Arquivo do código fonte. */
FILE * listing = stdout; /**< Arquivo de saída padrão. */
FILE * symbtab = stdout; /**< Arquivo para impressão da tabela de simbolos. */
FILE * symbtree = stdout; /**< Arquivo para impressão da árvore sintática. */
FILE * code = stdout; /**< Arquivo para impressão do código intermediário. */
FILE * assembly = stdout; /**< Arquivo para impressão do código assembly. */
FILE * machine = stdout; /**< Arquivo para impressão do código de máquina. */

/* allocate and set tracing flags */
bool TraceScan = false;
bool TraceParse = true;
bool TraceAnalyze = true;
bool TraceCode = false;
bool TraceAssembly = false;
bool TraceMachine = false;

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
    if(argc > 5)
        assembly = fopen(argv[5], "w");
    if(argc > 6)
        machine = fopen(argv[6], "w");
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
        LinkedList<Code> *clist = codeGen->generate(raiz);
        AssemblyGenerator *asmbGen = new AssemblyGenerator(assembly, TraceAssembly);
        LinkedList<Code> *alist = asmbGen->generate(clist);
        Assembler *machineGen = new Assembler(machine, TraceMachine);
        LinkedList<unsigned int> mlist = machineGen->generate(alist);
    }
    fclose(source);
    fclose(symbtab);
    fclose(symbtree);
    fclose(code);
    return 0;
}