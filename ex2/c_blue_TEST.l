%option yylineno
%{
    #include <stdlib.h>
    #include <stdio.h>
%}
/* 相同的输入可以被多种不同的模式匹配，于是出现了二义性。flex使用以下两个原则进行解决：尽可能匹配匹配多的字符串*/
/* 关键字的匹配模式先于标识符的匹配，所以关键字会被正确的匹配。*/
TYPE int|char|float
STRUCT struct
RETURN return
IF if
ELSE else
WHILE while
VOID void
BREAK break
CONTINUE continue
WRITE write
READ read

ID [A-Za-z][A-Za-z0-9]*
INT [0-9]+
FLOAT [0-9]+[.][0-9]+
CHAR \"[A-Za-z0-9]+\" 
/*优先级*/
LP "("
RP ")"
LB "["
RB "]"
DOT [.]
ADDSELF [+][+]
SUBSELF [-][-]
NOT [!]
MUL [*]
DIV [/]
SUB [-]
ADD [+]
RELOP [>]|[<]|[>][=]|[<][=]|[=][=]|[!][=]
AND &{2}
OR [|][|]
ASSIGNOP [=]

COMMA [,]
SEMI [;] 
LC "{"
RC "}"

%%
{STRUCT} {printf("STRUCT: %s\n",yytext);}
{RETURN} {printf("RETURN:%s\n",yytext);}
{IF} {printf("IF:%s\n",yytext);}
{ELSE} {printf("ELSE:%s\n",yytext);}
{WHILE} {printf("WHILE:%s\n",yytext);}
{VOID} {printf("VOID:%s\n",yytext);}
{BREAK} {printf("BREAK:%s\n",yytext);}
{CONTINUE} {printf("CONTINUE:%s\n",yytext);}
{WRITE} {printf("WRITE:%s\n",yytext);}
{READ} {printf("READ:%s\n",yytext);}
{TYPE} {printf("TYPE:%s\n",yytext);}

{INT} {printf("INT:%d\n",atoi(yytext));}
{FLOAT} {printf("FLOAT:%s\n",yytext);}
{CHAR} {printf("CHAR:%s\n",yytext);}
{ID} {printf("ID: %s\n",yytext);}

{LP} {printf("LP:%s\n",yytext);}
{RP} {printf("RP:%s\n",yytext);}
{LB} {printf("LB:%s\n",yytext);}
{RB} {printf("RB:%s\n",yytext);}
{DOT} {printf("DOT:%s\n",yytext);}

{ADDSELF} {printf("ADDSELF:%s\n",yytext);}
{SUBSELF} {printf("SUBSELF:%s\n",yytext);}
{NOT} {printf("NOT:%s\n",yytext);}
{MUL} {printf("MUL:%s\n",yytext);}
{DIV} {printf("DIV:%s\n",yytext);}
{SUB} {printf("SUB:%s\n",yytext);}
{ADD} {printf("ADD:%s\n",yytext);}
{RELOP} {printf("RELOP:%s\n",yytext);}
{AND} {printf("AND:%s\n",yytext);}
{OR} {printf("OR:%s\n",yytext);}
{ASSIGNOP} {printf("ASSIGNOP:%s\n",yytext);}

{COMMA} {printf("COMMA:%s\n",yytext);}
{SEMI} {printf("SEMI:%s\n",yytext);}
{LC} {printf("LC:%s\n",yytext);}
{RC} {printf("RC:%s\n",yytext);}
"//".* {}
"/*"([^\*]|(\*)*[^\*/])*(\*)*"*/" {}
"\n" {}
" " {}
. {printf("error:%s\n",yytext);}
%%
int main(int argc,char **argv){
    yylex();
    return 0;
}
