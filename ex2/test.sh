flex c_blue_TEST.l
cc lex.yy.c -o c_blue.out -lfl
./c_blue.out <test.cb >test.txt
./c_blue.out <test2.cb >test2.txt

flex c_blue.l
cc lex.yy.c -o c_blue.out -lfl
./c_blue.out <test.cb >test.txt