rm compilador.exe
echo gerando scanner.c ...
flex -o scanner.cpp scanner.l
cat scanner.cpp > lex.cpp
sed 's/extern int yylex (void);/\/\/caso queira usar c++\
#ifdef __cplusplus\
    extern "C" int yylex (void);\
#else\
    extern int yylex (void);\
#endif/g' lex.cpp > scanner.cpp
rm lex.cpp
echo gerando parser ...
bison parser.y --defines=parser.h -o parser.cpp
echo gerando objetos para compilacao ...
#rm parser.tab.o
g++ -c main.cpp scanner.cpp parser.cpp tiny/util.c tiny/analyze.c tiny/symtab.c tiny/code.c tiny/cgen.c
echo compilando objetos ...
g++ -o compilador.exe main.o scanner.o parser.o util.o analyze.o symtab.o cgen.o code.o -ly -lfl
rm *.o
#ls -la | grep 'compilador'
#echo executando scanner.out com \"sort.c\" como entrada ...
#./scanner.out sort.c
#echo imprimindo saida.txt ...
#sleep 1
#cat saida.txt
