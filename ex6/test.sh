bison -d c_blue.y
flex c_blue.l
gcc -g -o parser.out ast.c c_blue.tab.c lex.yy.c middle.c case.c -lfl
./parser.out <test.cb >test.txt