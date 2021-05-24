bison -d -v c_blue.y     # 注意-d，用于产生对应的头文件
flex c_blue.l
gcc c_blue.tab.c lex.yy.c ast.c -o parse.out -lfl 
./parse.out test.cb >test3_1.txt
./parse.out test2.cb >test3_2.txt