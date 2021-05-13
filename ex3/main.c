#include <stdio.h>
// extern FILE* yyin;
// int main(int argc,char **argv){
//     if(argc<=1){
//         return 1;
//     }
//     yyin = fopen(argv[1],"r");
//     if(!yyin){
//         perror(argv[1]);
//         return 1;
//     }
//     while(yylex()!=0);
//     return 0;
// }
int main(int argc,char **argv){
    yyin = fopen(argv[1],"r");
    if(!yyin){
        return 1;
    }
    yylineno=1;
	yyparse();
	return 0;
    return 0;
}