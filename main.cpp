#include <iostream>
using namespace std;

extern void abrirArq(char *arq);
extern void fecharArq();
#include "utils/globals.h"

/* set NO_PARSE to TRUE to get a scanner-only compiler */
#define NO_PARSE FALSE
/* set NO_ANALYZE to TRUE to get a parser-only compiler */
#define NO_ANALYZE FALSE

/* set NO_CODE to TRUE to get a compiler that does not
 * generate code
 */
#define NO_CODE FALSE

#include "utils/util.h"
#if NO_PARSE
#include "utils/scan.h"
#else
#include "utils/parse.h"
#if !NO_ANALYZE
#include "utils/analyze.h"
#if !NO_CODE
#include "utils/cgen.h"
#endif
#endif
#endif

/* allocate global variables */
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

extern int semantical(FILE *listing);
int erro = 0;


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