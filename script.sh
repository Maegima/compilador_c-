rm compilador.exe
echo gerando Scanner.cpp ...
flex -o Scanner.cpp Scanner.l
cat Scanner.cpp > lex.cpp
sed 's/extern int yylex (void);/\/\/caso queira usar c++\
#ifdef __cplusplus\
    extern "C" int yylex (void);\
#else\
    extern int yylex (void);\
#endif/g' lex.cpp > Scanner.cpp
rm lex.cpp
echo gerando Parser.cpp ...
bison Parser.y --defines=parser.h -o Parser.cpp
echo gerando objetos para compilacao ...
#rm parser.tab.o
g++ -c main.cpp Scanner.cpp utils/TreeNode.cpp Parser.cpp utils/analyze.cpp utils/symtab.cpp utils/code.c utils/cgen.cpp
echo compilando objetos ...
g++ -o compilador.exe main.o Scanner.o parser.o analyze.o symtab.o cgen.o code.o TreeNode.o -ly -lfl
rm *.o
#ls -la | grep 'compilador'
#echo executando Scanner.out com \"sort.c\" como entrada ...
#./Scanner.out sort.c
#echo imprimindo saida.txt ...
#sleep 1
#cat saida.txt
