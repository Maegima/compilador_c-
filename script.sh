#!/bin/sh
out_file="scanner.cpp"
echo gerando scanner.c ...
flex -o scanner.cpp scanner.l
cat scanner.cpp > lex.yy.cpp
sed 's/extern int yylex (void);/\/\/caso queira usar c++\
#ifdef __cplusplus\
    extern "C" int yylex (void);\
#else\
    extern int yylex (void);\
#endif/g' lex.yy.cpp > scanner.cpp
rm lex.yy.cpp
echo gerando parser ...
bison -d parser.y
echo gerando objetos para compilacao ...
#rm parser.tab.o
g++ -c main.cpp scanner.cpp parser.tab.c tiny/util.c tiny/analyze.c tiny/symtab.c
echo compilando objetos ...
g++ -o compilador main.o scanner.o parser.tab.o util.o analyze.o symtab.o -ly -lfl 
#ls -la | grep 'compilador'
#echo executando scanner.out com \"sort.c\" como entrada ...
#./scanner.out sort.c
#echo imprimindo saida.txt ...
#sleep 1
#cat saida.txt
