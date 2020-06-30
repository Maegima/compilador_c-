rm bin/compilador.exe
echo gerando Scanner.cpp ...
prefix="analysis"
flex -o $prefix/Scanner.cpp Scanner.l
cat $prefix/Scanner.cpp > lex.cpp
sed 's/extern int yylex (void);/\/\/caso queira usar c++\
#ifdef __cplusplus\
    extern "C" int yylex (void);\
#else\
    extern int yylex (void);\
#endif/g' lex.cpp > $prefix/Scanner.cpp
rm lex.cpp
echo gerando Parser.cpp ...
bison Parser.y --defines=parser.h -o $prefix/Parser.cpp
echo gerando objetos para compilacao ...
#rm parser.tab.o
#g++ -Wall -c main.cpp Scanner.cpp Parser.cpp utils/TreeNode.cpp utils/Register.cpp utils/CodeGenerator.cpp utils/LineList.cpp utils/BucketList.cpp utils/SymbolTable.cpp utils/Semantic.cpp utils/VariablesTable.cpp utils/Code.cpp utils/AssemblyGenerator.cpp utils/Assembler.cpp
echo compilando objetos ...
cd bin
prefix="../analysis"
g++ -Wall -c $prefix/Scanner.cpp $prefix/Parser.cpp $prefix/TreeNode.cpp $prefix/BucketList.cpp $prefix/SymbolTable.cpp \
$prefix/Semantic.cpp $prefix/LineList.cpp
prefix="../synthesis"
g++ -Wall -I../analysis -I../utils -c $prefix/Register.cpp $prefix/VariablesTable.cpp $prefix/Code.cpp \
$prefix/CodeGenerator.cpp $prefix/AssemblyGenerator.cpp $prefix/Assembler.cpp
g++ -Wall -I../analysis -I../utils -c ../main.cpp
g++ -Wall -o compilador.exe main.o Scanner.o Parser.o Register.o CodeGenerator.o TreeNode.o LineList.o BucketList.o SymbolTable.o \
Semantic.o VariablesTable.o Code.o AssemblyGenerator.o Assembler.o -ly -lfl
#rm *.o
#ls -la | grep 'compilador'
#echo executando Scanner.out com \"sort.c\" como entrada ...
#./Scanner.out sort.c
#echo imprimindo saida.txt ...
#sleep 1
#cat saida.txt
