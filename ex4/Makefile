all:
	bison -d c_blue.y     # 注意-d，用于产生对应的头文件
	flex c_blue.l
	gcc main.c lex.yy.c c_blue.tab.c -lfl -o parse
	./parse test.c >test3.txt

clean:
	rm c_blue.tab.h lex.yy.c c_blue.tab.c parse test3.txt