/* A Bison parser, made by GNU Bison 3.6.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.6.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "Parser.y"

/**
 * @file Parser.cpp
 * @author André Lucas Maegima
 * @brief Implementação do analisador sintático.
 * @version 2.0
 * @date 2020-07-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <iostream>
using namespace std;

#define YYPARSER /* distinguishes Yacc output from other code files */

#include "Scanner.hpp"
#include "Parser.hpp"

#define YYSTYPE TreeNode *
static int sc;
static int func_id;
static string **func;
static ExpType *type;
static string *str_global;
static string *scope;

int yylex(void);
void yyerror(const char *msg);
extern char* yytext;
extern Parser *parser;
extern Scanner *scan;

#line 105 "analysis/Parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IF = 258,                      /* IF  */
    ELSE = 259,                    /* ELSE  */
    WHILE = 260,                   /* WHILE  */
    INT = 261,                     /* INT  */
    VOID = 262,                    /* VOID  */
    RETURN = 263,                  /* RETURN  */
    ADD = 264,                     /* ADD  */
    SUB = 265,                     /* SUB  */
    MULT = 266,                    /* MULT  */
    DIV = 267,                     /* DIV  */
    SLT = 268,                     /* SLT  */
    SLTE = 269,                    /* SLTE  */
    SGT = 270,                     /* SGT  */
    SGTE = 271,                    /* SGTE  */
    EQUAL = 272,                   /* EQUAL  */
    DIFFERENT = 273,               /* DIFFERENT  */
    ATRIB = 274,                   /* ATRIB  */
    OPAREN = 275,                  /* OPAREN  */
    CPAREN = 276,                  /* CPAREN  */
    OBRACT = 277,                  /* OBRACT  */
    CBRACT = 278,                  /* CBRACT  */
    OBRACE = 279,                  /* OBRACE  */
    CBRACE = 280,                  /* CBRACE  */
    ID = 281,                      /* ID  */
    NUM = 282,                     /* NUM  */
    SEMICOLON = 283,               /* SEMICOLON  */
    COMMA = 284,                   /* COMMA  */
    OCOM = 285,                    /* OCOM  */
    CCOM = 286,                    /* CCOM  */
    COM = 287,                     /* COM  */
    ERR = 288                      /* ERR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_WHILE = 5,                      /* WHILE  */
  YYSYMBOL_INT = 6,                        /* INT  */
  YYSYMBOL_VOID = 7,                       /* VOID  */
  YYSYMBOL_RETURN = 8,                     /* RETURN  */
  YYSYMBOL_ADD = 9,                        /* ADD  */
  YYSYMBOL_SUB = 10,                       /* SUB  */
  YYSYMBOL_MULT = 11,                      /* MULT  */
  YYSYMBOL_DIV = 12,                       /* DIV  */
  YYSYMBOL_SLT = 13,                       /* SLT  */
  YYSYMBOL_SLTE = 14,                      /* SLTE  */
  YYSYMBOL_SGT = 15,                       /* SGT  */
  YYSYMBOL_SGTE = 16,                      /* SGTE  */
  YYSYMBOL_EQUAL = 17,                     /* EQUAL  */
  YYSYMBOL_DIFFERENT = 18,                 /* DIFFERENT  */
  YYSYMBOL_ATRIB = 19,                     /* ATRIB  */
  YYSYMBOL_OPAREN = 20,                    /* OPAREN  */
  YYSYMBOL_CPAREN = 21,                    /* CPAREN  */
  YYSYMBOL_OBRACT = 22,                    /* OBRACT  */
  YYSYMBOL_CBRACT = 23,                    /* CBRACT  */
  YYSYMBOL_OBRACE = 24,                    /* OBRACE  */
  YYSYMBOL_CBRACE = 25,                    /* CBRACE  */
  YYSYMBOL_ID = 26,                        /* ID  */
  YYSYMBOL_NUM = 27,                       /* NUM  */
  YYSYMBOL_SEMICOLON = 28,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 29,                     /* COMMA  */
  YYSYMBOL_OCOM = 30,                      /* OCOM  */
  YYSYMBOL_CCOM = 31,                      /* CCOM  */
  YYSYMBOL_COM = 32,                       /* COM  */
  YYSYMBOL_ERR = 33,                       /* ERR  */
  YYSYMBOL_YYACCEPT = 34,                  /* $accept  */
  YYSYMBOL_programa = 35,                  /* programa  */
  YYSYMBOL_declaracao_lista = 36,          /* declaracao_lista  */
  YYSYMBOL_declaracao = 37,                /* declaracao  */
  YYSYMBOL_var_declaracao = 38,            /* var_declaracao  */
  YYSYMBOL_identificador = 39,             /* identificador  */
  YYSYMBOL_numero = 40,                    /* numero  */
  YYSYMBOL_tipo_especificador = 41,        /* tipo_especificador  */
  YYSYMBOL_fun_declaracao = 42,            /* fun_declaracao  */
  YYSYMBOL_params = 43,                    /* params  */
  YYSYMBOL_param_lista = 44,               /* param_lista  */
  YYSYMBOL_param = 45,                     /* param  */
  YYSYMBOL_composto_decl = 46,             /* composto_decl  */
  YYSYMBOL_local_declaracoes = 47,         /* local_declaracoes  */
  YYSYMBOL_statement_lista = 48,           /* statement_lista  */
  YYSYMBOL_statement = 49,                 /* statement  */
  YYSYMBOL_expressao_decl = 50,            /* expressao_decl  */
  YYSYMBOL_selecao_decl = 51,              /* selecao_decl  */
  YYSYMBOL_iteracao_decl = 52,             /* iteracao_decl  */
  YYSYMBOL_retorno_decl = 53,              /* retorno_decl  */
  YYSYMBOL_expressao = 54,                 /* expressao  */
  YYSYMBOL_var = 55,                       /* var  */
  YYSYMBOL_simples_expressao = 56,         /* simples_expressao  */
  YYSYMBOL_relacional = 57,                /* relacional  */
  YYSYMBOL_soma_expressao = 58,            /* soma_expressao  */
  YYSYMBOL_soma = 59,                      /* soma  */
  YYSYMBOL_termo = 60,                     /* termo  */
  YYSYMBOL_mult = 61,                      /* mult  */
  YYSYMBOL_fator = 62,                     /* fator  */
  YYSYMBOL_ativacao = 63,                  /* ativacao  */
  YYSYMBOL_args = 64,                      /* args  */
  YYSYMBOL_arg_lista = 65                  /* arg_lista  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   103

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  106

#define YYMAXUTOK   288


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
  /* YYRLINEYYN -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    53,    53,    55,    66,    68,    68,    70,    77,    86,
      98,   105,   111,   118,   132,   132,   134,   145,   147,   154,
     162,   174,   185,   187,   198,   200,   201,   202,   203,   204,
     206,   207,   209,   215,   223,   230,   230,   236,   245,   247,
     252,   259,   266,   268,   273,   278,   283,   288,   293,   299,
     306,   308,   313,   319,   326,   328,   333,   339,   340,   341,
     342,   344,   358,   373,   373,   375,   386
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "WHILE",
  "INT", "VOID", "RETURN", "ADD", "SUB", "MULT", "DIV", "SLT", "SLTE",
  "SGT", "SGTE", "EQUAL", "DIFFERENT", "ATRIB", "OPAREN", "CPAREN",
  "OBRACT", "CBRACT", "OBRACE", "CBRACE", "ID", "NUM", "SEMICOLON",
  "COMMA", "OCOM", "CCOM", "COM", "ERR", "$accept", "programa",
  "declaracao_lista", "declaracao", "var_declaracao", "identificador",
  "numero", "tipo_especificador", "fun_declaracao", "params",
  "param_lista", "param", "composto_decl", "local_declaracoes",
  "statement_lista", "statement", "expressao_decl", "selecao_decl",
  "iteracao_decl", "retorno_decl", "expressao", "var", "simples_expressao",
  "relacional", "soma_expressao", "soma", "termo", "mult", "fator",
  "ativacao", "args", "arg_lista", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288
};
#endif

#define YYPACT_NINF (-91)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-16)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACTSTATE-NUM -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      54,   -91,   -91,     3,    54,   -91,   -91,    -8,   -91,   -91,
     -91,   -91,   -13,    62,   -19,   -91,     1,    -8,    10,    11,
     -91,   -91,    35,    40,    51,    54,    48,    55,   -91,   -91,
     -91,   -91,   -91,    54,   -91,    -8,     8,   -18,    57,    59,
      37,    23,   -91,   -91,    19,   -91,   -91,   -91,   -91,   -91,
     -91,   -91,    52,    63,   -91,    38,    60,   -91,   -91,    23,
      23,   -91,    53,    65,    23,    23,   -91,    23,   -91,   -91,
     -91,   -91,   -91,   -91,   -91,   -91,    23,    23,   -91,   -91,
      23,    66,    67,   -91,   -91,   -91,    68,    69,    56,    61,
     -91,   -91,    64,    60,   -91,    18,    18,   -91,   -91,    23,
     -91,    79,   -91,   -91,    18,   -91
};

  /* YYDEFACTSTATE-NUM -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    11,    12,     0,     2,     4,     5,     0,     6,     1,
       3,     9,     0,     0,     0,     7,    12,     0,     0,    14,
      17,    10,     0,    18,     0,     0,     0,     0,    22,    13,
      16,     8,    19,    24,    21,     0,     0,     0,     0,     0,
       0,     0,    20,    31,    39,    60,    26,    23,    25,    27,
      28,    29,     0,    58,    38,    42,    50,    54,    59,     0,
       0,    35,     0,     0,    64,     0,    30,     0,    51,    52,
      44,    43,    45,    46,    47,    48,     0,     0,    55,    56,
       0,     0,     0,    36,    57,    66,    38,     0,    63,     0,
      37,    58,    41,    49,    53,     0,     0,    61,    62,     0,
      40,    32,    34,    65,     0,    33
};

  /* YYPGOTONTERM-NUM.  */
static const yytype_int8 yypgoto[] =
{
     -91,   -91,   -91,    87,    70,    -5,    78,     4,   -91,   -91,
     -91,    71,    73,   -91,   -91,   -90,   -91,   -91,   -91,   -91,
     -40,   -10,    29,   -91,    22,   -91,    17,   -91,    15,   -91,
     -91,   -91
};

  /* YYDEFGOTONTERM-NUM.  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    44,    45,     7,     8,    18,
      19,    20,    46,    33,    36,    47,    48,    49,    50,    51,
      52,    53,    54,    76,    55,    77,    56,    80,    57,    58,
      87,    88
};

  /* YYTABLEYYPACT[STATE-NUM] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      62,    63,    12,     9,    14,   101,   102,    13,    21,    14,
      15,    38,    23,    39,   105,    15,    40,    17,    11,    81,
      82,    38,   -15,    39,    85,    89,    40,    90,    41,    17,
      37,    24,    28,    42,    11,    21,    43,    35,    41,    64,
      25,    65,    28,    41,    11,    21,    43,    68,    69,    11,
      21,    70,    71,    72,    73,    74,    75,    41,    26,   103,
       1,     2,    27,    11,    21,    61,    91,    91,     1,    16,
      91,    78,    79,    68,    69,    28,    31,    59,    32,    60,
      66,    83,    67,   104,   100,    99,    84,    95,    96,    97,
      98,    10,    22,    86,    93,    94,    30,    29,    92,     0,
       0,     0,     0,    34
};

static const yytype_int8 yycheck[] =
{
      40,    41,     7,     0,    22,    95,    96,    20,    27,    22,
      28,     3,    17,     5,   104,    28,     8,    13,    26,    59,
      60,     3,    21,     5,    64,    65,     8,    67,    20,    25,
      35,    21,    24,    25,    26,    27,    28,    33,    20,    20,
      29,    22,    24,    20,    26,    27,    28,     9,    10,    26,
      27,    13,    14,    15,    16,    17,    18,    20,    23,    99,
       6,     7,    22,    26,    27,    28,    76,    77,     6,     7,
      80,    11,    12,     9,    10,    24,    28,    20,    23,    20,
      28,    28,    19,     4,    23,    29,    21,    21,    21,    21,
      21,     4,    14,    64,    77,    80,    25,    24,    76,    -1,
      -1,    -1,    -1,    33
};

  /* YYSTOSSTATE-NUM -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,     7,    35,    36,    37,    38,    41,    42,     0,
      37,    26,    39,    20,    22,    28,     7,    41,    43,    44,
      45,    27,    40,    39,    21,    29,    23,    22,    24,    46,
      45,    28,    23,    47,    38,    41,    48,    39,     3,     5,
       8,    20,    25,    28,    39,    40,    46,    49,    50,    51,
      52,    53,    54,    55,    56,    58,    60,    62,    63,    20,
      20,    28,    54,    54,    20,    22,    28,    19,     9,    10,
      13,    14,    15,    16,    17,    18,    57,    59,    11,    12,
      61,    54,    54,    28,    21,    54,    56,    64,    65,    54,
      54,    55,    58,    60,    62,    21,    21,    21,    21,    29,
      23,    49,    49,    54,     4,    49
};

  /* YYR1YYN -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    34,    35,    36,    36,    37,    37,    38,    38,    39,
      40,    41,    41,    42,    43,    43,    44,    44,    45,    45,
      46,    47,    47,    48,    48,    49,    49,    49,    49,    49,
      50,    50,    51,    51,    52,    53,    53,    54,    54,    55,
      55,    56,    56,    57,    57,    57,    57,    57,    57,    58,
      58,    59,    59,    60,    60,    61,    61,    62,    62,    62,
      62,    63,    63,    64,    64,    65,    65
};

  /* YYR2YYN -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     6,     1,
       1,     1,     1,     6,     1,     1,     3,     1,     2,     4,
       4,     2,     0,     2,     0,     1,     1,     1,     1,     1,
       2,     1,     5,     7,     5,     2,     3,     3,     1,     1,
       4,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     4,     4,     1,     0,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize;

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yynerrs = 0;
  yystate = 0;
  yyerrstatus = 0;

  yystacksize = YYINITDEPTH;
  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;


  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 53 "Parser.y"
                           { parser->setSavedTree(yyvsp[0]); }
#line 1308 "analysis/Parser.cpp"
    break;

  case 3:
#line 56 "Parser.y"
{ 
    YYSTYPE t = yyvsp[-1];
    if (t != NULL) { 
        while (t->getSibling() != NULL)
            t = t->getSibling();
        t->setSibling(yyvsp[0]);
        yyval = yyvsp[-1]; 
    }
    else yyval = yyvsp[0];
}
#line 1323 "analysis/Parser.cpp"
    break;

  case 4:
#line 66 "Parser.y"
             { yyval = yyvsp[0]; }
#line 1329 "analysis/Parser.cpp"
    break;

  case 5:
#line 68 "Parser.y"
                           { sc = 1; yyval = yyvsp[0]; }
#line 1335 "analysis/Parser.cpp"
    break;

  case 6:
#line 68 "Parser.y"
                                                                 { sc = 1; yyval = yyvsp[0]; }
#line 1341 "analysis/Parser.cpp"
    break;

  case 7:
#line 71 "Parser.y"
{
    yyval = yyvsp[-2];
    yyvsp[-1]->setExp((ExpKind)(DeclK | IdK));
    yyval->setChild(yyvsp[-1], 0);
    yyvsp[-1]->setType(yyvsp[-2]->getType());
}
#line 1352 "analysis/Parser.cpp"
    break;

  case 8:
#line 78 "Parser.y"
{ 
    yyval = yyvsp[-5];
    yyvsp[-4]->setExp((ExpKind)(DeclK | IdK));
    yyval->setChild(yyvsp[-4], 0);
    yyval->getChild(0)->setChild(yyvsp[-2], 0);
    yyvsp[-4]->setType(yyvsp[-5]->getType());
}
#line 1364 "analysis/Parser.cpp"
    break;

  case 9:
#line 87 "Parser.y"
{ 
    yyval = new TreeNode(IdK);
    yyval->setName(new string(yytext));
    if(sc){
        scope = yyval->getName();
        yyval->setScope(str_global);
        sc = 0;
    }
    else yyval->setScope(scope);
}
#line 1379 "analysis/Parser.cpp"
    break;

  case 10:
#line 99 "Parser.y"
{ 
    yyval = new TreeNode(ConstK);
    yyval->setVal(atoi(yytext));
    yyval->setType(Integer);
}
#line 1389 "analysis/Parser.cpp"
    break;

  case 11:
#line 106 "Parser.y"
{ 
    yyval = new TreeNode(TypeK);
    yyval->setName(new string("INT"));
    yyval->setType(Integer);
}
#line 1399 "analysis/Parser.cpp"
    break;

  case 12:
#line 112 "Parser.y"
{ 
    yyval = new TreeNode(TypeK);
    yyval->setName(new string("VOID"));
    yyval->setType(Void);
}
#line 1409 "analysis/Parser.cpp"
    break;

  case 13:
#line 119 "Parser.y"
{
    yyval = yyvsp[-5];
    yyval->setChild(yyvsp[-4], 0);
    yyval->getChild(0)->setChild(yyvsp[-2], 0);
    yyval->getChild(0)->setChild(yyvsp[0], 1);
    yyvsp[-4]->setLineno(yyvsp[-4]->getLineno());
    yyvsp[-4]->setType(yyvsp[-5]->getType());
    yyvsp[-4]->setExp((ExpKind)(FuncK | DeclK));
    func[func_id] = yyvsp[-4]->getName();
    type[func_id] = yyvsp[-4]->getType();
    func_id++;
}
#line 1426 "analysis/Parser.cpp"
    break;

  case 14:
#line 132 "Parser.y"
                    { yyval = yyvsp[0]; }
#line 1432 "analysis/Parser.cpp"
    break;

  case 15:
#line 132 "Parser.y"
                                        { yyval = NULL; }
#line 1438 "analysis/Parser.cpp"
    break;

  case 16:
#line 135 "Parser.y"
{ 
   YYSTYPE t = yyvsp[-2];
    if (t != NULL) { 
        while (t->getSibling() != NULL)
            t = t->getSibling();
        t->setSibling(yyvsp[0]);
        yyval = yyvsp[-2]; 
    }
    else yyval = yyvsp[0];
}
#line 1453 "analysis/Parser.cpp"
    break;

  case 17:
#line 145 "Parser.y"
        { yyval = yyvsp[0]; }
#line 1459 "analysis/Parser.cpp"
    break;

  case 18:
#line 148 "Parser.y"
{  
    yyval = yyvsp[-1];
    yyvsp[0]->setExp((ExpKind)(ParamK | DeclK));
    yyval->setChild(yyvsp[0], 0);
    yyvsp[0]->setType(yyvsp[-1]->getType());
}
#line 1470 "analysis/Parser.cpp"
    break;

  case 19:
#line 155 "Parser.y"
{ 
    yyval = yyvsp[-3];
    yyvsp[-2]->setExp((ExpKind)(ParamK | DeclK));
    yyval->setChild(yyvsp[-2], 0);
    yyvsp[-2]->setType(yyvsp[-3]->getType());
}
#line 1481 "analysis/Parser.cpp"
    break;

  case 20:
#line 163 "Parser.y"
{ 
    YYSTYPE t = yyvsp[-2];
    if(t != NULL){
        while(t->getSibling() != NULL)
            t = t->getSibling();
        t->setSibling(yyvsp[-1]);
        yyval = yyvsp[-2];
    }
    else yyval = yyvsp[-1];
}
#line 1496 "analysis/Parser.cpp"
    break;

  case 21:
#line 175 "Parser.y"
{
    YYSTYPE t = yyvsp[-1];
    if(t != NULL){
        while(t->getSibling() != NULL)
            t = t->getSibling();
        t->setSibling(yyvsp[0]);
        yyval = yyvsp[-1];
    }
    else yyval = yyvsp[0];
}
#line 1511 "analysis/Parser.cpp"
    break;

  case 22:
#line 185 "Parser.y"
  { yyval = NULL; }
#line 1517 "analysis/Parser.cpp"
    break;

  case 23:
#line 188 "Parser.y"
{
    YYSTYPE t = yyvsp[-1];
    if(t != NULL){
        while(t->getSibling() != NULL)
            t = t->getSibling();
        t->setSibling(yyvsp[0]);
        yyval = yyvsp[-1];
    }
    else yyval = yyvsp[0];
}
#line 1532 "analysis/Parser.cpp"
    break;

  case 24:
#line 198 "Parser.y"
  { yyval = NULL; }
#line 1538 "analysis/Parser.cpp"
    break;

  case 25:
#line 200 "Parser.y"
                          { yyval = yyvsp[0]; }
#line 1544 "analysis/Parser.cpp"
    break;

  case 26:
#line 201 "Parser.y"
                { yyval = yyvsp[0]; }
#line 1550 "analysis/Parser.cpp"
    break;

  case 27:
#line 202 "Parser.y"
               { yyval = yyvsp[0]; }
#line 1556 "analysis/Parser.cpp"
    break;

  case 28:
#line 203 "Parser.y"
                { yyval = yyvsp[0]; }
#line 1562 "analysis/Parser.cpp"
    break;

  case 29:
#line 204 "Parser.y"
               { yyval = yyvsp[0]; }
#line 1568 "analysis/Parser.cpp"
    break;

  case 30:
#line 206 "Parser.y"
                                    { yyval = yyvsp[-1]; }
#line 1574 "analysis/Parser.cpp"
    break;

  case 32:
#line 210 "Parser.y"
{ 
    yyval = new TreeNode(IfK);
    yyval->setChild(yyvsp[-2], 0);
    yyval->setChild(yyvsp[0], 1);
}
#line 1584 "analysis/Parser.cpp"
    break;

  case 33:
#line 216 "Parser.y"
{ 
    yyval = new TreeNode(IfK);
    yyval->setChild(yyvsp[-4], 0);
    yyval->setChild(yyvsp[-2], 1);
    yyval->setChild(yyvsp[0], 2);
}
#line 1595 "analysis/Parser.cpp"
    break;

  case 34:
#line 224 "Parser.y"
{
    yyval = new TreeNode(WhileK);
    yyval->setChild(yyvsp[-2], 0);
    yyval->setChild(yyvsp[0], 1);
}
#line 1605 "analysis/Parser.cpp"
    break;

  case 36:
#line 231 "Parser.y"
{
    yyval = new TreeNode(ReturnK);
    yyval->setChild(yyvsp[-1], 0);
}
#line 1614 "analysis/Parser.cpp"
    break;

  case 37:
#line 237 "Parser.y"
{
    yyval = new TreeNode(AssignK);
    yyval->setName(yyvsp[-2]->getName());
    yyval->setType((yyvsp[-2]->getType() == yyvsp[0]->getType()) ? yyvsp[0]->getType() : Void);
    yyval->setScope(scope);
    yyval->setChild(yyvsp[-2], 0);
    yyval->setChild(yyvsp[0], 1);
}
#line 1627 "analysis/Parser.cpp"
    break;

  case 38:
#line 245 "Parser.y"
                    { yyval = yyvsp[0]; }
#line 1633 "analysis/Parser.cpp"
    break;

  case 39:
#line 248 "Parser.y"
{ 
    yyval = yyvsp[0];
    yyval->setType(Integer);
}
#line 1642 "analysis/Parser.cpp"
    break;

  case 40:
#line 253 "Parser.y"
{
    yyval = yyvsp[-3];
    yyval->setChild(yyvsp[-1], 0);
    yyval->setType(Integer);
}
#line 1652 "analysis/Parser.cpp"
    break;

  case 41:
#line 260 "Parser.y"
{
    yyval = yyvsp[-1];
    yyval->setChild(yyvsp[-2], 0);
    yyval->setChild(yyvsp[0], 1);
    yyval->setType((yyvsp[-2]->getType() == yyvsp[0]->getType()) ? yyvsp[-2]->getType() : Void);
}
#line 1663 "analysis/Parser.cpp"
    break;

  case 42:
#line 266 "Parser.y"
                 { yyval = yyvsp[0]; }
#line 1669 "analysis/Parser.cpp"
    break;

  case 43:
#line 269 "Parser.y"
{ 
    yyval = new TreeNode(OpK);
    yyval->setOp(SLTE);
}
#line 1678 "analysis/Parser.cpp"
    break;

  case 44:
#line 274 "Parser.y"
{ 
    yyval = new TreeNode(OpK);
    yyval->setOp(SLT);
}
#line 1687 "analysis/Parser.cpp"
    break;

  case 45:
#line 279 "Parser.y"
{
    yyval = new TreeNode(OpK);
    yyval->setOp(SGT);
}
#line 1696 "analysis/Parser.cpp"
    break;

  case 46:
#line 284 "Parser.y"
{
    yyval = new TreeNode(OpK); 
    yyval->setOp(SGTE);
}
#line 1705 "analysis/Parser.cpp"
    break;

  case 47:
#line 289 "Parser.y"
{
    yyval = new TreeNode(OpK);
    yyval->setOp(EQUAL);
}
#line 1714 "analysis/Parser.cpp"
    break;

  case 48:
#line 294 "Parser.y"
{
    yyval = new TreeNode(OpK);
    yyval->setOp(DIFFERENT);
}
#line 1723 "analysis/Parser.cpp"
    break;

  case 49:
#line 300 "Parser.y"
{
    yyval = yyvsp[-1];
    yyval->setChild(yyvsp[-2], 0);
    yyval->setChild(yyvsp[0], 1);
    yyval->setType((yyvsp[-2]->getType() == yyvsp[0]->getType()) ? yyvsp[-2]->getType() : Void);
}
#line 1734 "analysis/Parser.cpp"
    break;

  case 50:
#line 306 "Parser.y"
        { yyval = yyvsp[0]; }
#line 1740 "analysis/Parser.cpp"
    break;

  case 51:
#line 309 "Parser.y"
{ 
    yyval = new TreeNode(OpK);
    yyval->setOp(ADD); 
}
#line 1749 "analysis/Parser.cpp"
    break;

  case 52:
#line 314 "Parser.y"
{ 
    yyval = new TreeNode(OpK);
    yyval->setOp(SUB); 
}
#line 1758 "analysis/Parser.cpp"
    break;

  case 53:
#line 320 "Parser.y"
{
    yyval = yyvsp[-1];
    yyval->setChild(yyvsp[-2], 0);
    yyval->setChild(yyvsp[0], 1);
    yyval->setType((yyvsp[-2]->getType() == yyvsp[0]->getType()) ? yyvsp[-2]->getType() : Void);
}
#line 1769 "analysis/Parser.cpp"
    break;

  case 54:
#line 326 "Parser.y"
        { yyval = yyvsp[0]; }
#line 1775 "analysis/Parser.cpp"
    break;

  case 55:
#line 329 "Parser.y"
{ 
    yyval = new TreeNode(OpK);
    yyval->setOp(MULT); 
}
#line 1784 "analysis/Parser.cpp"
    break;

  case 56:
#line 334 "Parser.y"
{ 
    yyval = new TreeNode(OpK);
    yyval->setOp(DIV); 
}
#line 1793 "analysis/Parser.cpp"
    break;

  case 57:
#line 339 "Parser.y"
                               { yyval = yyvsp[-1]; }
#line 1799 "analysis/Parser.cpp"
    break;

  case 58:
#line 340 "Parser.y"
      { yyval = yyvsp[0]; }
#line 1805 "analysis/Parser.cpp"
    break;

  case 59:
#line 341 "Parser.y"
           { yyval = yyvsp[0]; }
#line 1811 "analysis/Parser.cpp"
    break;

  case 60:
#line 342 "Parser.y"
         { yyval = yyvsp[0]; }
#line 1817 "analysis/Parser.cpp"
    break;

  case 61:
#line 345 "Parser.y"
{ 
    yyval = yyvsp[-3];
    yyval->setExp(FuncK);
    yyval->setChild(yyvsp[-1], 0);
    ExpType t = Void;
    for(int i = 0; i < func_id; i++){
        if( func[i]->compare(*(yyvsp[-3]->getName())) == 0 ) {
            t = type[i];
            break;
        }
    }
    yyval->setType(t);
}
#line 1835 "analysis/Parser.cpp"
    break;

  case 62:
#line 359 "Parser.y"
{ 
    yyval = yyvsp[-3];
    yyval->setExp(FuncK);
    yyval->setChild(yyvsp[-1], 0);
    ExpType t = Void;
    for(int i = 0; i < func_id; i++){
        if( func[i]->compare(*(yyvsp[-3]->getName())) == 0 ){
            t = type[i];
            break;
        }
    }
    yyval->setType(t);
}
#line 1853 "analysis/Parser.cpp"
    break;

  case 63:
#line 373 "Parser.y"
                { yyval = yyvsp[0]; }
#line 1859 "analysis/Parser.cpp"
    break;

  case 64:
#line 373 "Parser.y"
                               { yyval = NULL; }
#line 1865 "analysis/Parser.cpp"
    break;

  case 65:
#line 376 "Parser.y"
{
    YYSTYPE t = yyvsp[-2];
    if(t != NULL){
        while(t->getSibling() != NULL)
            t = t->getSibling();
        t->setSibling(yyvsp[0]);
        yyval = yyvsp[-2];
    }
    else yyval = yyvsp[0];
}
#line 1880 "analysis/Parser.cpp"
    break;

  case 66:
#line 386 "Parser.y"
            { yyval = yyvsp[0]; }
#line 1886 "analysis/Parser.cpp"
    break;


#line 1890 "analysis/Parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 388 "Parser.y"


/**
 * @brief O procedimento yyerror imprime na tela 
 * caso ocorra algum erro semântico.
 * 
 * @param msg Mensagem do erro.
 */
void yyerror(const char * msg)
{
  cout << msg << ": " << yytext << " " << yylval << " " << yychar << " line " << scan->getLineNumber() << endl;
  parser->setError();
}
 
/**
 * @brief A função yylex chama a função getToken do parser
 * para obter o próximo token do arquivo de origem.
 * 
 * @return int Token do arquivo.
 */
int yylex(void){ 
    return scan->getToken(); 
}

Parser::Parser(FILE *listing, bool trace){
    sc = 1;
    func = new string*[256];
    type = new ExpType[256];
    func[0] = new string("input");
    func[1] = new string("output");
    type[0] = Integer;
    type[1] = Void;
    func_id = 2;
    str_global = new string("GLOBAL");
    this->listing = listing;
    this->trace = trace;
    this->error = false;
}

bool Parser::parse(TreeNode **tree){ 
    yyparse();
    *tree = this->savedTree;
    if(this->trace) this->savedTree->print(this->listing);
    return this->error;
}

void Parser::setSavedTree(TreeNode *savedTree){
    this->savedTree = savedTree;
}

void Parser::setError(){
    this->error = true;
}
