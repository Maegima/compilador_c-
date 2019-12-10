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
echo gerando parser ...
bison parser.y --defines=parser.h -o parser.cpp
echo gerando objetos para compilacao ...
#rm parser.tab.o
g++ -c main.cpp Scanner.cpp parser.cpp utils/util.c utils/analyze.c utils/symtab.c utils/code.c utils/cgen.c
echo compilando objetos ...
g++ -o compilador.exe main.o Scanner.o parser.o util.o analyze.o symtab.o cgen.o code.o -ly -lfl
rm *.o
#ls -la | grep 'compilador'
#echo executando Scanner.out com \"sort.c\" como entrada ...
#./Scanner.out sort.c
#echo imprimindo saida.txt ...
#sleep 1
#cat saida.txt
