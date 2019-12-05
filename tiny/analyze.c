/****************************************************/
/* File: analyze.c                                  */
/* Semantic analyzer implementation                 */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "analyze.h"

/* counter for variable memory locations */
static int location = 0;

/* Procedure traverse is a generic recursive 
 * syntax tree traversal routine:
 * it applies preProc in preorder and postProc 
 * in postorder to tree pointed to by t
 */
static void traverse( TreeNode * t,
               void (* preProc) (TreeNode *),
               void (* postProc) (TreeNode *) )
{ if (t != NULL)
  { preProc(t);
    { int i;
      for (i=0; i < MAXCHILDREN; i++)
        traverse(t->child[i],preProc,postProc);
    }
    postProc(t);
    traverse(t->sibling,preProc,postProc);
  }
}

/* nullProc is a do-nothing procedure to 
 * generate preorder-only or postorder-only
 * traversals from traverse
 */
static void nullProc(TreeNode * t)
{ if (t==NULL) return;
  else return;
}

char *idScopeName(const char* scope, const char *name){
    char *scopeName;
    int len1, len2;
    len1 = strlen(scope);
    len2 = strlen(name);
    scopeName = (char*) malloc(sizeof(char)*(len1+len2+2));
    memcpy(scopeName, scope, len1);
    memcpy(scopeName+len1, " ", 1);
    memcpy(scopeName+len1+1, name, len2+1);
    return scopeName;
}

/* Procedure insertNode inserts 
 * identifiers stored in t into 
 * the symbol table 
 */
static void insertNode( TreeNode * t){ 
    char *name;
    int n;
    switch (t->nodekind){ 
        case StmtK:
        switch (t->kind.stmt){ 
            case AssignK:
            // name = idScopeName(name, t->attr.name);
            // if (st_lookup(name) == -1)
            // /* not yet in table, so treat as new definition */
            //     st_insert(name,t->lineno,location++);
            // else{
            // /* already in table, so ignore location, 
            //     add line number of use only */ 
            //     st_insert(name,t->lineno,0);
            //     free(name);
            // }
            break;
            case ReturnK:
            case IfK:
            case WhileK:
            default: break;
        }
        break;
        case ExpK:
        switch (t->kind.exp){ 
            case IdK:
                name = idScopeName(t->scope, t->attr.name);
                if (st_lookup(name) == -1)
                /* not yet in table, so treat as new definition */
                    st_insert(name,t->lineno,t->decl_line,location++);
                else
                /* already in table, so ignore location, 
                    add line number of use only */ 
                    st_insert(name,t->lineno,t->decl_line,0);
            break;
            case ConstK:
            case TypeK:
            case OpK:
            default: break;
        }
        break;
        default: break;
    }
}

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode * syntaxTree)
{ 
    traverse(syntaxTree,insertNode,nullProc);
    if (TraceAnalyze)
    { 
        fprintf(listing,"\nSymbol table:\n\n");
        printSymTab(listing);
    }
}

static void typeError(TreeNode * t, char * message)
{ fprintf(listing,"Type error at line %d: %s\n",t->lineno,message);
  Error = TRUE;
}

/* Procedure checkNode performs
 * type checking at a single tree node
 */
static void checkNode(TreeNode * t)
{ switch (t->nodekind)
  { case ExpK:
      switch (t->kind.exp)
      { case OpK:
          if ((t->child[0]->type != Integer) ||
              (t->child[1]->type != Integer))
            typeError(t,"Op applied to non-integer");
          if ((t->attr.op == EQUAL) || (t->attr.op == SLT))
            t->type = Integer;
          else
            t->type = Integer;
          break;
        case ConstK:
        case IdK:
          t->type = Integer;
          break;
        default:
          break;
      }
      break;
    case StmtK:
      switch (t->kind.stmt)
      { case IfK:
          if (t->child[0]->type == Integer)
            typeError(t->child[0],"if test is not Boolean");
          break;
        case AssignK:
          if (t->child[0]->type != Integer)
            typeError(t->child[0],"assignment of non-integer value");
          break;
        case WhileK:
          if (t->child[1]->type == Integer)
            typeError(t->child[1],"repeat test is not Boolean");
          break;
        default:
          break;
      }
      break;
    default:
      break;

  }
}

/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode * syntaxTree)
{ traverse(syntaxTree,nullProc,checkNode);
}
