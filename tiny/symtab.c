/****************************************************/
/* File: symtab.c                                   */
/* Symbol table implementation for the TINY compiler*/
/* (allows only one symbol table)                   */
/* Symbol table is implemented as a chained         */
/* hash table                                       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

/* SIZE is the size of the hash table */
#define SIZE 211

/* SHIFT is the power of two used as multiplier
   in hash function  */
#define SHIFT 4

/* the hash function */
static int hash ( char * key )
{ int temp = 0;
  int i = 0;
  while (key[i] != '\0')
  { temp = ((temp << SHIFT) + key[i]) % SIZE;
    ++i;
  }
  return temp;
}

/* the list of line numbers of the source 
 * code in which a variable is referenced
 */
typedef struct LineListRec
   { int lineno;
     struct LineListRec * next;
   } * LineList;

/* The record in the bucket lists for
 * each variable, including name, 
 * assigned memory location, and
 * the list of line numbers in which
 * it appears in the source code
 */
typedef struct BucketListRec
   { char * name;
     LineList lines;
     LineList decl_line;
     int memloc ; /* memory location for variable */
     struct BucketListRec * next;
   } * BucketList;

/* the hash table */
static BucketList hashTable[SIZE];

/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void st_insert( char * name, int lineno, int decl_line, int loc )
{ int h = hash(name);
  BucketList l =  hashTable[h];
  while ((l != NULL) && (strcmp(name,l->name) != 0))
    l = l->next;
  if (l == NULL) /* variable not yet in table */
  { l = (BucketList) malloc(sizeof(struct BucketListRec));
    l->name = name;
    l->lines = (LineList) malloc(sizeof(struct LineListRec));
    l->lines->lineno = lineno;
    l->memloc = loc;
    l->lines->next = NULL;
    if(decl_line > -1){
        l->decl_line = (LineList) malloc(sizeof(struct LineListRec));
        l->decl_line->lineno = decl_line;
        l->decl_line->next = NULL;
    }
    else l->decl_line = NULL;
    l->next = hashTable[h];
    hashTable[h] = l; }
  else /* found in table, so just add line number */
  { LineList t = l->lines;
    while (t->next != NULL) t = t->next;
    t->next = (LineList) malloc(sizeof(struct LineListRec));
    t->next->lineno = lineno;
    t->next->next = NULL;
    if(decl_line > -1){
        LineList p;
        p = (LineList) malloc(sizeof(struct LineListRec));
        p->lineno = decl_line;
        p->next = NULL;
        t = l->decl_line;
        if(t != NULL){
            while (t->next != NULL) t = t->next;
            t->next = p;
        }
        else l->decl_line = p;
        

        //t = l->decl_line;
        //while (t != NULL){ 
        //    printf("%d ", t->lineno);
        //    t = t->next;
        //}
        //printf("\n");
    }
  }
} /* st_insert */

/* Function st_lookup returns the memory 
 * location of a variable or -1 if not found
 */
int st_lookup ( char * name )
{ int h = hash(name);
  BucketList l =  hashTable[h];
  while ((l != NULL) && (strcmp(name,l->name) != 0))
    l = l->next;
  if (l == NULL) return -1;
  else return l->memloc;
}

/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(FILE * listing)
{ int i, padding = 2, count;
  for (i=0;i<SIZE;++i)
  { if (hashTable[i] != NULL)
    { BucketList l = hashTable[i];
      while (l != NULL)
      { 
        count = 0;
        LineList s = l->decl_line;
        while (s != NULL){
            count++;
            s = s->next;
        }
        padding = (count > padding) ? count : padding;
        l = l->next;
      }
    }
  }
  fprintf(listing,"Variable Name  Location  Declaration");
  for(int j = 2; j < padding; j++) fprintf(listing, "     "); 
  fprintf(listing, "  Line Numbers\n");
  fprintf(listing,"-------------  --------  -----------");
  for(int j = 2; j < padding; j++) fprintf(listing, "-----");
  fprintf(listing,"  -------------\n");
  for (i=0;i<SIZE;++i)
  { if (hashTable[i] != NULL)
    { BucketList l = hashTable[i];
      while (l != NULL)
      { 
        LineList t = l->lines;
        LineList r = l->decl_line;
        fprintf(listing,"%-14s ",l->name);
        fprintf(listing,"%-8d  ",l->memloc);
        for(int j = 0; j < padding; j++){
            if(r != NULL){
                fprintf(listing, "%-4d ", r->lineno);
                r = r->next;
            }
            else{
                fprintf(listing, "     ");
            }
        }
        fprintf(listing, " ");
        while (t != NULL)
        { fprintf(listing,"%4d ",t->lineno);
          t = t->next;
        }
        fprintf(listing,"\n");
        l = l->next;
      }
    }
  }
} /* printSymTab */
