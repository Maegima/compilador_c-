#include <iostream>
using namespace std;

#include "utils/globals.h"
#include "utils/util.h"
#include "utils/scan.h"
#include "utils/parse.h"
#include "utils/analyze.h"
#include "utils/cgen.h"

/** allocate global variables */
int line_counter = 0;
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

extern void abrirArq(char *arq);
extern void fecharArq();
extern int semantical(FILE *listing);

int erro = 0; /**< Váravel que indica erro na compilação */

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
    return 0;
}